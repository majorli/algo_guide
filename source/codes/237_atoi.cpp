#include <iostream>
#include <string>
#include <cctype>

using namespace std;

const int READY = 0;		// 初始状态
const int READING = 1;		// 读数状态
const int TERMINATED = 2;	// 终止状态

// 记住下面C++获取int型数据上下限的方法，写起来太长，所以事先定义为常数，方便后面的书写
const long long MIN = numeric_limits<int>::min();	// int型最小值
const long long MAX = numeric_limits<int>::max();	// int型最大值

struct FSM {
	int state;		// 状态
	bool neg;		// 负数标志，计算value时正负数公式不同
	long long value;	// 值，考虑到可能溢出所以用long long
};

void atoi(FSM &fsm, char ch);

int main()
{
	FSM fsm = { 0, false, 0 };	// 定义并初始化状态机
	string s;
	cin >> s;

	string::iterator it = s.begin();
	while (it != s.end()) {
		atoi(fsm, *(it++));	// 状态机处理当前字符，迭代器指向下一字符
		if (fsm.state == TERMINATED) break;	// atoi转换过程结束
	}
	cout << (int)fsm.value << endl;	// 强制转换为int型，输出

	return 0;
}

void atoi(FSM &fsm, char ch)
{
	switch (fsm.state) {
		case READY:	// 初始状态
			switch (ch) {
				case ' ':	// 空格，什么都不做
					break;
				case '+':	// 正号，直接转移到READING状态
					fsm.state = READING;
					break;
				case '-':	// 负号，设置负数标志并转到READING状态
					fsm.neg = true;
					fsm.state = READING;
					break;
				default:
					if (ch >= '0' && ch <= '9') {
						// 数字，设为值并转到READING状态
						fsm.value = ch - '0';	
						fsm.state = READING;
					} else {
						// 其他，非数字、空格、正负号，转到终止状态
						fsm.state = TERMINATED;
					}
			}
			break;
		case READING:	// 读数状态
			if (ch >= '0' && ch <= '9') {
				// 数字，计算新的值
				if (fsm.neg) {
					fsm.value = fsm.value * 10 - (ch - '0');
					if (fsm.value < MIN) fsm.value = MIN;
				} else {
					fsm.value = fsm.value * 10 + (ch - '0');
					if (fsm.value > MAX) fsm.value = MAX;
				}
			} else {
				// 非数字，转到终止状态
				fsm.state = TERMINATED;
			}
			break;
		default:;	// 空的default后面要有一个空语句;不要忘记
	}
	// void函数在代码的末尾可以不写return语句
}

