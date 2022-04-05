#ifndef WEAPON_H
#define WEAPON_H
#include<iostream>

class weapon
{
private:
    /* data */
    int attack;
    int endurance;
    int weapon_id;
public:
    weapon(int a, int e, int w_id): attack(a), endurance(e), weapon_id(w_id){

    };
    weapon& operator = (weapon& w){
        attack = w.attack;
        endurance = w.endurance;
        weapon_id = w.weapon_id;
        return *this;
    }
    inline bool checkIsDamage(){
        return endurance <= 0? : true,false;
    }
    inline int getAttack();
    inline int getweaponId();
    inline int getEndurance();
    inline void setAttack();
    inline void setEndurance(int end);
    inline void generate_weapon(int id);
    // ~weapon();
};

// weapon::weapon(/* args */)
// {
// }
inline int weapon::getAttack(){
    if(weapon_id == 2){
        attack = endurance;
    }
    return attack;
}
inline int weapon::getweaponId(){
    return weapon_id;
}
inline int weapon::getEndurance(){
    return endurance;
}
inline void weapon::setAttack(){
    attack = attack * 2;
}
inline void weapon::setEndurance(int end){
    endurance = end;
}
// 按照id生成武器属性
inline void weapon::generate_weapon(int id){
    if(id == 1){
        attack = 4;
        endurance = 6;
        weapon_id = id;
    }else if(id == 2){
        endurance = 6;
        attack = endurance;
        weapon_id = id;
    }else{
        attack = 1;
        endurance =6;
        weapon_id = id;
    }
}
// weapon::~weapon()
// {
// }


#endif