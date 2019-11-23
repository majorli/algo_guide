#include <vector>
#include <cstdio>

using namespace std;

int main()
{
	vector<int> v;			// 定义一个存放int型元素的vector

	for (int i = 0; i < 10; i++)
		v.push_back(i * i);	// 添加10个元素，分别为0到9的平方

	vector<int>::iterator it = v.begin();	// 定义迭代器it并将其初始化为v的头迭代器
	while(it != v.end())			// 循环，直到it增长到等于v的尾迭代器
		printf("%3d", *it++);		// 用*运算符取值，用++运算向后移动it的位置
	printf("\n");

	return 0;
}

