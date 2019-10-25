#include <cstdlib>
#include <ctime>
#include <cstdio>

int main()
{
	srand(time(NULL));
	for (int i = 0; i < 100; i++)
		printf("%3d%c", rand() % 100, i % 20 == 19 ? '\n' : ',');

	return 0;
}
