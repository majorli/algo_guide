#include <cstdio>

int main()
{
	unsigned int n;
	scanf("%u", &n);

	unsigned int last_tem, tem;
	unsigned int cur_len = 0, max_len = 0;
	for (int i = 0; i < n; i++) {
		scanf("%u", &tem);
		if (tem > last_tem) {
			cur_len++;
		} else {
			if (cur_len > max_len)
				max_len = cur_len;
			cur_len = 1;
		}
		last_tem = tem;
	}
	if (cur_len > max_len)
		max_len = cur_len;
	printf("%u\n", max_len);

	return 0;
}
