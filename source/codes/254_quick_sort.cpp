#include <cstdio>
#include <cstdlib>
#include <ctime>

void print(int d[], int n);

int partition(int d[], int l, int r);

void quick_sort(int d[], int l, int r);

int main()
{
	int n, d[100000];
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%d", &d[i]);

	srand(time(NULL));
	quick_sort(d, 0, n);
	print(d, n);

	return 0;
}

int partition(int d[], int l, int r)
{
	int i = l, last = r - 1, pivot = d[r-1];
	for (int j = l; j < last; ++j)
		if (d[j] < pivot) {
			d[last] = d[i];
			d[i++] = d[j];
			d[j] = d[last];
		}
	d[last] = d[i];
	d[i] = pivot;
	return i;
}

void quick_sort(int d[], int l, int r)
{
	if (r - l <= 1) return;

	int t = l + rand() % (r - l);
	int tmp = d[t];
	d[t] = d[r-1];
	d[r-1] = tmp;

	int p = partition(d, l, r);
	quick_sort(d, l, p);
	quick_sort(d, p + 1, r);
}

void print(int d[], int n)
{
	printf("%d", d[0]);
	for (int i = 1; i < n; ++i) printf(" %d", d[i]);
	printf("\n");
}

