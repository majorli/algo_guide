#include <cstdio>

int readint()
{
	int n = 0, ch;
	bool neg = false;	// 是否负数的标志
	// 先读完输入缓存中的所有无效字符，直到出现0-9的数字符或正负号+，-
	while (((ch = getchar()) < '0' || ch > '9') && ch != '+' && ch != '-');
	if (ch == '-') neg = true;
	else if (ch >= '0' && ch <= '9') n = ch - '0';
	while ((ch = getchar()) >= '0' && ch <= '9') n = n * 10 + ch - '0';
	return neg ? -n : n;
}

int main()
{
	int a[5];
	for (int i = 0; i < 5; i++) a[i] = readint();
	for (int i = 4; i >= 0; i--) printf("%d\n", a[i]);
	return 0;
}
