#include <cstdio>

template<typename T>
T max(T a, T b)
{
	return a > b ? a : b;
}

int main()
{
	printf("%d is bigger\n", max(3, -2));
	printf("%lf is bigger\n", max(2.7817, 3.1415));

	return 0;
}
