#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "../class-entity/Player.h"
#include "../class-entity/Enemy.h"
#include "../class-entity/Box.h"
#include <vector>

// Some settings that can easily be modified here
static int GameManager_configuration[] = {
    500,            // Min Map-Axis Size
    1500,           // Max Map-Axis Size
    10,             // Percentage of map filled with powerups.
    2,              // Turn delay between monster spawns
    5,              // Percent chance of an enemy dropping a powerup box.
    10,             // Turn delay between box spawns
    2,              // Initial monster count by percentage of map tiles.
    20,             // Spawns before a boss monster is created.
};

static vector<string> difficulty = {
    "Drizzle",
    "Rainstorm",
    "Monsoon",
};

class GameManager {
public:
    // Constructors
    void Initialiser();                              // Initialises the variables.
    GameManager();                                   // Base
    GameManager(int _mapX_Bound, int _mapY_Bound);   // Initialise the game with a generated map of predetermined size.
    GameManager(vector<vector<char>> _map);          // Initialise the game with a fixed map.

    // Game Settings
    bool canSpawnEnemies = true;
    bool canSpawnBoxes = true;
    bool canGenerateBoxes = true;
    bool canGenerateEnemies = true;

    // Game Functions - Capitalised at start of function name to indicate importance.
    void Start();                                                  // Start the game.
    void Start(int _playerX, int _playerY);       // Start the game with the player at a specific point.
    void Start_Debug();
    bool GameLoop();                                // What happens every game turn

    // Spawn Functions
    void spawnPlayer();
    void spawnPlayer(int _x, int _y);
    void spawnEnemy();                              // Enemy Spawn at Random Location
    void spawnEnemy(int _x, int _y);                // At Fixed Location
    void spawnBox();                                // Box Spawn at Random Location
    void spawnBox(int _x, int _y);                  // At Fixed location

    // Player Reference - Exposing this value so that the GameManager's player can be modified.
    // Prevents constant getting and setting of player.
    Player *player;

    // Deconstructor
    void flushEnemies();
    void flushBoxes();
    ~GameManager();
private:
    // Game Variables
    vector<vector<char>> map;
    int duration = 0;                                   // Game Time / Number of steps made by Player
    double difficultyModifier;

    vector<Enemy*> enemies;
    vector<Box*> boxes;

    // Customizable Gameplay Functions
    void Setup(bool quickStart);
    void MapSizeSet(bool forceGeneration);
    void NameCharacter();
    void SelectDifficulty();

    // Game Functions
    void EnemyFunction();
    void BoxFunction();
    void GameOver();

    // GameLoop generation over time
    void GameLoop_generateBox();
    int generateBoxDelayCurrent = GameManager_configuration[5];
    void GameLoop_generateEnemy();
    int generateEnemyDelayCurrent = GameManager_configuration[3];
    int generateEnemyAsBossDelayCurrent = GameManager_configuration[7];

    // Map Variables and Functions
    int mapX_Bound;
    int mapY_Bound;
    void generateMap();
    void generateMap(int _mapX_Bound, int _mapY_Bound); // Set map bounds are ignored; generating map with specified size.
    void generateMapObjects();

    // Miscellanious
    int getRandomInt(int upperBound);               // Upper bound is not inclusive.
    int getRandomInt(int min, int max);             // Upper bound is not inclusive.
    double getCurrentModifier();
    bool checkValidUserInput();

    // Settings Variables - Made for readability
    // Not constant due to Custom Start
    int mapSizeMin = 500;
    int mapSizeMax = 1500;

    int initialPowerUpPercentCount = 10;
    int initialMonsterPercentCount = 2;

    int spawnPowerUpDelay = 10;
    int spawnMonsterDelay = 2;

    int monsterDropPowerUpChance = 5;
    int spawnMonsterBossSpawnDelay = 20;

    // Readability Enumeration
    enum StartOption {
        Invalid,
        QuickStart,
        CustomStart,
        Help,
        Exit,
    };

    enum Settings {
        InvalidSetting,
        MapWidth,
        MapHeight,
        InitialPowerupCount,
        InitialMonsterCount,
        PowerupSpawnInterval,
        MonsterSpawnInterval,
        MonsterDropChance,
        MonsterBossSpawnDelay,
        StartGame,
    };
};

#endif // GAMEMANAGER_H