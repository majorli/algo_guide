#include <cstdio>

void print(int d[], int n);     // 输出数组 d[] 的前 n 个元素，用于调试

void bubble_sort(int d[], int n);

int main()
{
        int n, d[100];
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) scanf("%d", &d[i]);
        bubble_sort(d, n);

        printf("Bubble sort finished\n");
        print(d, n);

        return 0;
}

void bubble_sort(int d[], int n)
{
        int swap_cnt, tmp;
        for (int m = n; m > 1; --m) {
                swap_cnt = 0;
                for (int i = 0; i < m - 1; ++i) {
                        if (d[i] > d[i+1]) {
                                tmp = d[i];
                                d[i] = d[i+1];
                                d[i+1] = tmp;
                                ++swap_cnt;
                        }
                }
                if (!swap_cnt) return;
                // 调试语句
                printf("Bubble from d[0] to d[%d]: ", m - 1);
                print(d, n);
        }
}

void print(int d[], int n)
{
        printf("%d", d[0]);
        for (int i = 1; i < n; ++i) printf(" %d", d[i]);
        printf("\n");
}
