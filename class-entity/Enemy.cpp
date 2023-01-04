#include "Enemy.h"
#include "Player.h"
#include <cmath>
#include <iostream>

using namespace std;

void Enemy::Initialiser_Enemy(Player *_player, double modifier){
    player = _player; // Set up player pointer

    // as long as GameManager has srand, this is not needed.
    //srand(time(NULL)); // Activate RNG

    name = enemyTypes[getRandomInt(enemyTypes.size())];
    level = getRandomInt(fmax(1, player -> getLevel() - 2), (int)floor((player -> getLevel() + 2) * (1 + modifier)));

    // Stats - Initialises based on player progression.
    setMaxHealth(enemyBaseHealth * level * getRandomStrength() * (1 + modifier));
    setAttack(enemyBaseAttack * level * getRandomStrength() * (1 + modifier));
    setDefence(enemyBaseDefence * level * getRandomStrength() * (1 + modifier));
    setHealth(getMaxHealth());
}

Enemy::Enemy(Player *_player){
    Initialiser_Enemy(_player, 0);
}

Enemy::Enemy(Player *_player, int _x, int _y){
    Initialiser_Enemy(_player, 0);

    x = _x;
    y = _y;
}

Enemy::Enemy(Player *_player, int _x, int _y, double modifier){
    Initialiser_Enemy(_player, modifier);

    x = _x;
    y = _y;
}

// ------------
// Basic Enemy AI
// Checks if the player is within aggro distance,
// Then checks if the player is in attack distance,
// else move towards the player.
// ------------

void Enemy::Move(){
    // Has a chance to approach the player even when far away.
    if(getDistanceFromEntity(*player) <= enemyAggroDistance == false){
        if(getRandomInt(100) >= enemyFarMovementChance) return;
    }

    if(getDistanceFromEntity(*player) > attackRange){
        Step();
    }
    else {
        PerformAttack(player);
    }
}

void Enemy::Step(){
    vector<char> direction;

    if(player -> getY() < getY()) direction.push_back('n');
    if(player -> getY() > getY()) direction.push_back('s');
    if(player -> getX() < getX()) direction.push_back('w');
    if(player -> getX() > getX()) direction.push_back('e');

    switch(direction[getRandomInt(direction.size())]){
        case 'n':
            setY(getY() - 1);
            break;
        case 's':
            setY(getY() + 1);
            break;
        case 'w':
            setX(getX() - 1);
            break;
        case 'e':
            setX(getX() + 1);
            break;
    }
}

// ------------
// Boss Identifier
// ------------

bool Enemy::getIsBoss(){
    return isBoss;
}

void Enemy::setIsBoss(bool _isBoss){
    isBoss = _isBoss;
}

// ------------
// Helper Functions
// ------------

// Enemy stats vary between 65% - 135% of the base value.
double Enemy::getRandomStrength(){
    return (double) getRandomInt(65, 135)/100;
}

// Prints attack action
void Enemy::outputAttackMessage(Entity *target){
    cout << getName() << " " << enemyAttackActions[getRandomInt(enemyAttackActions.size())] << " " << target -> getName() << "!" << endl;
}

Enemy::~Enemy(){
    // no!!!
    //delete playerPointer;
}