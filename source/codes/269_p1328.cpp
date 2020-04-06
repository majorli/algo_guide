#include <cstdio>

int main()
{
	const int A = 0, B = 1;		// 小A、小B的编号
	// 胜负规则表，rulues[a][b] 表示小A出a、小B出b 时谁获胜，平局二人都不加分
	const int rules[5][5] = {
		{ 2, B, A, A, B },
		{ A, 2, B, A, B },
		{ B, A, 2, B, A },
		{ B, B, A, 2, A },
		{ A, A, B, B, 2 } };
	int n, t[2], periods[2][200], bonus[3] = { 0 };
	// 读取游戏轮数、小A和小B的出拳周期长度
	scanf("%d %d %d", &n, &t[A], &t[B]);
	// 读取小A的出拳周期
	for (int i = 0; i < t[A]; ++i) scanf("%d", &periods[A][i]);
	// 读取小B的出拳周期
	for (int i = 0; i < t[B]; ++i) scanf("%d", &periods[B][i]);
	// 从 0 到 n - 1，模拟 n 轮出拳的情况，并查表得到获胜者，给获胜者加一分
	for (int i = 0; i < n; ++i)
		++bonus[rules[periods[A][i % t[A]]][periods[B][i % t[B]]]];
	// 输出结果
	printf("%d %d\n", bonus[A], bonus[B]);

	return 0;
}

