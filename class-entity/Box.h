#ifndef BOX_H
#define BOX_H

#include "Entity.h"
#include <vector>

// Forward declaration in order to use other classes while said classes use this class.
class Player;

class Box : public Entity {
public:
    // Initialisers
    void Initialiser_Box(Player *_player, int _x, int _y);
    Box(Player *_player, int _x, int _y);   // Needs pointer to player to apply buffs directly to
    //Box(Player *_player, int _x, int _y, double _modifier);   // Added modifier parameter to modify the effectiveness of the box pickup.
    void setPlayer(Player *_player); // Boxes created during set up are pointing to null. Use this to re-set the player pointer.

    // Transfers boosts from box to player.
    void powerupGive(double _modifier);

private:
    vector<int> powerupList;
    Player *player;

    // Box configuration settings
    const int minBoostCount = 1;
    const int maxBoostCount = 5;

    // Calculates how much boosts this box should contain
    // and insert them.
    void powerupContain(double modifier);
};

#endif