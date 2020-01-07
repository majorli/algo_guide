#include <cstdio>
#include <cstring>

bool sub_sequence(char *s, char *t);

int main()
{
	char s[81], t[81];
	scanf("%80s %80s", s, t);
	printf("%s\n", sub_sequence(s, t) ? "Yes" : "No");

	return 0;
}

bool sub_sequence(char *s, char *t)
{
	int m = strlen(s), n = strlen(t);
	int j = 0;
	for (int i = 0; i < m; ++i) {
		while (j < n && t[j] != s[i]) ++j;
		if (j == n) return false;
		++j;
	}
	return true;
}

