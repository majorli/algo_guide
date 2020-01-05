#include <cstdio>
#include <cstring>

bool is_period(char *s, int p);

int main()
{
	char s[81] = { 0 };
	scanf("%80s", s);
	int n = strlen(s), p;	// 调用strlen()获取s的长度
	int half = n / 2;
	for (p = 1; p <= half; ++p)
		if (n % p == 0 && is_period(s, p)) break;// 利用逻辑短路，若p不是因数则判断直接结束
	printf("%d\n", p > half ? n : p);	// p > half 说明全部可能的因数都判断失败了

	return 0;
}

bool is_period(char *s, int p)
{
	int n = strlen(s);
	for (int j = p; j < n; j += p)
		if (strncmp(s, s+j, p)) return false;	// 比较从s开始的和从s[j]开始的p个字符
	return true;
}
