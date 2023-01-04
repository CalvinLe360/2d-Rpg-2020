#include "../maps/fixed_map.h"
#include "../class-game-entity/GameManager.h"
int main(){
    fixed_map test_map;
    GameManager testgame = GameManager(test_map.get_map());
    testgame.Start_Debug();
    bool alive = true;

    // spawn 5 boxes
    for(int i = 0 ; i < 5; i++){
        testgame.spawnBox();
    }

    while(alive){
        alive = testgame.GameLoop();
    }
}