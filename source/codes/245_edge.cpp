#include <cstdio>

#define LEN(x) sizeof(x)/sizeof(x[0])

int bi_edge(int a[], int v, int left, int right);

int main()
{
        int a[] = { 1, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 6 };
        int v;
        scanf("%d", &v);
        printf("right-hand edge of %d is at %d\n", v, bi_edge(a, v, 0, LEN(a) - 1));

        return 0;
}

int bi_edge(int a[], int v, int left, int right)
{
        int mid;
        while (left <= right) {
                mid = (left + right) / 2;
                if (a[mid] <= v)
                        left = mid + 1;
                else
                        right = mid - 1;
        }
        return left;
}
