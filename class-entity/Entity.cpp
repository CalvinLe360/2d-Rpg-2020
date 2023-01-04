#include "Entity.h"
#include <iostream>
#include <cmath>
using namespace std;

// Libraries specifically required for Random Number Generation
#include <stdlib.h>
#include <time.h>

// ------------
// Constructors
// ------------

// Initialises all the variables of the entity.
void Entity::Initialiser_Entity(){
    name = "";

    // Default Stats
    healthMax = 1.0;
    attack = 0.5;
    defence = 0.1;

    healthCurrent = healthMax; // Must be done during construction, else they would not have any health.
    level = 1;
    attackRange = 1.0;

    // Because their coordinates are not specified in this constructor,
    // We have to default their values to the top left corner of the map.
    x = 0;
    y = 0;
}

Entity::Entity(){
    Initialiser_Entity();
}

// Uses base constructor to set up initial values,
// Then sets their starting location to a specific point on the map.
Entity::Entity(int _x, int _y){
    Initialiser_Entity();

    x = _x;
    y = _y;
}

// Sets level of entity after placing them on the map.
Entity::Entity(int _x, int _y, int _level){
    Initialiser_Entity();

    x = _x;
    y = _y;
    level = _level;
}

// ------------
// Active Functions - Used constantly within the game state
// ------------

// Uses a formula to calculate the damage.
// Damage dealt = Attack * (Attack/(Attack + Defence))
// Rounds to two decimal places
double Entity::getAttackDamage(Entity target){
    double attackerDamage = getAttack();
    double targetDefence = target.getDefence();

    // Damage after calculation
    double currentDamage = attackerDamage * (attackerDamage/(attackerDamage + targetDefence));

    int finalDamage = (int)(currentDamage * 100 + .5);
    return (double)finalDamage / 100;
}

// Applies damage to this entity without a known attacker
void Entity::applyDamage(double attackerDamage){
    cout << getName() << " was hurt for " << attackerDamage << " damage! (" << getHealth() - attackerDamage << "/" << getMaxHealth() << ")" << endl;
    setHealth(getHealth() - attackerDamage);
}

// Applies damage to this entity with a known attacker
void Entity::applyDamage(double attackerDamage, Entity attacker){
    cout << getName() << " was attacked by " << attacker.getName() << " for " << attackerDamage << " damage! (" << getHealth() - attackerDamage << "/" << getMaxHealth() << ")" << endl;
    setHealth(getHealth() - attackerDamage);
}

// Heals the entity by the smaller of the amount in the parameter,
// Or the difference between the current and max health.
void Entity::applyHealing(double heal){
    double currentHealthLost = getMaxHealth() - getHealth();
    double healing = min(currentHealthLost, heal);               // Calculation happens here

    if(healing != 0) cout << getName() << " was healed for " << healing << " HP." << endl;
    setHealth(getHealth() + healing);
}

// a^2 + b^2 = c^2 --- Distance formula
double Entity::getDistanceFromEntity(Entity target){
    double distance = sqrt(pow(getX() - target.getX(), 2) + pow(getY() - target.getY(), 2));
    return distance;
}

// Bundles functions together to make an attack.
void Entity::PerformAttack(Entity *target){
    if(target == NULL) {
        cout << "Error! PerformAttack was called on a null target!" << endl;
        return;
    }

    outputAttackMessage(target);
    target -> applyDamage(getAttackDamage(*target));
    //target -> applyDamage(getAttackDamage(*target), *this);
}

void Entity::outputAttackMessage(Entity *target){
    cout << "outputAttackMessage not defined for Entity." << endl;
}

// ------------
// Get/Set Functions
// ------------
string Entity::getName(){
    return name;
}

int Entity::getX(){
    return x;
}

int Entity::getY(){
    return y;
}

int Entity::getLevel(){
    return level;
}

double Entity::getHealth(){
    return healthCurrent;
}

double Entity::getMaxHealth(){
    return healthMax;
}

double Entity::getAttack(){
    return attack;
}

double Entity::getDefence(){
    return defence;
}

void Entity::setName(string newName){
    name = newName;
}

void Entity::setX(int _x){
    x = _x;
}

void Entity::setY(int _y){
    y = _y;
}

void Entity::setHealth(double newHealth){
    healthCurrent = newHealth;
}

void Entity::setMaxHealth(double newMaxHealth){
    healthMax = newMaxHealth;
}

void Entity::setAttack(double newAttack){
    attack = newAttack;
}

void Entity::setDefence(double newDefence){
    defence = newDefence;
}

// ------------
// Math Functions
// ------------
// Returns an integer between 0 (inclusive) and the upper bound (exclusive)
int Entity::getRandomInt(int upperBound){
    return rand() % upperBound;
}

// Returns an integer between min and max (both inclusve)
int Entity::getRandomInt(int min, int max){
    return min + rand() % (max - min + 1);
}

// ------------
// Deconstructor
// ------------
Entity::~Entity(){

}

// ------------
// If I don't put this in, the compiler will get angry
// ------------
void Entity::Move(){

}