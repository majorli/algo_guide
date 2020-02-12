#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
	string src = "3 Alice 1 5 Bob 2 4.7 Carol 3 3.5";
	int n;
	string name;
	short no;
	double gpa;

	istringstream srcin(src);		// 建立字符串输入流srcin并连接到src上
	ostringstream dstout;			// 建立字符串输出流dstout
	dstout << "No.\tName\tGPA" << endl;	// 向dstout输出
	srcin >> n;				// 从src读入学生数n
	for (int i = 0; i < n; ++i) {
		srcin >> name >> no >> gpa;	// 读入一个学生的姓名学号和分数
		dstout << no << '\t' << name << '\t' << gpa << endl;	// 输出到dstout
	}
	string dst = dstout.str();		// 从字符串输出流dstout获取所有已经输出的内容
	cout << dst;

	return 0;
}
