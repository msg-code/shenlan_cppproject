#include<iostream>
#include"character.h"

// 增加持续恢复buff
void character::addBuff(){
    pii b{5,2};
    buff.emplace_back(b);
}
// 触发恢复buff（可叠加）
void character::triggerBuff(){
    int sum_hp = 0;
    if(!buff.empty()){
        for(auto it = buff.begin();it < buff.end(); ++it){
            int ori_hp = current_HP;
            current_HP = std::min(max_HP, current_HP + it->first);
            sum_hp += current_HP - ori_hp;
            it->second --;
        }
        for(auto it = buff.begin();it < buff.end(); ++it){
            if(it->second<=0) buff.erase(it);
        }
        std::cout << "持续恢复效果触发，获得"<< sum_hp << "点生命值，当前生命值（" << current_HP << "/"<< max_HP<<")"<<std::endl;
    }

}
// 增加损伤buff
void character::addDebuff(){
    pii b{2,5};
    debuff.emplace_back(b);
}
// 触发持续损伤buff
void character::triggerDebuff(){
    int sum_hp = 0;
    if(!debuff.empty()){
        for(auto it = debuff.begin();it < debuff.end(); ++it){
            current_HP = current_HP - it->first;
            sum_hp += it->first;
            it->second --;
        }
        for(auto it = debuff.begin();it < debuff.end(); ++it){
            if(it->second<=0) debuff.erase(it);
        }
        std::cout << "持续损伤效果触发，失去"<< sum_hp << "点生命值，当前生命值（" << current_HP << "/"<< max_HP<<")"<<std::endl;
    }
}
// 进入首领房间清除所有buff
void character::clearAllBuff(){
    if(!buff.empty())
    {
        std::cout << "持续恢复效果被移除" << std::endl;
        buff.clear();
    }
    if(!debuff.empty()){
        std::cout << "持续损伤效果被移除" << std::endl;
        debuff.clear();
    }
    
}
// 普通房间战斗
void character::beat(int monster_num){
    std::vector<character> monster;
    std::vector<int> index_monster; 
    // 随机生成1-3个怪物
    for(int i = 0; i < monster_num; ++i){
        int x = rand()%40;
        int y = rand()%2; //正负增益
        if(y ==1){
            int cur_hp = 10 * (100 + x) / 100;
            int max_hp = cur_hp;
            int atk = 5 * (100 + x) / 100;
            std::string monster_name = "moster" + std::to_string(i+1); 
            monster.push_back(character(monster_name,cur_hp, max_hp, atk));    
        }else{
            int cur_hp = 10 * (100 - x) / 100;
            int max_hp = cur_hp;
            int atk = 5 * (100 - x) / 100;
            std::string monster_name = "moster" + std::to_string(i+1); 
            monster.push_back(character(monster_name,cur_hp, max_hp, atk));
        }
        
    }

    auto my_cmp = [&](const pii& a,const pii& b){
        return a.second > b.second;
    };
    std::vector<pii> monsterAttack;
    for(int i = 0; i < monster_num; ++i){
        std::cout<< "遇到怪物" << i+1 << "(" << monster[i].getHp()<<"/"<<monster[i].getMaxHp()<<") ";
        monsterAttack.push_back({i,monster[i].getAttack()});
    }
    // 按攻击力排序
    sort(monsterAttack.begin(), monsterAttack.end(), my_cmp);
    // 战斗开始，先对拥有武器判断，攻击后检查武器是否损坏
    std::cout<<"\n"<<"战斗开始"<<std::endl;
    int defeat_num = 0;
    while(!monsterAttack.empty()){
        weapon_check();
        pii cur = monsterAttack[0];
        if(!epuip_weapon.empty()){
            monster[cur.first].setDeHp(attack + epuip_weapon[0].getAttack());
            std::cout << "探险者攻击怪物" << cur.first + 1 << "造成" << attack + epuip_weapon[0].getAttack()<< "点伤害, 怪物" <<  cur.first+1 
            << "(" << monster[cur.first].getHp()<<"/"<<monster[cur.first].getMaxHp()<<") "<< std::endl;
        }else{
            monster[cur.first].setDeHp(attack);
            std::cout << "探险者攻击怪物" << cur.first + 1 << "造成" << attack << "点伤害, 怪物" <<  cur.first+1 
            << "(" << monster[cur.first].getHp()<<"/"<<monster[cur.first].getMaxHp()<<") "<< std::endl;
        } 
        weapon_attack_end();

        if(monster[cur.first].getHp()<=0){
            std::cout << "怪物" << cur.first + 1 << "死亡" << std::endl;
            monsterAttack.erase(monsterAttack.begin());
            defeat_num ++;
        }

        for(int i = 0; i< monsterAttack.size(); ++i){
            current_HP -= monster[monsterAttack[i].first].getAttack();
            std::cout<< "怪物" << monsterAttack[i].first + 1 << "攻击探险者, 造成" << monster[monsterAttack[i].first].getAttack() <<
            "点伤害， 探险者" << "(" << current_HP <<"/"<< max_HP <<") "<< std::endl;
            if(current_HP<=0) break;
        }
        if(current_HP<=0 ) break;
    }
    exper += defeat_num;
    if(exper >= max_exper){
        current_HP = max_HP;
        exper -= max_exper;
        std::cout << "获得" << defeat_num << "点经验, 生命恢复， 当前生命（" << current_HP << "/" << max_HP << ") , 当前经验("
        << exper << "/" << max_exper << ")"<< std::endl;
    }else{
        std::cout << "获得" << defeat_num << "点经验, 当前经验（" << exper << "/" << max_exper << ")"<< std::endl;
    }
}

// 判断有怪物存活
// bool character::judgeMonsterLive(std::vector<character>& monster){
//     for(int i = 0; i < monster.size(); ++i){
//         if(monster[i].checkIsLive()){
//             return true;
//         }
//     }
//     return false;
// }

// 陷阱房间 
void character::beat_trap(){
    int defeat_num = 0;
    character monster("monster_trap", 20, 20, 5);

    std::cout<< "遇到怪物1" << "(" << monster.getHp()<<"/"<<monster.getMaxHp()<<") "<<std::endl;
    std::cout << "战斗开始" << std::endl;
    while(current_HP >0 && monster.getHp()>0){
        weapon_check();
        if(!epuip_weapon.empty()){
            monster.setDeHp(attack + epuip_weapon[0].getAttack());
            std::cout << "探险者攻击怪物1" << "造成" << attack+epuip_weapon[0].getAttack() << "点伤害, 怪物1" 
                << "(" << monster.getHp()<<"/"<<monster.getMaxHp()<<") "<< std::endl;
        }else{
            monster.setDeHp(attack);
            std::cout << "探险者攻击怪物1" << "造成" << attack << "点伤害, 怪物1" 
                << "(" << monster.getHp()<<"/"<<monster.getMaxHp()<<") "<< std::endl;
        } 
        weapon_attack_end();
        if(monster.getHp()<=0){
            std::cout << "怪物1"  << "死亡" << std::endl;
            defeat_num ++;
            break;
        }
        current_HP -= monster.getAttack();
        std::cout<< "怪物1"  << "攻击探险者, 造成" << monster.getAttack() <<
        "点伤害， 探险者" << "(" << current_HP <<"/"<< max_HP <<") "<< std::endl;
        if(current_HP<=0) break;
    }
    exper += defeat_num;
    if(exper > max_exper){
        current_HP = max_HP;
        exper -= max_exper;
        std::cout << "获得" << defeat_num << "点经验, 生命恢复， 当前生命（" << current_HP << "/" << max_HP << ") , 当前经验("
        << exper << "/" << max_exper << ")"<< std::endl;
    }else{
        std::cout << "获得" << defeat_num << "点经验, 当前经验（" << exper << "/" << max_exper << ")"<< std::endl;
    }
}
// 首领房间
void character::beat_learder(){
    character monster("monster_leader", 40, 40, 15);

    std::cout<< "遇到怪物首领" << "(" << monster.getHp()<<"/"<<monster.getMaxHp()<<") "<<std::endl;
    std::cout << "战斗开始" << std::endl;
    while(current_HP >0 && monster.getHp()>0){
        weapon_check();
        if(!epuip_weapon.empty()){
            monster.setDeHp(attack + epuip_weapon[0].getAttack());
            std::cout << "探险者攻击怪物首领" << "造成" << attack+epuip_weapon[0].getAttack() << "点伤害, 怪物首领" 
                << "(" << monster.getHp()<<"/"<<monster.getMaxHp()<<") "<< std::endl;
        }else{
            monster.setDeHp(attack);
            std::cout << "探险者攻击怪物首领" << "造成" << attack << "点伤害, 怪物首领" 
                << "(" << monster.getHp()<<"/"<<monster.getMaxHp()<<") "<< std::endl;
        } 
        weapon_attack_end();
        if(monster.getHp()<=0){
            std::cout << "怪物首领"  << "死亡" << std::endl;
            break;
        }
        // 触发扩展一 攻击力提升1并且首领生命恢复20
        if(monster.getHp() < 10){
            monster.setAddHp(20);
            std::cout << "怪物首领恢复生命20点， 怪物首领（" << monster.getHp() << "/" << monster.getMaxHp() << ")" << std::endl; 
        }else{
            monster.setAddAttack(1);
            current_HP -= monster.getAttack();
            std::cout<< "怪物首领"  << "攻击探险者, 造成" << monster.getAttack() <<
            "点伤害， 探险者" << "(" << current_HP <<"/"<< max_HP <<") "<< std::endl;
        }
        if(current_HP<=0) break;
    }
    exper += 5;
    if(exper > max_exper){
        current_HP = max_HP;
        exper -= max_exper;
        std::cout << "获得" << 5 << "点经验, 生命恢复， 当前生命（" << current_HP << "/" << max_HP << ") , 当前经验("
        << exper << "/" << max_exper << ")"<< std::endl;
    }else{
        std::cout << "获得" << 5 << "点经验, 当前经验（" << exper << "/" << max_exper << ")"<< std::endl;
    }
}
// 武器房间
void character::beat_weapon(){
    int record_hp = current_HP;
    character monster("monster_weapon", 40, 40, 5);
    // 随机生成怪物武器
    int x = rand()%3 + 1;
    weapon monster_weapon(0, 0, 0);
    monster_weapon.generate_weapon(x);

    std::cout<< "遇到怪物1" << "(" << monster.getHp()<<"/"<<monster.getMaxHp()<<") "<<std::endl;
    std::cout << "战斗开始" << std::endl;
    while(current_HP >0 && monster.getHp()>0){
        weapon_check();
        if(!epuip_weapon.empty()){
            monster.setDeHp(attack+epuip_weapon[0].getAttack());
            std::cout << "探险者攻击怪物1" << "造成" << attack+epuip_weapon[0].getAttack() << "点伤害, 怪物1" 
                << "(" << monster.getHp()<<"/"<<monster.getMaxHp()<<") "<< std::endl;
        }else{
            monster.setDeHp(attack);
            std::cout << "探险者攻击怪物1" << "造成" << attack << "点伤害, 怪物1" 
                << "(" << monster.getHp()<<"/"<<monster.getMaxHp()<<") "<< std::endl;
        }    
        weapon_attack_end();
        if(monster.getHp()<=0){
            std::cout << "怪物1"  << "死亡" << std::endl;
            break;
        }
        current_HP -= monster.getAttack() + monster_weapon.getAttack();
        std::cout<< "怪物1"  << "攻击探险者, 造成" << monster.getAttack() + monster_weapon.getAttack()<<
        "点伤害， 探险者" << "(" << current_HP <<"/"<< max_HP <<") "<< std::endl;
        if(current_HP<=0) break;
    }
    exper += 2;
    if(exper > max_exper){
        current_HP = max_HP;
        exper -= max_exper;
        std::cout << "获得" << 2 << "点经验, 生命恢复， 当前生命（" << current_HP << "/" << max_HP << ") , 当前经验("
        << exper << "/" << max_exper << ")"<< std::endl;
    }else{
        std::cout << "获得" << 2 << "点经验, 当前经验（" << exper << "/" << max_exper << ")"<< std::endl;
        current_HP = record_hp;
        std::cout << "生命恢复， 当前生命（" << current_HP << "/" << max_HP << ")" << std::endl;
    }
    // 装备怪物武器 
    if(!epuip_weapon.empty()){
        epuip_weapon.pop_back();
    }
    epuip_weapon.push_back(monster_weapon);
    std::cout << "获得武器" << monster_weapon.getweaponId() << std::endl;
}
// 攻击前武器检查
void character::weapon_check(){
    if(!epuip_weapon.empty()){
        if(epuip_weapon[0].getweaponId()==3){
            int randnum = rand() % 2;
            if(randnum == 0){
                epuip_weapon[0].setAttack();
                std::cout << "攻击时武器攻击力翻倍！" << std::endl;
            }
        }else if(epuip_weapon[0].getweaponId()==2){
            epuip_weapon[0].getAttack();
        }
    }
}
// 攻击后武器损坏检查
void character::weapon_attack_end(){
    if(!epuip_weapon.empty()){
        int curEndurance = epuip_weapon[0].getEndurance() -1;
        epuip_weapon[0].setEndurance(curEndurance);
        if( curEndurance<= 0){
            std::cout << "武器" << epuip_weapon[0].getweaponId() << "损坏" << std::endl;
            epuip_weapon.pop_back();
        }
    }
}

