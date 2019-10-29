#include <cstdio>

const int MAXN = 1000000;
bool seive[MAXN];

void erato(int n)
{
	seive[0] = true;
	seive[1] = true;
	int p = 2;
	while (p * p <= n) {
		for (int k = p * p; k <= n; k += p)
			seive[k] = true;
		while (seive[++p]);
	}
}

int main()
{
	erato(120);
	int cnt = 0;
	for (int i = 2; i <= 120; i++)
		if (!seive[i])
			printf("%3d%c", i, ++cnt % 20 ? ' ' : '\n');
	printf("\nThere're %d primes from 2 to 120.\n", cnt);

	return 0;
}
