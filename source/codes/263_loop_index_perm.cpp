#include <cstdio>

const int N = 10;

void func(char data[], int index[], int m)
{
	for (int i = 0; i < m; ++i)
		printf("%c%c", data[index[i]], i == m - 1 ? '\n' : ' ');
}

void perm(char data[], int n, int m, int level);

int main()
{
	int n, m;
	scanf("%d %d",&n, &m);
	char ch[N] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
	perm(ch, n, m, 0);

	return 0;
}

void perm(char data[], int n, int m, int level)
{
	static int *index;
	static bool *mask;

	if (level == 0) {
		index = new int[m]();
		mask = new bool[n]();
	}
	if (level == m) {
		func(data, index, m);
		return;
	}
	for (int i = 0; i < n; ++i) {
		if (mask[i]) continue;
		index[level] = i;
		mask[i] = true;
		perm(data, n, m, level + 1);
		mask[i] = false;
	}
	if (level == 0) {
		delete [] index;
		delete [] mask;
	}
}

