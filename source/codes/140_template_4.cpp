#include <cstdio>

template<int N>
int sqr_sum(int (&a)[N])
{
	int s = 0;
	for (int i = 0; i < N; i++)
		s += a[i] * a[i];
	return s;
}

template<typename T, int M, int N>
T cube_sum(const T (&num)[M][N])
{
	T s = 0;
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			s += num[i][j] * num[i][j];
	return s;
}

int main()
{
	int a[4] = { 1, 2, 3, 4 };
	double f[2][2] = {{ 1.1, 2.2 }, { 3.3, 4.4 }};

	printf("%d\n", sqr_sum(a));
	printf("%lf\n", cube_sum(f));

	return 0;
}
