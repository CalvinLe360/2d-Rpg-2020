#include "../maps/fixed_map.h"
#include "../class-game-entity/GameManager.h"
#include <iostream>
#include <cmath>
int main(){
    int numTests = 0;
    int numSucceeded = 0;

    // Experience Test Cases
    {
        numTests++;
        fixed_map test_map;
        GameManager testgame = GameManager(test_map.get_map());
        testgame.Start_Debug();

        testgame.GameLoop();
        testgame.player -> gainExperience(100);

        if(testgame.player -> getExperience() == 100) numSucceeded++;
        else cout << "Test Failure" << endl;

    }

    {
        numTests++;
        fixed_map test_map;
        GameManager testgame = GameManager(test_map.get_map());
        testgame.Start_Debug();

        testgame.GameLoop();
        testgame.player -> gainExperience(500);

        if(testgame.player -> getExperience() == 500) numSucceeded++;
        else cout << "Test Failure" << endl;

    }

    {
        numTests++;
        fixed_map test_map;
        GameManager testgame = GameManager(test_map.get_map());
        testgame.Start_Debug();

        testgame.GameLoop();
        testgame.player -> gainExperience(-100);

        if(testgame.player -> getExperience() == -100) numSucceeded++;
        else cout << "Test Failure" << endl;

    }

    {
        numTests++;
        fixed_map test_map;
        GameManager testgame = GameManager(test_map.get_map());
        testgame.Start_Debug();

        testgame.GameLoop();
        testgame.player -> gainExperience(1234567890);

        if(testgame.player -> getExperience() == 1234567890) numSucceeded++;
        else cout << "Test Failure" << endl;

    }

    {
        numTests++;
        fixed_map test_map;
        GameManager testgame = GameManager(test_map.get_map());
        testgame.Start_Debug();

        testgame.GameLoop();
        testgame.player -> gainExperience(0);

        if(testgame.player -> getExperience() == 0) numSucceeded++;
        else cout << "Test Failure" << endl;
    }

    // Level Tests
    // level = (-1 + sqrt(1 + 8xp/10))/2

    {
        numTests++;
        fixed_map test_map;
        GameManager testgame = GameManager(test_map.get_map());
        testgame.Start_Debug();

        testgame.GameLoop();
        testgame.player -> gainExperience(10);

        if(testgame.player -> getCurrentLevel() == 1) numSucceeded++;
        else cout << "Test Failure" << endl;

    }

    {
        numTests++;
        fixed_map test_map;
        GameManager testgame = GameManager(test_map.get_map());
        testgame.Start_Debug();

        testgame.GameLoop();
        testgame.player -> gainExperience(30);

        if(testgame.player -> getCurrentLevel() == 2) numSucceeded++;
        else cout << "Test Failure" << endl;

    }

    {
        numTests++;
        fixed_map test_map;
        GameManager testgame = GameManager(test_map.get_map());
        testgame.Start_Debug();

        testgame.GameLoop();
        testgame.player -> gainExperience(120);

        if(testgame.player -> getCurrentLevel() == 4) numSucceeded++;
        else cout << "Test Failure" << endl;

    }

    {
        numTests++;
        fixed_map test_map;
        GameManager testgame = GameManager(test_map.get_map());
        testgame.Start_Debug();

        testgame.GameLoop();
        testgame.player -> gainExperience(1000);

        if(testgame.player -> getCurrentLevel() == 13) numSucceeded++;
        else cout << "Test Failure" << endl;

    }


    cout << "Tests Finished!" << endl;
    cout << numSucceeded << "/" << numTests << " succeeded!" << endl;
    cout << "Regression Test:" << endl;

    {
        fixed_map test_map;
        GameManager testgame = GameManager(test_map.get_map());
        testgame.Start_Debug();
        bool alive = true;

        while(alive){
            testgame.player -> gainExperience(100);
            alive = testgame.GameLoop();
        }
    }
}