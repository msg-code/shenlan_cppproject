#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<unordered_map>
using namespace std;


int main(int argc, char* argv[]) {

	// windows平台下 viual studio上测试过可执行文件的加解密
	// const char* code_name = "code.txt";
	// const char* de_filename = "EN_NetAssist.exe";
	// const char* out_filename = "de_NetAssist.exe";
	// const char* de_filename = "en_02.jpg";
	// const char* out_filename = "de_02.jpg";

	char *code_name = argv[1];
    char *de_filename = argv[2];
    char *out_filename = argv[3];
	ifstream code_;
	ifstream input;
	ofstream out;

	code_.open(code_name);
	input.open(de_filename, ios_base::in | ios_base::binary);
	out.open(out_filename, ios_base::out | ios_base::binary | ios_base::trunc);
	if (!code_.is_open() | !input.is_open() | !out.is_open()) {
		cout << "open failed" << endl;
		return -1;
	}
	string code_str;
	unordered_map<char, char> mp;
	while (getline(code_, code_str)) {
		istringstream is(code_str);
		int i = 0;
		string s;
		while (!is.eof()) {
			is >> s;
			char y = (char)atoi(s.c_str());
			mp[y] = (char) i;
			i++;
		}
	}
	char c;
	while (input.get(c)) {
		out.put(mp[c]);
	}
	code_.close();
	input.close();
	out.close();

	return 0;
}