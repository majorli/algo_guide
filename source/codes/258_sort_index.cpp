#include <cstdio>

void index(int da[], int dx[], int n);

int main()
{
        int n;
        scanf("%d", &n);
        int *da = new int[n], *dx = new int[n];

        for (int i = 0; i < n; ++i) {
                scanf("%d", &da[i]);
                dx[i] = i;
        }
        index(da, dx, n);
        printf("%d", dx[0]);
        for (int i = 1; i < n; ++i) printf(" %d", dx[i]);
        printf("\n");

        delete [] da;
        delete [] dx;

        return 0;
}

void index(int da[], int dx[], int n)
{
        for (int i = 0; i < n; ++i)
                for (int j = i + 1; j < n; ++j)
                        if (da[i] > da[j]) { ++dx[i]; --dx[j]; }
}
