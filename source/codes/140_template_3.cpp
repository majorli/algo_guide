#include <cstdio>

const int MAXN = 100;
const double PI = 3.1415926536;

template<typename T>
struct List {
	T values[MAXN];
	int len;
};

int main()
{
	List<int> sqr;
	for (int i = 0; i < 10; i++)
		sqr.values[i] = i * i;
	sqr.len = 10;

	for (int i = 0; i < sqr.len; i++)
		printf("sqr(%d) = %d\n", i, sqr.values[i]);

	List<double> cir;
	for (int i = 0; i < 10; i++)
		cir.values[i] = PI * sqr.values[i];
	cir.len = sqr.len;

	for (int i = 0; i < cir.len; i++)
		printf("area of radius %d circle = %12.8lf\n", i, cir.values[i]);

	return 0;
}
