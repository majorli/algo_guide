#include <cstdio>

template<typename T, typename V>
T compare(T a, V b, bool max = true)
{
	if (max)
		return a > (T)b ? a : (T)b;
	else
		return a < (T)b ? a : (T)b;
}

int main()
{
	double a = 3.1415926;
	int b = 2;
	long long c = -3;

	printf("%lf is bigger\n", compare(a, b));
	printf("%lld is smaller\n", compare(c, b, false));

	return 0;
}
