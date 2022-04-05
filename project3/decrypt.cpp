#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<unordered_map>

int main(int argc, char *argv[]){

    char *code_name = argv[1];
    char *de_filename = argv[2];
    char *out_filename = argv[3];
    std::ifstream de_before;
    std::ofstream de_after;
    std::ifstream code;
    //读字节流
    code.open(code_name, std::ios_base::binary);
    de_before.open(de_filename, std::ios_base::binary);
    de_after.open(out_filename, std::ios_base::binary | std::ios_base::trunc); 
    if(!code.is_open() || !de_before.is_open() || !de_after.is_open()){
        std::cout << "open file failed" << std::endl;
        return -1;
    }
    std::string code_;
    std::string in_str;
    while(getline(code, code_));
    // std::cout << code_<< std::endl;
    // 采用哈希表存储编码对应关系，便于解码 
    std::unordered_map<char, char> mp;
    int num = 0;
    for(auto& c:code_){
        mp[c] = 'a'+ num;
        num++;
    }

    while(getline(de_before,in_str)){

        for(auto& str:in_str){
            if(str >= 'a'&& str <= 'z'){
               de_after << mp[str]; 
            }else{
                de_after << str;
            } 
        }
        de_after << "\n";
        
    }
    de_before.close();
    de_after.close();
    code.close();
    return 0;
}