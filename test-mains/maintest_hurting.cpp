#include "../maps/fixed_map.h"
#include "../class-game-entity/GameManager.h"
#include <iostream>

int main(){
    int numTests = 0;
    int numSuccesses = 0;

    {
        numTests++;
        fixed_map test_map;
        GameManager testgame = GameManager(test_map.get_map());
        testgame.Start_Debug();

        testgame.player -> applyDamage(1);
        if(testgame.player -> getCurrentHealthLost() == 1) numSuccesses++;
        else cout << "Test Failure" << endl;
    }

    {
        numTests++;
        fixed_map test_map;
        GameManager testgame = GameManager(test_map.get_map());
        testgame.Start_Debug();

        testgame.player -> applyDamage(testgame.player -> getMaxHealth() / 2); // halve the health
        if(testgame.player -> getCurrentHealthLost() == testgame.player -> getHealth()) numSuccesses++;
        else cout << "Test Failure" << endl;
    }

    {
        numTests++;
        fixed_map test_map;
        GameManager testgame = GameManager(test_map.get_map());
        testgame.Start_Debug();

        testgame.player -> applyDamage(5);
        if(testgame.player -> getCurrentHealthLost() == 5) numSuccesses++;
        else cout << "Test Failure" << endl;
    }

    {
        numTests++;
        fixed_map test_map;
        GameManager testgame = GameManager(test_map.get_map());
        testgame.Start_Debug();

        testgame.player -> applyDamage(40);
        if(testgame.player -> getCurrentHealthLost() == 40) numSuccesses++;
        else cout << "Test Failure" << endl;
    }

    {
        numTests++;
        fixed_map test_map;
        GameManager testgame = GameManager(test_map.get_map());
        testgame.Start_Debug();

        testgame.player -> applyDamage(testgame.player -> getMaxHealth()); // lose all health
        if(testgame.player -> getCurrentHealthLost() == testgame.player -> getMaxHealth()) numSuccesses++;
        else cout << "Test Failure" << endl;
    }


    cout << "Tests Finished!" << endl;
    cout << numSuccesses << "/" << numTests << " succeeded!" << endl;
    cout << "Regression Test:" << endl;

    {
        fixed_map test_map;
        GameManager testgame = GameManager(test_map.get_map());
        testgame.Start_Debug();
        bool alive = true;

        while(alive){
            testgame.player -> applyDamage(1);
            alive = testgame.GameLoop();
        }
    }
}