#include <cstdio>
#include <cstring>

int main()
{
	char s[81];		// 原字符串
	int rows;		// 指定到Z字形行数
	scanf("%s", s);
	scanf("%d", &rows);
	int size = strlen(s);	// 原字符串长度
	if (rows == 1) {	// 特判：行数为1时，变形后与原串相同，直接输出即可
		puts(s);
		return 0;
	}
	int d = rows + rows - 2;	// 公差
	for (int i = 0; i < rows; ++i) {
		int j = i, k = d - j;	// j：主列字符位置首项，k：斜排字符位置首项
		while (j < size) {	// 因为输出是按先主列后斜排的顺序输出，所以只需控制主列字符位置
			putchar(s[j]);	// 输出主列字符
			if (i > 0 && i < rows - 1 && k < size) putchar(s[k]);	// 输出斜排字符
			j += d;		// 进入下一个主列
			k += d;		// 进入下一个斜排字符
		}
	}
	putchar('\n');

	return 0;
}
