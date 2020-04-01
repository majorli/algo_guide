#include <cstdio>
#include <algorithm>

const int N = 10;

void func(char data[], int index[], int n)
{
        for (int i = 0; i < n; ++i)
                printf("%c%c", data[index[i]], i == n - 1 ? '\n' : ' ');
}

inline void swap(int &a, int &b) { int t = a; a = b; b = t; }

bool next_perm(int index[], int n);

int main()
{
        int n;
        scanf("%d", &n);
        char ch[N] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };

        int *index = new int[n];
        for (int i = 0; i < n; ++i) index[i] = i;

        do {
                func(ch, index, n);
        } while (next_perm(index, n));

        delete [] index;

        return 0;
}

bool next_perm(int index[], int n)
{
        int i = n - 1;
        while (i > 0 && index[i-1] > index[i]) --i;
        if (i == 0) return false;
        --i;
        int k = n - 1;
        while (index[k] < index[i]) --k;
        swap(index[i], index[k]);
        std::sort(index + i + 1, index + n);
        return true;
}
