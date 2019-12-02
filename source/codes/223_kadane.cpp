#include <cstdio>

inline int max(int a, int b)
{
	return a > b ? a : b;
}

int main()
{
	int n, a, max_so_far, max_end_here;

	scanf("%d", &n);
	scanf("%d", &a);
	max_so_far = a;
	max_end_here = a;
	while (--n) {
		scanf("%d", &a);
		max_end_here = max(max_end_here + a, a);
		max_so_far = max(max_so_far, max_end_here);
	}
	printf("%d\n", max_so_far);

	return 0;
}
