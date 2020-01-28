#include <cstdio>
#include <cstring>

void compute_next_array(const char *p, int next[]);
int kmp_search(const char *s, const char *p);

int main()
{
	char s[1001], p[101];
	fgets(s, 1001, stdin);
	fgets(p, 101, stdin);
	int len_s = strlen(s), len_p = strlen(p);
	if (s[len_s-1] == '\n') s[--len_s] = '\0';	// 去除末尾可能存在的换行符
	if (p[len_p-1] == '\n') p[--len_p] = '\0';	// 去除末尾可能存在的换行符

	printf("%d\n", kmp_search(s, p));

	return 0;
}

void compute_next_array(const char *p, int next[])
{
	next[0] = -1;
	int j = 0, len = strlen(p);
	int k = next[j];
	while (j < len)
		if (k == -1 || p[k] == p[j])	// 递归终止，由next[j]推导出next[j+1]
			if (p[++j] == p[++k])	// 判断是否为坑，两个前置++确保先完成计算再判断
				next[j] = next[k];
			else
				next[j] = k;
		else
			k = next[k];		// 情况3，递归

	return;
}

int kmp_search(const char *s, const char *p)
{
	int next[101] = { -1 };
	compute_next_array(p, next);
	int i = 0, j = 0, len_s = strlen(s), len_p = strlen(p);
	while (j < len_p && len_s - i >= len_p - j)
		if (j == -1 || s[i] == p[j]) {
			++i;
			++j;
		} else {
			j = next[j];
		}
	if (j == len_p)
		return i - j;
	else
		return -1;
}

