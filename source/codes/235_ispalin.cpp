#include <cstdio>
#include <cstring>

bool is_palin(const char *s);
bool is_palin_p(const char *s);

int main()
{
	char s[81];
	scanf("%80s", s);
	printf("%s is%sa palindromic string.\n", s, is_palin_p(s) ? " " : " not ");

	return 0;
}

bool is_palin(const char *s)
{
	int i = 0, j = strlen(s) - 1;
	while (i <= j)
		if (s[i++] != s[j--]) return false;
	return true;
}

bool is_palin_p(const char *s)
{
	const char *left = s, *right = s + strlen(s) - 1;
	while (left <= right)
		if (*(left++) != *(right--)) return false;
	return true;
}
