#include <cstdio>
#include <cstring>
#include <ctime>

int expand(const char *s, int left, int right);

int main()
{
	char s[100010];
	scanf("%100009s", s);

	clock_t start, end;
	start = clock();

	int sz = strlen(s);
	int len1, len2, len, maxlen = 1, left = 0;
	for (int i = 0; i < sz; ++i) {
		len1 = expand(s, i, i);
		len2 = expand(s, i, i+1);
		len = len1 > len2 ? len1 : len2;
		if (len > maxlen) {
			maxlen = len;
			left = i - (len - 1) / 2;
		}
	}
	
	end = clock();

	while (maxlen--) putchar(s[left++]);
	putchar('\n');

	printf("time elapsed = %ld ms.\n", (end - start) / (CLOCKS_PER_SEC / 1000));

	return 0;
}

int expand(const char *s, int left, int right)
{
	while (left >= 0 && s[right] && s[left] == s[right]) {
		--left;
		++right;
	}
	return right - left - 1;
}
