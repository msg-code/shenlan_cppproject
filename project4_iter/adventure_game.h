#ifndef ADVENTURE_GAME_H
#define  ADVENTURE_GAME_H

#include<iostream>
#include<algorithm>
#include<unistd.h>
#include"room.h"
#include"weapon.h"
#include"Endl.h"
class adventure_game
{
private:
    /* data */
    enum room_type{
        Campsite = 1,
        Common_room,
        Trap_room,
        Leader_room,
        Weapon_room
    };
    int sum_inroom = 0;
    int inroom[5]={0, 0 ,0 , 0, 0};

public:
    // adventure_game();
    adventure_game()
    {
    std::cout << "welcome to adventure game!" << Endl{}; 
    }
    // void game_run();

    // void test();
    // ~adventure_game();
};

// adventure_game::adventure_game()
// {
//     std::cout << "welcome to adventure game!" << std::endl; 
// }

// adventure_game::~adventure_game()
// {
// }
#endif