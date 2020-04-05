#include <cstdio>
#include <cctype>

inline bool to_expand(char prev, char next)
{
	return ((isalpha(prev) && isalpha(next)) || (isdigit(prev) && isdigit(next)))
		&& next > prev;
}

int main()
{
	int p1, p2, p3;
	char str[101] = { 0 }, res[21000] = { 0 };

	scanf("%d %d %d", &p1, &p2, &p3);
	scanf("%100s", str);

	char *r = str, *w = res;
	*(w++) = *(r++);
	while (*(r+1)) {
		if (*r != '-' || !to_expand(*(r-1), *(r+1))) {
			*(w++) = *(r++);
			continue;
		}
		char *temp = w;	// 保存开始扩展的位置，以便后续万一要颠倒顺序
		for (char d = (*(r-1) + 1); d < *(r+1); d++) {
			char ch = p1 == 3 ? '*' : p1 == 2 ? toupper(d) : d;
			for (int i = 0; i < p2; i++)
				*(w++) = ch;
		}
		if (p3 == 2 && p1 != 3) {
			char *i = temp, *j = w - 1;	// 颠倒刚才扩展的子串
			while (i < j) {
				char t = *i;
				*(i++) = *j;
				*(j--) = t;
			}
		}
		r++;
	}
	*w = *r;
	printf("%s\n", res);

	return 0;
}
