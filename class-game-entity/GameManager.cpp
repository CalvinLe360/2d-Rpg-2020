#include "../class-entity/Entity.h"
#include "../class-entity/Player.h"
#include "../class-entity/Enemy.h"
#include "../class-entity/Box.h"
#include "GameManager.h"
#include <iostream>
#include <cmath>

// Libraries specifically required for Random Number Generation
#include <stdlib.h>
#include <time.h>

// Included this library in case of input faults
#include <limits>

using namespace std;

// ------------
// Constructors
// ------------

void GameManager::Initialiser(){
    // Initialises all base game settings and variables here
    duration = 0;

    // Activates RNG
    srand(time(NULL));

    // Randomises the map size based on the configurations in GameManager.h
    mapX_Bound = getRandomInt(mapSizeMin, mapSizeMax);
    mapY_Bound = getRandomInt(mapSizeMin, mapSizeMax);
}

GameManager::GameManager(){
    Initialiser();
}

GameManager::GameManager(int _mapX_Bound, int _mapY_Bound){
    Initialiser();

    mapX_Bound = _mapX_Bound;
    mapY_Bound = _mapY_Bound;
}

GameManager::GameManager(vector<vector<char>> _map){
    Initialiser();
    map = _map;
    if(map.empty() == false) {
        mapY_Bound = _map.size();
        mapX_Bound = _map[0].size();
    }
}

// ------------
// Game Functions
// ------------

void GameManager::Start(){
    cout << "Welcome to the Field of Adventure!" << endl;
    cout << "Select your game-mode!" << endl;

    // User chooses options here
    int choice = StartOption::Invalid;

    while(choice == StartOption::Invalid){
        cout << "1. Quick Start" << endl << "2. Custom Start" << endl << "3. Help" << endl << "4. Exit" << endl;
        cin >> choice;
        if(checkValidUserInput() == false){
            cout << "Invalid command!" << endl;
            choice = StartOption::Invalid;
            continue;
        }
        switch(choice){
            case StartOption::QuickStart:
                Setup(true);
                break;
            case StartOption::CustomStart:
                Setup(false);
                break;
            case StartOption::Help:
                cout << "Your objective is to survive the longest in an unforgiving world where monsters populate." << endl;
                cout << "Quick Start gets you into the game with set parameters and a random-sized map." << endl;
                cout << "Custom Start lets you modify these parameters to provide a different experience!" << endl;
                cout << "Write \'help\' in-game to see what actions the player character can perform." << endl;
                choice = StartOption::Invalid;
                break;
            case StartOption::Exit:
                exit(0);
                break;
            default:
                cout << "Invalid command!" << endl;
                choice = StartOption::Invalid;
                break;
        }
    }
}

void GameManager::Start(int _playerX, int _playerY){
    Start();

    // Checks if the passed specific player coordinates point to a legal space.
    if(_playerX >= 0 && _playerX < mapX_Bound) player -> setX(_playerX);
    if(_playerY >= 0 && _playerY < mapY_Bound) player -> setY(_playerY);
}

// Quickly starts the game with toggled settings for debug sessions
void GameManager::Start_Debug(){
    canSpawnEnemies = false;
    canSpawnBoxes = false;
    canGenerateBoxes = false;
    canGenerateEnemies = false;

    if(map.empty()) generateMap();
    spawnPlayer();
    player -> setName("tester");
    difficultyModifier = 1;
}

// ------------
// Player Setup
// ------------

void GameManager::Setup(bool quickStart){
    // Player selects options if they don't quickstart
    if(quickStart) {
        generateMap();
    }
    else {
        bool gameIsStarting = false;
        while(gameIsStarting == false){
            cout << "<-- Current Settings -->" << endl;

            cout << "1. Map Width: " << mapX_Bound << endl;
            cout << "2. Map Height: " << mapY_Bound << endl;
            cout << "3. Initial Powerup Count: " << initialPowerUpPercentCount * mapX_Bound * mapY_Bound / 100 << endl;
            cout << "4. Initial Monster Count: " << initialMonsterPercentCount * mapX_Bound * mapY_Bound / 100 << endl;
            cout << "5. Powerup Spawn Turn Interval: " << spawnPowerUpDelay << endl;
            cout << "6. Monster Spawn Turn Interval: " << spawnMonsterDelay << endl;
            cout << "7. Monster Percent Chance to drop Powerup: " << monsterDropPowerUpChance << "%" << endl;
            cout << "8. Spawned Monster becomes boss Turn Interval: " << spawnMonsterBossSpawnDelay << endl << endl;
            cout << "9. Start The Game" << endl;

            // Input section
            int userInput;
            cin >> userInput;

            if(checkValidUserInput() == true){ // Check if the user inputs an integer.
                switch(userInput){
                    case Settings::MapWidth:
                        cout << "Set Map Width (Current: " << mapX_Bound << "): ";
                        cin >> userInput;
                        if(checkValidUserInput() == true) mapX_Bound = userInput;
                        break;
                    case Settings::MapHeight:
                        cout << "Set Map Height (Current: " << mapY_Bound << "): ";
                        cin >> userInput;
                        if(checkValidUserInput() == true) mapY_Bound = userInput;
                        break;
                    case Settings::InitialPowerupCount:
                        cout << "Initial Powerup Count is based on a percentage of the number of map tiles." << endl;
                        cout << "Currently, a [" << mapX_Bound << " x " << mapY_Bound << "] map will start with " << initialPowerUpPercentCount * mapX_Bound * mapY_Bound / 100 << " powerups." << endl;
                        cout << "Initial Powerup Count (Current: " << initialPowerUpPercentCount << "%): ";
                        cin >> userInput;
                        if(checkValidUserInput() == true) initialPowerUpPercentCount = userInput;
                        break;
                    case Settings::InitialMonsterCount:
                        cout << "Initial Monster Count is based on a percentage of the number of map tiles." << endl;
                        cout << "Currently, a [" << mapX_Bound << " x " << mapY_Bound << "] map will start with " << initialMonsterPercentCount * mapX_Bound * mapY_Bound / 100 << " monsters." << endl;
                        cout << "Initial Powerup Count (Current: " << initialMonsterPercentCount << "%): ";
                        cin >> userInput;
                        if(checkValidUserInput() == true) initialMonsterPercentCount = userInput;
                        break;
                    case Settings::PowerupSpawnInterval:
                        cout << "Set Powerup Spawn Interval (Currently spawns every " << spawnPowerUpDelay << " turns): ";
                        cin >> userInput;
                        if(checkValidUserInput() == true) spawnPowerUpDelay = userInput;
                        break;
                    case Settings::MonsterSpawnInterval:
                        cout << "Set Monster Spawn Interval (Currently spawns every " << spawnMonsterDelay << " turns): ";
                        cin >> userInput;
                        if(checkValidUserInput() == true) spawnMonsterDelay = userInput;
                        break;
                    case Settings::MonsterDropChance:
                        cout << "Set Chance for Monsters to drop Powerups (Current: " << monsterDropPowerUpChance << "%): ";
                        cin >> userInput;
                        if(checkValidUserInput() == true) monsterDropPowerUpChance = userInput;
                        break;
                    case Settings::MonsterBossSpawnDelay:
                        cout << "Set Monster Boss Spawn Interval (Currently a boss spawns every " << spawnMonsterBossSpawnDelay << " monster spawns): ";
                        cin >> userInput;
                        if(checkValidUserInput() == true) spawnMonsterBossSpawnDelay = userInput;
                        break;
                    case Settings::StartGame:
                        cout << "Custom Game will now start with these settings..." << endl;
                        gameIsStarting = true;
                        break;
                    case Settings::InvalidSetting:
                    default:
                        cout << "Option " << userInput << " does not exist." << endl;
                        break;
                }
            }
            cout << endl; // Line Separator
        }
        /*
        cout << "Set percentage of map tiles to box count" << endl;
        cout << "Default (" << GameManager_configuration[2] << "): ";
        cin >> GameManager_configuration[2];

        cout << "Set turn delay between monster spawns" << endl;
        cout << "Default (" << GameManager_configuration[3] << "): ";
        cin >> GameManager_configuration[3];

        cout << "Set turn delay between box spawns" << endl;
        cout << "Default (" << GameManager_configuration[4] << "): ";
        cin >> GameManager_configuration[5];

        cout << "Set chance for enemy to drop box" << endl;
        cout << "Default (" << GameManager_configuration[5] << "): ";
        cin >> GameManager_configuration[4];

        cout << "Set percentage of map tiles to enemy count" << endl;
        cout << "Default (" << GameManager_configuration[6] << "): ";
        cin >> GameManager_configuration[6];

        cout << "Set number of spawns before making a boss enemy" << endl;
        cout << "Default (" << GameManager_configuration[7] << "): ";
        cin >> GameManager_configuration[7];

        cout << "How big should the map be? (X-Axis): ";
        cin >> mapX_Bound;
        cout << "Set Map Size of (Y-Axis): ";
        cin >> mapY_Bound;
        */

        MapSizeSet(false);
    }

    // Essential options that the player must pick, regardless of quick start.
    spawnPlayer();
    NameCharacter();
    SelectDifficulty();

    // Functions that run with values based on given conditions.
    generateMapObjects();

    /*
    // Player selects options if they don't quickstart
    if(quickStart){

    }
    else {

    }
    */
}

// Initialises the name of player.
void GameManager::NameCharacter(){
    cout << "Name your character: ";

    string name = "";
    cin >> name;
    if(name != "") player -> setName(name);
}

// Main Files should have a while loop, using the player character's health as the conditional.
// This design enables room for performing actions outside of the GameLoop; especially testing.
bool GameManager::GameLoop(){
    // Death Check
    if(player -> getHealth() <= 0) {
        GameOver();
        return false;
    }

    // Normal Loop
    duration++;
    player -> Move(mapX_Bound, mapY_Bound, map);
    BoxFunction();
    EnemyFunction();

    return true;
}

// Logic for each box
void GameManager::BoxFunction(){
    for(int i = boxes.size() - 1; i >= 0; i--){
        if(player -> getX() == boxes[i] -> getX() && player -> getY() == boxes[i] -> getY()){
            boxes[i] -> powerupGive(getCurrentModifier());

            // Garbage Collection
            delete boxes[i];
            boxes.erase(boxes.begin() + i);
        }
    }
}

// Controls each enemy on every execution.
void GameManager::EnemyFunction(){
    for(int i = enemies.size() - 1; i >= 0; i--){
        // Death Check
        if(enemies[i] -> getHealth() <= 0){
            cout << enemies[i] -> getName() << " has been killed." << endl;
            if(enemies[i] -> getIsBoss()) player -> gainExperience(enemies[i] -> getLevel() * 5);
            else player -> gainExperience(enemies[i] -> getLevel());

            // Chance to spawn box
            if(getRandomInt(100) < monsterDropPowerUpChance) {
                spawnBox(enemies[i] -> getX(), enemies[i] -> getY());
            }

            // Garbage collection
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
            continue;
        }

        // Enemy Move Function
        enemies[i] -> Move();
    }

    // Tries to generate an enemy this turn.
    GameLoop_generateEnemy();
}

void GameManager::GameOver(){
    cout << player -> getName() << " has died!" << endl << endl << endl;

    cout << "--< GAME OVER >--" << endl;
    cout << "You survived for " << duration << " rounds!" << endl;
    cout << "Level: " << player -> getLevel() << endl;
    cout << player -> getName() << " returns to dust once more..." << endl;
    cout << "-----------------" << endl;

    // Garbage Collection - Remove objects at game end.
    delete player;
    flushEnemies();
    flushBoxes();
    cout << endl << endl;
}

// Box generation
void GameManager::GameLoop_generateBox(){
    if(canSpawnBoxes){
        generateBoxDelayCurrent--;
        if(generateBoxDelayCurrent <= 0){
            spawnBox();

            // Resets delay to the game manager configuration.
            generateEnemyDelayCurrent = spawnPowerUpDelay;
        }
    }
}

// Enemy generation
void GameManager::GameLoop_generateEnemy(){
    if(canSpawnEnemies){
        generateEnemyDelayCurrent--;
        if(generateEnemyDelayCurrent <= 0) {
            spawnEnemy();

            // Resets delay to the game manager configuration.
            generateEnemyDelayCurrent = spawnMonsterDelay;
        }
    }
}

// ------------
// Spawn Functions
// ------------

void GameManager::spawnPlayer(){
    spawnPlayer(getRandomInt(mapX_Bound), getRandomInt(mapY_Bound));
}

void GameManager::spawnPlayer(int _x, int _y){
    player = new Player(_x, _y, 10);
    player -> setEnemiesPointer(&enemies);
    player -> setBoxesPointer(&boxes);
}

void GameManager::spawnEnemy(){
    // Enemy generates on a random tile if no coordinates were passed.
    spawnEnemy(getRandomInt(mapX_Bound), getRandomInt(mapY_Bound));
}

void GameManager::spawnEnemy(int _x, int _y){
    if(duration != 0 && generateEnemyAsBossDelayCurrent <= 0){
        Enemy *newEnemy = new Enemy(player, _x, _y, getCurrentModifier() * 5);
        enemies.push_back(newEnemy);
        generateEnemyAsBossDelayCurrent = spawnMonsterBossSpawnDelay;

        newEnemy -> setIsBoss(true);
    }
    else{
        generateEnemyAsBossDelayCurrent--;
        Enemy *newEnemy = new Enemy(player, _x, _y, getCurrentModifier());
        enemies.push_back(newEnemy);
    }
}

void GameManager::spawnBox(){
    // Box generates on a random tile if no coordinates were passed.
    spawnBox(getRandomInt(mapX_Bound), getRandomInt(mapY_Bound));
}

void GameManager::spawnBox(int _x, int _y){
    Box *newBox = new Box(player, _x, _y);
    boxes.push_back(newBox);
}

// Difficulty affects how quickly enemy stats scale over time.
void GameManager::SelectDifficulty(){
    for(int i = 0; i < difficulty.size(); i++){
        cout << i << ". " << difficulty[i] << endl;
    }
    cout << "Select your difficulty: ";

    // Any number, including those with decimal points can be used.
    // Clamps difficulty to 0.5 in case of negative numbers.
    cin >> difficultyModifier;
    if(checkValidUserInput() == false){ // Difficulty modifier is not input as a number
        cout << "Setting initial difficulty to " << difficulty[1] << endl;
        difficultyModifier = 1;
    }

    // Equation of initially set difficulty modifier:
    // initial difficulty = 0.5 * (1 + input number)
    difficultyModifier = fmax(0.5 * (1 + difficultyModifier), 0.5);
}

// ------------
// Map Generation Functions
// ------------
void GameManager::generateMap(){
    generateMap(mapX_Bound, mapY_Bound);
}

void GameManager::generateMap(int _mapX_Bound, int _mapY_Bound){
    // In case any rare bugs come up from map bound inconsistency
    mapX_Bound = _mapX_Bound;
    mapY_Bound = _mapY_Bound;

    cout << "Generating map of size: [" << _mapX_Bound << " x " << _mapY_Bound << "] ..." << endl;
    if(map.empty() == false) map.clear(); // Possibility of the player travelling to different maps.
    for(int yCoord = 0; yCoord < _mapY_Bound; yCoord++){
        vector<char> region;
        for(int xCoord = 0; xCoord < _mapX_Bound; xCoord++){
            region.push_back('.');
        }
        map.push_back(region);
    }
}

void GameManager::generateMapObjects(){
    // Regenerate boxes and enemies, destroys existong ones first.
    flushEnemies();
    flushBoxes();

    if(canGenerateBoxes){
        int boxesToSpawn = mapX_Bound * mapY_Bound * initialPowerUpPercentCount / 100;
        for(int i = 0; i < boxesToSpawn; i++){
            spawnBox();
        }
    }

    if(canGenerateEnemies){
        int enemiesToSpawn = mapX_Bound * mapY_Bound * initialMonsterPercentCount / 100;
        for(int i = 0; i < enemiesToSpawn; i++) {
            spawnEnemy();
        }
    }
}

// Map Size for generation given empty map.
void GameManager::MapSizeSet(bool forceGeneration){
    if(map.empty() || forceGeneration) {
        /*
        cout << "How big should the map be? (X-Axis): ";
        cin >> mapX_Bound;
        cout << "Set Map Size of (Y-Axis): ";
        cin >> mapY_Bound;
        */

        generateMap();
    }
}

// ------------
// Helper Functions
// ------------

// Returns an integer between 0 (inclusive) and the upper bound (exclusive)
int GameManager::getRandomInt(int upperBound){
    return rand() % upperBound;
}

// Returns an integer between min and max (both inclusve)
int GameManager::getRandomInt(int min, int max){
    return min + rand() % (max - min + 1);
}

// Returns the modifier based on:
// Duration and Difficulty.
double GameManager::getCurrentModifier(){
    return 0.02 * duration * difficultyModifier;
}

// Proofs the program of invalid user inputs, if used.
bool GameManager::checkValidUserInput(){
    if(!cin){ // If the input is not valid.
        // These two lines apparently fix the cin failbit problem.
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cout << "Input is not valid!" << endl << endl;
        return false;
    }
    return true;
}

// ------------
// Deconstructor
// ------------

GameManager::~GameManager(){

}

// Garbage Collection should the game end.
void GameManager::flushEnemies(){
    for(int i = enemies.size() - 1; i >= 0; i--){
        delete enemies[i];
        enemies.erase(enemies.begin() + i);
    }
}

void GameManager::flushBoxes(){
    for(int i = boxes.size() - 1; i >= 0; i--){
        delete boxes[i];
        boxes.erase(boxes.begin() + i);
    }
}