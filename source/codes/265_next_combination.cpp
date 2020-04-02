#include <cstdio>

const int N = 10;

bool next_combination(int index[], int n, int m);

int main()
{
        char ch[N] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
        int n, m;
        scanf("%d %d", &n, &m);

        int *index = new int[m]();
        for (int i = 0; i < m; ++i) index[i] = i;

        do {
                for (int i = 0; i < m; ++i)
                        printf("%c%c", ch[index[i]], i == m - 1 ? '\n' : ' ');
        } while (next_combination(index, n, m));

        return 0;
}

bool next_combination(int index[], int n, int m)
{
        int i = m - 1, max_val = n - 1;
        while (i >= 0 && index[i] == max_val) {
                --i;
                --max_val;
        }
        if (i < 0) return false;
        ++index[i];
        for (int j = i + 1; j < m; ++j)
                index[j] = index[j-1] + 1;
        return true;
}
