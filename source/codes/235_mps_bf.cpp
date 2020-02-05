#include <cstdio>
#include <cstring>
#include <ctime>

bool is_palin(const char *left, const char *right);

int main()
{
	char s[100010];
	scanf("%100009s", s);

	clock_t start, end;
	start = clock();

	int sz = strlen(s);
	char *left, *right;	// 用来指示待判断子串的头尾字符的一对指针
	for (int len = sz; len > 0; --len) {	// 外层循环，子串长度len，从sz到1
		left = s;			// 左指针从s的头部开始
		right = left + len - 1;		// 根据len计算出右指针
		while (*right)	// 循环条件为右指针处的字符不为'\0'，右端抵达'\0'表示没有长len的子串了
			if (is_palin(left, right)) {
				break;		// 找到一个回文子串，马上退出循环
			} else {
				++left;		// 否则左右指针分别后移一个字符继续判断
				++right;
			}
		// while循环结束后若右指针处不是'\0'说明找到回文子串了，那就退出外层循环，搜索结束
		// 否则说明本轮没有找到回文子串，那就继续外循环，len减1继续暴搜
		if (*right) break;
	}

	end = clock();

	while (left <= right) putchar(*(left++));	// 一定会有解，所以放心地输出即可
	putchar('\n');

	printf("time elapsed = %ld ms.\n", (end - start) / (CLOCKS_PER_SEC / 1000));

	return 0;
}

bool is_palin(const char *left, const char *right)
{
	while (left <= right)
		if (*(left++) != *(right--)) return false;
	return true;
}

