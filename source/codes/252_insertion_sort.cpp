#include <cstdio>

void insertion_sort(int d[], int n);

int main()
{
	int n, d[1000];
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%d", &d[i]);

	insertion_sort(d, n);
	print(d, n);

	return 0;
}

void insertion_sort(int d[], int n)
{
	int j, t;
	for (int m = 1; m < n; ++m) {
		t = d[m];
		j = m - 1;
		while (j >= 0 && d[j] > t) {
			d[j+1] = d[j];
			--j;
		}
		d[j+1] = t;
	}
}
