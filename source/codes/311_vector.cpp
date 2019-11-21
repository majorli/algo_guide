#include <vector>
#include <cstdio>

using namespace std;

int main()
{
	vector<int> v;

	for (int i = 1; i <= 5; i++)		// 依次向v的尾部添加1、2、3、4、5
		v.push_back(i);
	for (int i = 1; i <= 5; i++)		// 依次从v的头部插入1、2、3、4、5
		v.insert(v.begin(), i);
	// 到这里为止，v中的元素依次应为：5、4、3、2、1、1、2、3、4、5

	printf("v.size() = %lu\n", v.size());	// 输出：10
	printf("v: ");
	for (int i = 0; i < v.size(); i++)	// 依次输出v中的元素
		printf("%3d", v[i]);
	printf("\n");

	v.pop_back();				// 弹掉v尾部的那个元素
	printf("v: ");
	for (int i = 0; i < v.size(); i++)
		printf("%3d", v[i]);
	printf("\n");
	// 到这里为止，应该输出：5、4、3、2、1、1、2、3、4

	v.erase(v.begin() + 3);		// 删除从头向后数第3个位置(v[3])的元素
	printf("v: ");
	for (int i = 0; i < v.size(); i++)
		printf("%3d", v[i]);
	printf("\n");
	// 到这里为止，应该输出：5、4、3、1、1、2、3、4

	v.insert(v.begin(), 9);		// 在最头部位置(v[0])插入整数9
	printf("v: ");
	for (int i = 0; i < v.size(); i++)
		printf("%3d", v[i]);
	printf("\n");
	// 到这里为止，应该输出：9、5、4、3、1、1、2、3、4

	if (!v.empty()) v.clear();		// 如果v不为空，那么清空它
	printf("v.empty() = %s\n", v.empty() ? "true" : "false");

	return 0;
}
