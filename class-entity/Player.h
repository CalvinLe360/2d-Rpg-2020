#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <vector>
using namespace std;

// Forward declaration in order to use other classes while said classes use player class.
class Enemy;
class Box;

// In-game flavour text for the player's actions
static vector<string> playerAttackActions = {
    "stabs",
    "shoots",
    "bashes",
    "casts a fireball towards",
    "destroys",
    "pummels",
    "combusts",
};

static vector<string> playerWaitActions = {
    "watches the watch tick by...",
    "tactically stands in a single spot.",
    "starts daydreaming.",
};

class Player : public Entity {
public:
    // Constructors
    void Initialiser_Player();                  // Constructors interact strangely when initialising base values and calling each other, thus this function is executed.
    Player();                                   // Base Constructor
    Player(int _x, int _y);                     // Constructor with initialised coordinates.
    Player(int _x, int _y, int _potionCount);   // Constructor with added potions.

    // Player Functions
    void gainExperience(int experienceCount);
    void recalculateStats();                    // Recalculates stats based on the base stats and boosts collected.
    void recalculateAttackRange();              // Recalculates attack range based on level.
    void powerUp(int boostType, int boostCount);

    // Move function receives an input command from the user.
    // Requires much of the game state
    void Move(int mapX_Bound, int mapY_Bound, vector<vector<char>> map);

    // Get / Set
    int getExperience();
    int getCurrentLevel();
    double getCurrentHealthLost();

    void setEnemiesPointer(vector<Enemy*> *_enemies);
    void setBoxesPointer(vector<Box*> *_boxes);

protected:
    // Player-exclusive variables
    int experience;
    int potionCount;
    int sightRadius;

    // Pointers to directly refer to them in functions.
    vector<Enemy*> *enemies;
    vector<Box*> *boxes;

    // Names of Boosts in enum to provide better readability
    enum boostType {
        maxHealth,
        attack,
        defence,
    };

    // Base stats, to be modified by stat powerups.
    double baseMaxHealth;
    double baseAttack;
    double baseDefence;

    int boostMaxHealth;
    int boostAttack;
    int boostDefence;

    // Hidden functions that are executed by other functions
    void levelCheck();                  // Checks if the experience gathered is enough to obtain a higher level.
    void levelUpgrade(int newLevel);

    // Move outcomes - If they fail, return false, else return true.
    bool moveMovement(char direction, int mapX_Bound, int mapY_Bound);
    bool moveAttack();
    bool movePotion();
    bool moveWait();
    bool moveDie();

    // Misc Functions
    void getVision(int mapX_Bound, int mapY_Bound, vector<vector<char>> map);
    void getPlayerStatus();
    virtual void outputAttackMessage(Entity *target);

    // Move Enum
    enum playerValidCommandsEnum {
        Up,
        Left,
        Down,
        Right,
        Attack,
        DrinkPotion,
        Wait,
        GetPlayerStats,
        Suicide,
        Help
    };

    const double healthGain = 5.0;
    const double attackGain = 1.15;
    const double defenceGain = 0.1;
};

// The Move function reads from this vector and stores its index.
static vector<string> playerValidCommands = {
    "w",
    "a",
    "s",
    "d",
    "attack",
    "drink",
    "wait",
    "stats",
    "die",
    "help",
};

#endif // PLAYER_H