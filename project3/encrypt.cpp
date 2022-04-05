#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

// void  encry(std::string& s, std::string& code){
//     for(int i = 0; i < s.size(); ++i){
//         if(s[i] >= 'a'&& s[i] <='z'){
//             s[i] = code[s[i] - 'a'];
//         }
//     }
// }
int main(int argc, char *argv[]){

    char *code_name = argv[1];
    char *en_filename = argv[2];
    char *out_filename = argv[3];
    std::ifstream en_before;
    std::ofstream en_after;
    std::ifstream code;
    //读字节流
    code.open(code_name, std::ios_base::binary);
    en_before.open(en_filename, std::ios_base::binary);
    en_after.open(out_filename, std::ios_base::binary | std::ios_base::trunc); 
    if(!code.is_open() || !en_before.is_open() || !en_after.is_open()){
        std::cout << "open file failed" << std::endl;
        return -1;
    }
    std::string code_;
    std::string in_str;
    // std::string out_str;
    while(getline(code, code_));
    // std::cout << code_<< std::endl; 

    while(getline(en_before,in_str)){

        // 使用istringstream 会出现多个空格合并成一个的问题 因此未采用
        // std::istringstream is(in_str);
        // while (!is.eof())
        // {
        //     is >> out_str;
        //     encry(out_str, code_);
        //     en_after << out_str << " ";
        // }
        for(auto& str:in_str){
            if(str >= 'a'&& str <= 'z'){
               en_after << code_[str - 'a']; 
            }else{
                en_after << str;
            } 
        }
        en_after << "\n";
        
    }
    en_before.close();
    en_after.close();
    code.close();
    return 0;
}