#include "../maps/fixed_map.h"
#include "../class-game-entity/GameManager.h"
int main(){
    fixed_map test_map;
    GameManager testgame = GameManager(test_map.get_map());
    testgame.Start_Debug();
    testgame.canSpawnEnemies = true;
    bool alive = true;

    testgame.spawnEnemy();
    while(alive){
        alive = testgame.GameLoop();
    }
}