#include <cstdio>

const int N = 10;

void func(char data[], int index[], int m)
{
        for (int i = 0; i < m; ++i)
                printf("%c%c", data[index[i]], i == m - 1 ? '\n' : ' ');
}

void choose(char data[], int n, int m, int level = 0);

int main()
{
        char ch[N] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
        int n, m;
        scanf("%d %d", &n, &m);

        choose(ch, n, m);

        return 0;
}

void choose(char data[], int n, int m, int level)
{
        static int *index;

        if (level == 0) index = new int[m]();

        if (level == m) {
                func(data, index, m);
                return;
        }

        int start = level == 0 ? 0 : index[level-1] + 1;
        for (int i = start; i < n; ++i) {
                index[level] = i;
                choose(data, n, m, level + 1);
        }

        if (level == 0) delete [] index;
}
