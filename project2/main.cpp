#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<algorithm>
// 读文件操作 包括输入数字以及输入输出进制
void read_input(std::string filename, std::vector<std::string>& out, int& input_s, int& output_s){

    std::ifstream infile;
    infile.open(filename);
    if(!infile.is_open()){
        std::cout << "ERROR: OPEN FILE FAILED" << std::endl;
    }
    std::string temp;
    int row = 0;
    while(getline(infile, temp)){
        if(row < 2){
            out.push_back(temp);
        }else{
            std::istringstream is(temp);
            while(!is.eof()){
                is >> input_s;
                is >> output_s;
            }
        }
        row++;
    }
    infile.close();
}
// 判断输入数字是否符合进制要求
bool judge(std::string& num, int scale){
    for(auto& str:num){
        if(str == '+'|| str == '-') continue;
        int temp = str - '0';
        int temp_a = str - 'a' + 10;
        int temp_A = str - 'A' + 10;
        // std::cout<< temp << " "<<temp_a<< " "<<temp_A<<" "<<scale<<std::endl; 
        if(scale <= 10 && temp < scale && temp >= 0) continue; 
        if(scale > 10 && scale <=36 && (temp < scale || (temp_a > 0 && temp_a  < scale)|| (temp_A > 0 && temp_A  < scale))) continue;
        return false;
    }
    return true;
}
// 字符串去零 "00012" -> "12" e.g "0000" -> "0"
std::string delete_zero_str(std::string& a){
    int i = 0;
    while(a[i] =='0'){
        i++;
    }
    if(i == a.size()){
        a.erase(0,i - 1);
    }else{
         a.erase(0,i);
    }
    return a;
}
// 加法 a+b e.g: ”1234648431“ + ”15464645415“
std::string add_longnum(std::string a, std::string b){
    int len_a = a.size();
    int len_b = b.size();
    int len = std::max(len_a, len_b);
    std::string ret;
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    int carry = 0;
    for(int i = 0; i < len; ++i){
        int str_a = i < len_a ? a[i]-'0':0;
        int str_b = i < len_b ? b[i]-'0':0;
        int sum = (str_a + str_b + carry) % 10;
        carry = (str_a + str_b + carry) / 10;
        ret.insert(ret.begin(), sum + '0');
    }
    if(carry != 0) ret.insert(ret.begin(), carry + '0');
    return ret;
}
// 减法 a-b e.g "10000" - "1000" 
std::string sub_longnum(std::string a, std::string b){

    std::string ret;
    int carry = 0;
    bool flag = false; // 符号标志位
    if(a.size() < b.size() || (a.size() == b.size() && a < b)){ //被减数小于减数
        flag = true;
        swap(a, b);
    }
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    for(int i = 0; i < b.size(); ++i){
        int str_a = a[i] - '0';
        int str_b = b[i] - '0';
        int sum = str_a - str_b - carry;
        if(sum >= 0){
            carry = 0;
            ret.insert(ret.begin(), sum +'0');
        }else{
            carry = 1;
            ret.insert(ret.begin(), sum + 10 +'0');
        }
    }
    for(int i = b.size(); i < a.size(); ++i){
        int str_a = a[i] - '0';
        int sum = str_a - carry;
        if(sum >= 0){
            carry = 0;
            ret.insert(ret.begin(), sum + '0');
        }else{
            carry = 1;
            ret.insert(ret.begin(), sum + 10 + '0');
        }
    }
    if (flag) ret.insert(ret.begin(), '-');
    return ret;
}
// char转化为int型
int charToInt(char x){
    if(x >= 'A' && x <= 'Z'){
        return x - 'A' + 10;
    }else if(x >= 'a' && x <= 'z'){
        return  x - 'a' + 10;
    }else if(x >= '0' && x <= '9'){
        return x - '0';
    }else{
        return -1;
    }
}
// int型转化为char型
char intToChar(int x){
    if(x >= 0 && x <= 9){
        return x + '0';
    }else if(x >= 10 && x <= 35){
        return x + 'a';
    }else{
        return -1;
    }
}

// 任意进制转化为10进制 input_s -> 10
std::string otherToDec(std::string a, int input_s){

    std::string ret = "0";
    std::string c = "1";
    std::string c_ = "1";
    for(int i = a.size()-1; i >= 0; i--){
        std::string temp = "0";
        int now = charToInt(a[i]); 
        for(int j = 0; j < now;j++){
            temp = add_longnum(temp, c);
        }
        // std::cout << "now " << now  << " temp " << temp<<std::endl; 
        ret = add_longnum(ret, temp);
        for(int k = 0; k < input_s -1; k++){
            c_ = add_longnum(c_, c);
        }
        c = c_;
    }
    return ret;
}

// 字符串取余 a % b e.g : "1000" / "8" = "0" (此时其实b = output_s（”2-36“）（字符串形式） 里面可以不做输入判错 一开始做过了)
std::string string_remainder(std::string a, std::string b){
    if(b == "0"){
        std::cout << "ERROR: output_s" << std::endl;
        return "ERROR";
    } 
    if(a.size() == b.size() && a == b || (a.size() < b.size()))  return "0";
    delete_zero_str(a);
    delete_zero_str(b);
    int divisor = std::stoi(b);
    int ans = 0;
    for(int i = 0; i < a.size(); i++){
        ans = ans * 10 + (a[i] - '0');
        ans = ans % divisor;
    }
    return std::to_string(ans);
}
// 字符串除法 a / b  e.g : "1000" / "8" = "125"
std::string dividion_string(std::string a, std::string b){
    std::string ret;
    // 本函数没有对b 进行判错 （取余操作已说明）
    if(a.size() == b.size() && a == b)  return "1";
    if(a.size() < b.size()) return "0";
    delete_zero_str(a);
    delete_zero_str(b);
    std::string temp = "";
    for(int i = 0; i < a.size(); i++){
        int num = 0;
        temp.insert(temp.end(), a[i]);
        delete_zero_str(temp); // 特别重要 去零 "00" 和 "0"差别影响判断
        while(temp.size() == b.size() && temp >= b|| temp.size() > b.size()){
            temp = sub_longnum(temp, b);
            num ++;
            delete_zero_str(temp);
            // std::cout << temp << std::endl;
        }
        // std::cout << num << std::endl;
        if(num<10){
            ret.insert(ret.end(), num + '0');
        }else{
            ret.insert(ret.end(), num - 10 + 'a');
        }
    }
    return delete_zero_str(ret);

}

// 字符串的大小判断 （仅调试使用）
// int jud(std::string a, std::string b){
//     if(a.size() == b.size() && a> b){
//         return 1;
//     }
//     if(a.size() == b.size()&& a ==b){
//         return 0;
//     }else if(a.size()>b.size()){
//         return 1;
//     }else{
//         return -1;
//     }
// }


// 十进制转化为任意进制 10 -> output_s
std::string decToOther(std::string a, int output_s){
    std::string ret;
    if(a == "0") return "0";
    while(a != "0"){
        std::string temp;
        std::string remain = string_remainder(a, std::to_string(output_s));
        // 此时的remain 是数字形式的字符串 并没有转化为a-z形式
        // std::cout<< a << " " << remain <<std::endl;
        temp = a;
        a = dividion_string(a, std::to_string(output_s));
        int int_remain = std::stoi(remain);
        if( a == "0") int_remain = std::stoi(temp);
        if( int_remain < 10){
            ret.insert(ret.begin(), int_remain + '0');
        }else{
            ret.insert(ret.begin(), int_remain -10 + 'A');
        }
        // std::cout<< a << " " << remain <<std::endl;
    }
    return delete_zero_str(ret);
}

// 最终考虑所有情况的长整数加法
std::string final_operator(std::string a, std::string b, int& input_s, int& output_s){
    std::string ret;
    // 四种情况分别处理 ++ -- +- -+ 以及 隐式+
    if(a[0] == '+'){
        a.erase(0, 1);
        a = otherToDec(a, input_s);
        if(b[0] == '+'){  // + +
            b.erase(0,1);
            b = otherToDec(b, input_s);
            ret = add_longnum(a, b);
            delete_zero_str(ret);
            ret = decToOther(ret, output_s);
        }else if(b[0] == '-'){ // + -
            b.erase(0,1);
            b = otherToDec(b, input_s);
            ret = sub_longnum(a, b);
            if(ret[0] == '-'){ //结果为负时 先将进制转化 后加上符号
                ret.erase(0,1);
                ret = decToOther(ret, output_s);
                delete_zero_str(ret);
                ret.insert(ret.begin(), '-');
            }else{
                ret = decToOther(ret, output_s);
                delete_zero_str(ret);
            }
        }else{  // + +
            b = otherToDec(b, input_s);
            ret = add_longnum(a, b);
            delete_zero_str(ret);
            ret = decToOther(ret, output_s);
        }
    }else if(a[0] == '-'){ 
        a.erase(0, 1);
        a = otherToDec(a, input_s);
        if(b[0] == '+'){  // - +
            b.erase(0,1);
            b = otherToDec(b, input_s);
            ret = sub_longnum(b, a);
            if(ret[0] == '-'){ //结果为负时 先将进制转化 后加上符号
                ret.erase(0,1);
                ret = decToOther(ret, output_s);
                delete_zero_str(ret);
                ret.insert(ret.begin(), '-');
            }else{
                ret = decToOther(ret, output_s);
                delete_zero_str(ret);
            }
            // delete_zero_str(ret);
        }else if(b[0] == '-'){ // - -
            b.erase(0,1);
            b = otherToDec(b, input_s);
            ret = add_longnum(a, b);
            ret.erase(0,1);
            ret = decToOther(ret, output_s);
            delete_zero_str(ret);
            ret.insert(ret.begin(), '-');
        }else{  // - +
            b = otherToDec(b, input_s);
            ret = sub_longnum(b, a);
            if(ret[0] == '-'){ //结果为负时 先将进制转化 后加上符号
                ret.erase(0,1);
                ret = decToOther(ret, output_s);
                delete_zero_str(ret);
                ret.insert(ret.begin(), '-');
            }else{
                ret = decToOther(ret, output_s);
                delete_zero_str(ret);
            }
        }
    }else{  // 隐式 +
        a = otherToDec(a, input_s);
        if(b[0] == '+'){  // + +
            b.erase(0,1);
            b = otherToDec(b, input_s);
            ret = add_longnum(a, b);
            ret = decToOther(ret, output_s);
            delete_zero_str(ret);
        }else if(b[0] == '-'){ // + -
            b.erase(0,1);
            b = otherToDec(b, input_s);
            ret = sub_longnum(a, b);
            if(ret[0] == '-'){ //结果为负时 先将进制转化 后加上符号
                ret.erase(0,1);
                ret = decToOther(ret, output_s);
                delete_zero_str(ret);
                ret.insert(ret.begin(), '-');
            }else{
                ret = decToOther(ret, output_s);
                delete_zero_str(ret);
            }
        }else{  // + +
            b = otherToDec(b, input_s);
            ret = add_longnum(a, b);
            ret = decToOther(ret, output_s);
            delete_zero_str(ret);
        }
    }
    
    return ret;
}
int main(){
    std::string filename = "input.txt";
    std::vector<std::string> data;
    std::string ret;
    int input_s = 0; // 输入进制
    int output_s = 0; // 输出进制
    read_input(filename, data, input_s, output_s);
    if(input_s < 2 || input_s > 36 || output_s < 2 || output_s >36){
        std::cout << "Please input true scale" << std::endl;
        return -1;
    }
    if(!judge(data[0], input_s)||!judge(data[1], input_s)){
        std::cout<< "scale and input's num not match" << std::endl;
        return -1;
    }
    // 测试读入数据正确性
        for(auto& d:data){
        std::cout << d << std::endl;
    }
    std::cout<< "input_s = " << input_s << " output_s = " << output_s << std::endl; 

    // 最终操作
    ret = final_operator(data[0], data[1], input_s, output_s);
    std::cout << "result = " << ret << std::endl;
    std::string s{"124"};
    std::cout<< <<std::endl;
    // 测试 十进制下的加减法
    // ret = add_longnum(data[0], data[1]);
    // ret = sub_longnum("100", "10000");

    // 测试任意进制转十进制操作
    // std::string x = otherToDec("12342323423", 10);
    // std::cout << "otherToDec = " << x << std::endl;
    
    // 测试十进制转任意进制操作
    // std::string x = decToOther("1000", 16);
    // std::cout << "decToOther = " << x << std::endl;

    // 测试去零操作
    // std::string x ="000012";
    // delete_zero_str(x);
    // std::cout<<x<<std::endl;

    // 测试取余操作
    // std::string x;
    // x = string_remainder("1000", "8");
    // std::cout << x << std::endl;

    // 测试除法操作
    // std::string x = dividion_string("10000", "8");
    // std::cout << x << std::endl;

    // std::cout << jud("5", "14") << std::endl;
    return 0;
}