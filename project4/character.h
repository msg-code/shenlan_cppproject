#ifndef CHARACTER_H
#define CHARACTER_H
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include"weapon.h"

class character
{
private:
    typedef std::pair<int, unsigned int> pii;
    std::string m_name;
    int current_HP;
    int max_HP;
    int attack;
    int exper;
    int max_exper;
    std::vector<weapon> epuip_weapon;
    std::vector<std::pair<int, unsigned int>> buff;
    std::vector<std::pair<int, unsigned int>> debuff;
public:
    character(std::string name, int cur_hp, int max_hp, int atk, int exp = 0,int max_exp = 0):
        m_name(name), current_HP(cur_hp), max_HP(max_hp), attack(atk), exper(exp), max_exper(max_exp){

        }
    inline bool checkIsLive();
    inline int getHp();
    inline int getMaxHp();
    inline int getAttack();
    inline int getExper();
    inline int getMaxExper();
    inline void setExper(int exp);
    inline void setHp(int hp);
    inline void setAddHp(int addHp);
    inline void setDeHp(int deHp);
    inline void setAddAttack(int atk);
    void addBuff();
    void triggerBuff();
    void addDebuff();
    void triggerDebuff();
    void clearAllBuff();
    void beat(int monster_num);
    void beat_trap();
    void beat_learder();
    void beat_weapon();
    void weapon_check();
    void weapon_attack_end();
    // bool judgeMonsterLive(std::vector<character>& monster);
    // ~character();
};

inline bool character::checkIsLive(){
    if(current_HP<=0){
        return false;
    }
    return true;
}
inline int character::getHp(){
    return current_HP;
}
inline int character::getMaxHp(){
    return max_HP;
}
inline int character::getAttack(){
    return attack;
}
inline int character::getExper(){
    return exper;
}
inline int character::getMaxExper(){
    return max_exper;
}
inline void character::setExper(int exp){
    exper = exp;
}
inline void character::setHp(int hp){
    current_HP = hp;
}
inline void character::setAddHp(int addHp){
    current_HP += addHp;
    current_HP = std::min(current_HP, max_HP);
}
inline void character::setDeHp(int deHp){
    current_HP -= deHp;
}
inline void character::setAddAttack(int atk){
    attack += atk;
}
// character::~character()
// {
// }

#endif