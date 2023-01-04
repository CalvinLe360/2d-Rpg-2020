#ifndef ENTITY_H
#define ENTITY_H

#include <string>
using namespace std;

class Entity {
public:
    // Constructors
    void Initialiser_Entity();          // Initialises all variables.
    Entity();                           // Base Constructor
    Entity(int _x, int _y);             // Constructor with specified spawning coordinates
    Entity(int _x, int _y, int _level); // Previous Constructor with Level Parameter

    // Various Entity Functions
    double getAttackDamage(Entity target);                      // Calculates damage, taking the target's defence into account.
    void applyDamage(double attackerDamage);                    // Default damage function, prints a message.
    void applyDamage(double attackerDamage, Entity inflictor);  // Damage function that uses the attacker as the source of damage.
    void applyHealing(double heal);
    double getDistanceFromEntity(Entity target);
    void PerformAttack(Entity *target);

    // Get/Set Functions
    string getName();
    int getX();
    int getY();
    int getLevel();

    double getHealth();
    double getMaxHealth();
    double getAttack();
    double getDefence();

    void setName(string newName);
    void setX(int _x);
    void setY(int _y);

    void setHealth(double newHealth);
    void setMaxHealth(double newMaxHealth);
    void setAttack(double newAttack);
    void setDefence(double newDefence);

    // Move Function, implemented in classes that inherit the Entity Class
    void Move();

    // Deconstructor
    ~Entity();

protected:
    // Meta Information
    string name;

    // Location Variables
    int x;
    int y;

    // Primary Attributes
    double healthMax;
    double attack;
    double defence;

    double healthCurrent;
    int level;
    double attackRange;

    // Math Functions
    int getRandomInt(int upperBound);
    int getRandomInt(int min, int max);

    // Implemented in child classes to provide different flavour for their attacks.
    virtual void outputAttackMessage(Entity *target);
};

#endif // ENTITY_H