#include <cstdio>
#include <cstring>

int main()
{
	char s[81];
	scanf("%80s", s);

	int pos[128];
	memset(pos, -1, sizeof(pos));
	int n = strlen(s), max = 0, len = 0;
	for (int i = 0, j = 0; j < n; ++j) {
		if (pos[s[j]] >= i) i = pos[s[j]] + 1;
		pos[s[j]] = j;
		len = j - i + 1;
		if (len > max) max = len;
	}
	printf("%d\n", max);

	return 0;
}

