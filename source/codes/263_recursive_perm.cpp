#include <cstdio>

const int N = 10;

void func(char data[], int m)
{
        for (int i = 0; i < m; ++i)
                printf("%c%c", data[i], i == m - 1 ? '\n' : ' ');
}

inline void swap(char &a, char &b) { char t = a; a = b; b = t; }

void recursive_perm(char data[], int n, int m, int len = 0);

int main()
{
        char ch[N] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
        int n, m;
        scanf("%d %d", &n, &m);
        recursive_perm(ch, n, m);

        return 0;
}

void recursive_perm(char data[], int n, int m, int len)
{
        if (m == 0) {
                func(data - len, len);
                return;
        }
        for (int i = 0; i < n; ++i) {
                swap(data[i], data[0]);
                recursive_perm(data + 1, n - 1, m - 1, len + 1);
                swap(data[i], data[0]);
        }
}
