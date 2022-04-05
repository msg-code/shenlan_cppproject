#include"adventure_game.h"
#include<iostream>
// #include<algorithm>
#include<time.h>
#include<random>

void adventure_game::game_run(){
    character explorer("explorer", 100, 100, 10, 0, 10);
    int in_probaility[100];
    for(int i = 0; i < 100; ++i){
        if(i < 10){
            in_probaility[i] = 1;
        }else if(i < 65){
            in_probaility[i] = 2;
        }else if(i < 80){
            in_probaility[i] = 3;
        }else if(i < 90){
            in_probaility[i] = 4;
        }else{
            in_probaility[i] = 5;
        }   
    }
    srand(time(0));

    while(true){
        int begin = rand() % 100;
        int r = 0; //随机数
        // std::cout<< "welcome!" << begin<<std::endl;
        switch (in_probaility[begin])
        {
        case Campsite:
            std::cout << "进入营地" << std::endl;
            sleep(1);
            explorer.setHp(explorer.getMaxHp()); //恢复全部生命值
            std::cout << "冒险者" <<"(" << explorer.getHp() << "/" << explorer.getMaxHp() << ")" << std::endl;
            inroom[0]++;
            break;
        case Common_room: 
            std::cout << "进入普通房间" << std::endl;
            sleep(1);
            explorer.triggerBuff();
            explorer.triggerDebuff();
            explorer.addBuff();
            r = rand()%100;
            if(in_probaility[r] == 1){
                explorer.setHp(std::min(explorer.getHp() + 10,explorer.getMaxHp()));
                std::cout << "触发事件，回复10点生命，获得持续恢复效果，当前生命（" << explorer.getHp() << "/" << explorer.getMaxHp()<< ")"<<std::endl;
            }
            r = rand() % 3 +1;
            explorer.beat(r);
            inroom[1]++;
            break;
        case Trap_room: 
            std::cout << "进入陷阱房间" << std::endl;
            sleep(1);
            explorer.triggerBuff();
            explorer.triggerDebuff();
            explorer.addDebuff();
            explorer.setDeHp(explorer.getHp() / 10);
            std::cout << "触发事件，损失" << explorer.getHp() / 10 <<"点生命，造成持续损伤，当前生命（" << explorer.getHp() << "/" << explorer.getMaxHp()<< ")"<<std::endl;
            explorer.beat_trap();
            inroom[2]++;
            break;
        case Leader_room: 
            std::cout << "进入首领房间" << std::endl;
            sleep(1);
            explorer.triggerBuff();
            explorer.triggerDebuff();
            explorer.setAddHp(20);
            std::cout << "生命恢复， 当前生命（" << explorer.getHp() << "/" << explorer.getMaxHp() << ")" << std::endl;
            explorer.clearAllBuff();
            explorer.beat_learder();
            inroom[3]++;
            break;
        case Weapon_room:
            std::cout << "进入武器房间" << std::endl;
            sleep(1);
            explorer.triggerBuff();
            explorer.triggerDebuff();
            explorer.beat_weapon();
            inroom[4]++;
            break;
        default:
            break;

        }
        sum_inroom++;
        if(!explorer.checkIsLive()){
            std::cout << "探险者死亡" << ",一共走过"<< sum_inroom <<"个房间," << "普通房间："<<inroom[1] << " ,陷阱房间："<<inroom[2]
            << " ,武器房间："<< inroom[4]<< " ,首领房间："<< inroom[3]<< " ,营地：" << inroom[0] << std::endl;
            break;
        }
    }
}