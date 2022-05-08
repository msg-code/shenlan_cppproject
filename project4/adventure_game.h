#ifndef ADVENTURE_GAME_H
#define  ADVENTURE_GAME_H

#include<iostream>
#include<algorithm>
#include<memory>
#include<unistd.h>
#include"character.h"
#include"weapon.h"

struct Endl{

};
inline std::ostream& operator<<(std::ostream& out, const Endl&){
    sleep(10);
    std::cout << std::endl;
    return std::cout;
}
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
    void game_run();
    std::vector<std::shared_ptr<character>> vec;
    void test();
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