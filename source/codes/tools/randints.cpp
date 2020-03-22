#include <cstdio>
#include <cstdlib>
#include <ctime>

int main()
{
	int n;
	scanf("%d", &n);
	srand(time(NULL));
	printf("%d\n", n);
	printf("%d", rand() % 2000 + 1);
	for (int i = 0; i < n; ++i)
		printf(" %d", rand() % 2000 + 1);
	printf("\n");
	return 0;
}

