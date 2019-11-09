#include <cstdio>

char *strcpy(char *dest, const char *src)
{
	int i = 0;
	while (src[i]) {
		dest[i] = src[i];
		i++;
	}
	return dest;
}

int main()
{
	char src[] = "Hello, World!";
	char dest[100];

	strcpy(dest, src);
	printf("%s\n", dest);

	return 0;
}
