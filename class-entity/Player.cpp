#include "Player.h"
#include "Enemy.h"
#include "Box.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// ------------
// Constructors
// ------------

// Initialises player variables.
// Other variables are already initialised by the inherited Entity constructor.
void Player::Initialiser_Player(){
    name = "Player";
    level = 0;
    experience = 0;
    potionCount = 0;
    sightRadius = 4;

    // Default player character stats
    baseMaxHealth = 10.0;
    baseAttack = 2.0;
    baseDefence = 0.5;

    boostMaxHealth = 0;
    boostAttack = 0;
    boostDefence = 0;

    recalculateStats();
    setHealth(getMaxHealth());
}

Player::Player() : Entity(){
    Initialiser_Player();
}

// I have thrown the entire code of the previous constructor into the below constructors
// Because it would somehow spawn with crazy numbers - Player() does not work.
Player::Player(int _x, int _y) : Entity(_x, _y){
    Initialiser_Player();
}

Player::Player(int _x, int _y, int _potionCount) : Entity(_x, _y){
    Initialiser_Player();
    potionCount = _potionCount;
}

// ------------
// Functions
// ------------

void Player::recalculateStats(){
    const int percentBase = 1;
    const double percentGain = 0.1;

    setMaxHealth(baseMaxHealth * (percentBase + percentGain * boostMaxHealth));
    setAttack(baseAttack * (percentBase + percentGain * boostAttack));
    setDefence(baseDefence * (percentBase + percentGain * boostDefence));
}

// Area of a circle: pi * r ^ 2
// Increase area by 1 every level
// Thus: r = sqrt((pi + level)/pi)
void Player::recalculateAttackRange(){
    const int baseRadius = 1;

    cout << "Attack Range: " << attackRange;
    attackRange = sqrt((M_PI * (baseRadius + getLevel()))/M_PI);
    cout << " -> " << attackRange << " spaces" << endl;
}

// When the player picks up a power up.
void Player::powerUp(int boostIndex, int boostCount){
    // Makes no output if there isn't any boosts of that type in the box.
    if(boostCount <= 0) return;

    switch(boostIndex){
        case boostType::maxHealth:
            boostMaxHealth += boostCount;
            cout << getName() << "'s health has been boosted!" << " (+" << boostCount << ")" << endl;
            break;
        case boostType::attack:
            boostAttack += boostCount;
            cout << getName() << "'s attack has been boosted!" << " (+" << boostCount << ")" << endl;
            break;
        case boostType::defence:
            boostDefence += boostCount;
            cout << getName() << "'s defence has been boosted!" << " (+" << boostCount << ")" << endl;
            break;
        default:
            cout << getName() << " found a bunch of useless." << " (+" << boostCount << ")" << endl;
            break;
    }

    recalculateStats();
}

// The experience functions uses a formula to calculate the level based on the experience gained.
// Formula based on the sum formula: x = n*(n+1)/2
// Next level requires 10 * level exp: Level 48 requires 480 exp for example.
// By rearrangement, xp = 10*level*(level+1)/2
// Becomes level = (-1 + sqrt(1 + 8xp/10))/2
void Player::gainExperience(int experienceCount){
    experience += experienceCount;
    cout << name << " gains " << experienceCount << " XP! [" << experience << "/" << 10*(level+1)*(level+2)/2 << "]" << endl;
    levelCheck();
}

void Player::levelCheck(){
    int newLevel = (int)floor((-1 + sqrt(1+8*experience/10))/2);
    if(newLevel > level){
        // Level up!
        cout << name << " has levelled up! (" << level << " -> " << newLevel << ")" << endl;
        levelUpgrade(newLevel);
    }
}

void Player::levelUpgrade(int newLevel){
    int levelUps = newLevel - level;

    // Outputs the difference in base stats due to level up.
    cout << "Base Max Health: " << baseMaxHealth << " -> " << baseMaxHealth + healthGain * levelUps << endl;
    cout << "Base Attack: " << baseAttack << " -> " << baseAttack + attackGain * levelUps << endl;
    cout << "Base Defence: " << baseDefence << " -> " << baseDefence + defenceGain * levelUps << endl;

    baseMaxHealth += healthGain * levelUps;
    baseAttack += attackGain * levelUps;
    baseDefence += defenceGain * levelUps;

    recalculateStats();
    applyHealing(getMaxHealth());
    potionCount += 10;
    level = newLevel;
    recalculateAttackRange();
}

// ------------
// Move Functions
// ------------

void Player::Move(int mapX_Bound, int mapY_Bound, vector<vector<char>> map){
    bool successfulMove = false;
    while(successfulMove == false){
        // Outputs the map and player status into the console
        getVision(mapX_Bound, mapY_Bound, map);
        getPlayerStatus();

        cout << "Enter a command: ";

        string command = "";
        cin >> command;

        // Invalid inputs default to the help command,
        // Shows the user what actions they can input.
        int intCommand = playerValidCommandsEnum::Help;
        for(int i = 0; i < playerValidCommands.size(); i++){
            if(command == playerValidCommands[i]){
                intCommand = i;
                break;
            }
        }

        switch(intCommand){
            case playerValidCommandsEnum::Up:
            case playerValidCommandsEnum::Left:
            case playerValidCommandsEnum::Down:
            case playerValidCommandsEnum::Right:
                successfulMove = moveMovement(command[0], mapX_Bound, mapY_Bound);
                if(successfulMove == false) cout << "Cannot move out of bounds!" << endl;
                break;
            case playerValidCommandsEnum::Attack:
                successfulMove = moveAttack();
                if(successfulMove == false) cout << "There is no attackable entity within range!" << endl;
                break;
            case playerValidCommandsEnum::DrinkPotion:
                successfulMove = movePotion();
                if(successfulMove == false) cout << name << " has no potions!" << endl;
                break;
            case playerValidCommandsEnum::Wait:
                successfulMove = moveWait();
                break;
            case playerValidCommandsEnum::GetPlayerStats:
                cout << "---< " << getName() << "'s stats >---" << endl;
                cout << "Max Health: " << baseMaxHealth << " (+" << baseMaxHealth * 0.1 * boostMaxHealth << ")" << endl;
                cout << "Attack: " << baseAttack << " (+" << baseAttack * 0.1 * boostAttack << ")" << endl;
                cout << "Defence: " << baseDefence << " (+" << baseDefence * 0.1 * boostDefence << ")" << endl;
                break;
            case playerValidCommandsEnum::Suicide:
                successfulMove = moveDie();
                break;
            case playerValidCommandsEnum::Help:
                for(int i = 0; i < playerValidCommands.size(); i++){
                    cout << i << ". " << playerValidCommands[i] << endl;
                }
                break;
            default:
                cout << "Invalid command!" << endl;
                break;
        }
    }
}

bool Player::moveMovement(char direction, int mapX_Bound, int mapY_Bound){
    switch(direction){
        case 'w':
            if((getY() - 1) < 0) return false;
            else setY(getY() - 1);
            break;
        case 's':
            if((getY() + 1) >= mapY_Bound) return false;
            else setY(getY() + 1);
            break;
        case 'a':
            if((getX() - 1) < 0) return false;
            else setX(getX() - 1);
            break;
        case 'd':
            if((getX() + 1) >= mapX_Bound) return false;
            else setX(getX() + 1);
            break;
    }
    return true;
}

// Player will attack 1 + level / 2 rounded down times.
bool Player::moveAttack(){
    const int numAttacksBase = 1;
    const int numAttacksLevelDivisor = 2;
    bool hasAttacked = false;

    // Calculates the number of attacks the Player can make in this turn.
    int numAttacks = numAttacksBase + level / numAttacksLevelDivisor;

    while(numAttacks > 0){
        for(int i = 0; i < enemies -> size(); i++){
            if(getDistanceFromEntity(*(enemies -> at(i))) <= attackRange){
                PerformAttack(enemies -> at(i));
                numAttacks--;
                hasAttacked = true;

                if(numAttacks <= 0) break;
            }
        }
        if(hasAttacked == false) break;
    }

    return hasAttacked;
}

bool Player::movePotion(){
    const int healthPercentGain = 50;

    if(potionCount > 0){
        potionCount--;
        cout << name << " drank a healing potion!" << " (Potions Left: " << potionCount << ")" << endl;
        applyHealing(getMaxHealth() * healthPercentGain/100);
        return true;
    } else return false;
}

bool Player::moveWait(){
    cout << getName() << " " << playerWaitActions[getRandomInt(playerWaitActions.size())] << endl;
    return true;
}

bool Player::moveDie(){
    applyDamage(getHealth());
    return true;
}

// ------------
// Get / Set
// ------------

int Player::getExperience(){
    return experience;
}

int Player::getCurrentLevel(){
    return (int)floor((-1 + sqrt(1+8*experience/10))/2);
}

double Player::getCurrentHealthLost(){
    return getMaxHealth() - getHealth();
}

void Player::setEnemiesPointer(vector<Enemy*> *_enemies){
    enemies = _enemies;
}
void Player::setBoxesPointer(vector<Box*> *_boxes){
    boxes = _boxes;
}

// ------------
// Misc Functions
// ------------

// Prints out the area around the player based on the vision range
void Player::getVision(int mapX_Bound, int mapY_Bound, vector<vector<char>> map){
    // Marks objects on the map
    for(int i = 0; i < boxes -> size(); i++){    // Marks Boxes
        map[boxes -> at(i) -> getY()][boxes -> at(i) -> getX()] = 'O';
    }
    for(int i = 0; i < enemies -> size(); i++){    // Marks Enemies, Bosses prioritised to be seen over normal enemies.
        if(map[enemies -> at(i) -> getY()][enemies -> at(i) -> getX()] != 'M' && enemies -> at(i) -> getIsBoss() == false) map[enemies -> at(i) -> getY()][enemies -> at(i) -> getX()] = 'm';
        else if(enemies -> at(i) -> getIsBoss()) map[enemies -> at(i) -> getY()][enemies -> at(i) -> getX()] = 'M';
    }
    map[getY()][getX()] = 'A';                  // Marks Player

    // For loop clamps vision to the sight radius of the player.
    for(int ySight = getY() - sightRadius; ySight <= getY() + sightRadius; ySight++){
        //cout << "y: " << ySight << endl;
        if(ySight < 0 || ySight >= mapY_Bound) continue; // If sight on Y-Axis happens to be out of map bounds
        for(int xSight = getX() - sightRadius; xSight <= getX() + sightRadius; xSight++){
            //cout << "x: " << xSight << endl;
            if(xSight < 0 || xSight >= mapX_Bound) continue; // If sight on X-Axis happens to be out of map bounds
            cout << map[ySight][xSight];
        }
        cout << endl;
    }
}

// Prints attack action
void Player::outputAttackMessage(Entity *target){
    cout << getName() << " " << playerAttackActions[getRandomInt(playerAttackActions.size())] << " " << target -> getName() << "!" << endl;
}

// Prints out the player's status
void Player::getPlayerStatus(){
    cout << getName() << " " << "[LVL: " << level << "] ";
    cout << "(" << getHealth() << "/" << getMaxHealth() << ") is at <";
    cout << getX() << "," << getY() << ">" << endl;
}