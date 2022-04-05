#ifndef ROLE_H
#define ROLE_H
#include<iostream>
#include<memory>
#include<vector>
#include<queue>
#include<algorithm>
#include"weapon.h"
#include"Endl.h"

class role
{
private:
    typedef std::pair<int, unsigned int> pii;
    std::string m_name;
    std::pair<int, const int> health;
    int attack;
    std::pair<int, const int> exp;
    std::unique_ptr<weapon> w;
    std::vector<std::pair<int, unsigned int>> buff;
    std::vector<std::pair<int, unsigned int>> debuff;
public:
    role(std::string name, std::pair<int, const int> h, std::pair<int, const int> e,int atk):
        m_name(name), health(h), exp(e), attack(atk)
    {

    }

    void beat(role& r);
    void beat(std::vector<role>& r);
    int atkEvaluate();
    // ~character();
};


class Boss : public role
{
public:
    int atkEvaluate();
};
// character::~character()
// {
// }

#endif