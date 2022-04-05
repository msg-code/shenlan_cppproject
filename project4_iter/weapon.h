#ifndef WEAPON_H
#define WEAPON_H
#include<iostream>

class weapon
{
public:
    std::string weapon_name;
    int attack;
    int durability;

    weapon(std::string w_name, int a, int dur): weapon_name(w_name), attack(a), durability(dur){

    };
    virtual void atkEvaluate();
    // ~weapon();
};


class weapon2 : public weapon

{
private:
    /* data */
public:
    // weapon2 (std::string w_name, int a, int dur) :weapon(w)
    // ;
    void atkEvaluate();
};

class weapon3 : public weapon

{
private:
    /* data */
public:

    void atkEvaluate();
};
// weapon::weapon(/* args */)
// {
// }
// weapon::~weapon()
// {
// }


#endif