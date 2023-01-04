#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include <vector>
using namespace std;

// Forward declaration in order to use player class while player class is using enemy class
class Player;

// Implementation of flavour in-game
static vector<string> enemyTypes = {
    "Zombie",
    "Skeleton",
    "Spider",
    "Adventurer",
    "Bandit",
    "Ogre",
    "Wolf",
    "Bird",
};

static vector<string> enemyAttackActions = {
    "bites",
    "bludgeons",
    "claws",
    "breaks",
    "kicks",
};

class Enemy : public Entity {
public:
    // Constructors
    void Initialiser_Enemy(Player *_player, double modifier);    // Constructors interact strangely when initialising base values and calling each other, thus this function is utilised.
    Enemy(Player *_player);                                      // Base Constructor
    Enemy(Player *_player, int _x, int _y);                      // Constructor with initialised coordinates.
    Enemy(Player *_player, int _x, int _y, double _modifier);    // Constructor with scaling modifier.

    // Enemy functions
    void Move();                                                 // Code that represents an enemy's actions each turn.
    void Step();                                                 // Moves the enemy closer to the player.

    // Enemies can be labled as bosses.
    bool getIsBoss();
    void setIsBoss(bool _isBoss);

    // Deconstructor
    ~Enemy();
private:
    // Actions are resolved with the player by pointing to the actual player object.
    Player *player;

    // Enemy Functions
    void constructStats();
    virtual void outputAttackMessage(Entity *target);

    // Boss Identifier - Initially not a boss.
    bool isBoss = false;

    // Math functions
    double getRandomStrength();                                 // Enemy stats are randomised even further with this function

    // Base attributes
    const double enemyBaseHealth = 1.75;
    const double enemyBaseAttack = 0.45;
    const double enemyBaseDefence = 0.025;
    const double enemyAggroDistance = 10;
    const double enemyFarMovementChance = 10;
};

#endif // ENEMY_H