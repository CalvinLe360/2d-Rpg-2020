#include "../maps/fixed_map.h"
#include "../class-game-entity/GameManager.h"
int main(){
    fixed_map map;

    while(true){
        GameManager game = GameManager(map.get_map());
        game.Start();
        bool alive = true;

        while(alive){
            alive = game.GameLoop();
        }
    }

}