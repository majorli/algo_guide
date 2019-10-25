#include <cstdio>
#include <ctime>

int main()
{
	clock_t start, end;
	start = clock();
	int pow2[100000];
	for (int i = 1; i <= 100000; i++)
		pow2[i - 1] = i * i;
	end = clock();
	printf("\n100000 times of i^i computed using a for loop.\n");
	printf("Start at %ld clocks, end at %ld clocks.\n", start, end);
	printf("Time elapsed = %ld clocks.\n", end - start);
	printf("CLOCKS_PER_SEC = %ld\n", CLOCKS_PER_SEC);
	printf("In ms, time elapsed = %ld ms.\n",
			(end - start) / (CLOCKS_PER_SEC / 1000));

	return 0;
}
