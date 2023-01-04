#include "Box.h"
#include "Player.h"
#include <iostream>

// Libraries specifically required for Random Number Generation
#include <stdlib.h>
#include <time.h>

void Box::Initialiser_Box(Player *_player, int _x, int _y){
    player = _player;
    setX(_x);
    setY(_y);

    // Set up randomer for buffs..
    // As long as GameManager has srand, this is not required.
    // srand(time(NULL));
}

Box::Box(Player *_player, int _x, int _y){
    Initialiser_Box(_player, _x, _y);
}

void Box::setPlayer(Player *_player){
    player = _player;
}

// ----
// Buff Process
// Boxes will not contain anything until the player picks it up.
// ----

void Box::powerupGive(double _modifier){
    cout << player -> getName() << " opens a box of powerups!" << endl;
    powerupContain(_modifier);
    for(int i = 0; i < powerupList.size(); i++){
        player -> powerUp(i, powerupList[i]);
    }
}

void Box::powerupContain(double _modifier){
    // Reset the amount of buffs in this crate.
    powerupList = {0,0,0};

    // Powerup count is randomised and boosted with given modifier.
    double powerupCount = getRandomInt(minBoostCount, maxBoostCount);
    powerupCount *= 1 + _modifier;

    for(int i = 0; i < powerupCount; i++){
        powerupList[rand() % powerupList.size()]++;
    }
}