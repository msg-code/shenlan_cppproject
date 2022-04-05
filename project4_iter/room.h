#ifndef ROOM_H
#define ROOM_H
#include<iostream>
#include<string>
#include<vector>
#include"role.h"
#include"weapon.h"
#include"Endl.h"
class room
{
private:
    /* data */
    virtual void enterEvent(role& r);
    virtual std::vector<std::unique_ptr<role>> genMonster();
    virtual void extSettlement(role& r);
public:
    std::string room_name;
    void interacton(role& r);
    void battle();
    room(/* args */);
    ~room();
};


class Camp : public room
{
private:
    void enterEvent(role& r);
};

class TrivialRoom : public room
{
private:
    void enterEvent(role& r);
    std::vector<std::unique_ptr<role>> genMonster();
};

class TrapRoom : public room
{
private:
    void enterEvent(role& r);
    std::vector<std::unique_ptr<role>> genMonster();
};

class BossRoom : public room
{
private:
    void enterEvent(role& r);
    std::vector<std::unique_ptr<role>> genMonster();
};

class WeaponRoom : public room
{
private:
    weapon w;
    void enterEvent(role& r);
    std::vector<std::unique_ptr<role>> genMonster();
    void extSettlement(role& r);
};
#endif