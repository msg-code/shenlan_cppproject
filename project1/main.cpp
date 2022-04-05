#include<iostream>
#include<cstdlib>
#include<time.h>
#define    CLOCKS_PER_SEC      ((clock_t)1000)
int main() {
	// 变量定义
	int len;
	int answer;
	int Correct_num = 0;
	int MAX_VALUE;
	int flag_mult_division;
	clock_t start, finish;
	srand(time(0));
	// 用户输入
	std::cout << "1.Welcome to answer system!" << std::endl;
	std::cout << "2.Please confirm the number and difficulty of the questions" << std::endl;
	std::cout << "question number:" << std::endl;
	std::cin >> len;
	std::cout << "Size of operation: 0 - MAX_VALUE" << std::endl;
	std::cout << "MAX_VALUE:" << std::endl;
	std::cin >> MAX_VALUE;
	std::cout << "Set multiplication and division? (1:yes 2:no)" << std::endl;
	std::cin >> flag_mult_division;
	std::cout << "3.Please answer them in turn!" << std::endl;
	int *input_1 = (int *)malloc(sizeof(int)*len); //user_input
	int *input_2 = (int *)malloc(sizeof(int)*len); //user_input
	int *flag = (int *)malloc(sizeof(int)*len); //运算符号标志
	double *user_answer = (double *)malloc(sizeof(double)*len); //用户答案
	bool *is_correct = (bool *)malloc(sizeof(bool)*len); //存储是否正确
	double *duration = (double *)malloc(sizeof(double)*len);
	for (int i = 0; i < len; ++i) {
		input_1[i] = rand() % MAX_VALUE;
		input_2[i] = rand() % MAX_VALUE;
		// 设置乘除法
		if (flag_mult_division==2) {
			flag[i] = rand() % 2 + 1;
		}
		else {
			flag[i] = rand() % 4 + 1;
		}
		std::cout << "please input your answer" << std::endl;
		std::cout << "This is " << i+1 << " question:" << std::endl;
		start = clock();
		if (flag[i] == 1) {
			std::cout << input_1[i] << " + " << input_2[i] << " = ?" << std::endl;
			std::cin >> user_answer[i];
			if (user_answer[i] == input_1[i] + input_2[i]) {
				is_correct[i] = true;
				Correct_num++;
			}
			else {
				is_correct[i] = false;
			}
		}
		else if(flag[i] == 2) {
			std::cout << input_1[i] << " - " << input_2[i] << " = ?" << std::endl;
			std::cin >> user_answer[i];
			if (user_answer[i] == input_1[i] - input_2[i]) {
				is_correct[i] = true;
				Correct_num++;
			}
			else {
				is_correct[i] = false;
			}
		}
		else if (flag[i] == 3) {
			std::cout << input_1[i] << " * " << input_2[i] << " = ?" << std::endl;
			std::cin >> user_answer[i];
			if (user_answer[i] == input_1[i] * input_2[i]) {
				is_correct[i] = true;
				Correct_num++;
			}
			else {
				is_correct[i] = false;
			}
		}
		else {
			std::cout << input_1[i] << " / " << input_2[i] << " = ?" << std::endl;
			std::cin >> user_answer[i];
			if (user_answer[i] == (double)input_1[i] / (double)input_2[i]) {
				is_correct[i] = true;
				Correct_num++;
			}
			else {
				is_correct[i] = false;
			}
		}
		finish = clock();
		duration[i] = (double)(finish - start) / CLOCKS_PER_SEC;
	}
	std::cout << "You answered " << Correct_num << " questions correctly and " << len - Correct_num << " wrong" << std::endl;
	std::cout << "wrong answer as follows:" << std::endl;
	for (int i = 0; i < len; ++i) {
		if (!is_correct[i]) {
			if (flag[i] == 1) {
				std::cout << input_1[i] << " + " << input_2[i] << " != " << user_answer[i] << " -> " << " = " << input_1[i] + input_2[i] << std::endl;

			}
			else if(flag[i] == 2) {
				std::cout << input_1[i] << " - " << input_2[i] << " != " << user_answer[i] << " -> " << " = " << input_1[i] - input_2[i] << std::endl;
			}
			else if (flag[i] == 3) {
				std::cout << input_1[i] << " * " << input_2[i] << " != " << user_answer[i] << " -> " << " = " << input_1[i] * input_2[i] << std::endl;
			}
			else {
				std::cout << input_1[i] << " / " << input_2[i] << " != " << user_answer[i] << " -> " << " = " << (double)input_1[i] / (double)input_2[i] << std::endl;
			}
			
		}
	}
	std::cout << "your score = " << (double)Correct_num / len *100 << " (100 points)" << std::endl;
	double avg_duration = 0;
	double sum_duration = 0;
	double min_duration = duration[0];
	for (int i = 0; i < len; ++i) {
		min_duration = duration[i] <= min_duration ? duration[i] : min_duration;
		sum_duration += duration[i];
	}
	avg_duration = sum_duration / len;
	std::cout << "avg_duration = " << avg_duration << " ; min_duration= " << min_duration <<"(seconds)"<<std::endl;
	free(input_1);
	free(input_2);
	free(flag);
	free(user_answer);
	free(is_correct);
	free(duration);
	return 0;

}