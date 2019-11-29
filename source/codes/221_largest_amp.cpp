#include <cstdio>

int main()
{
	int n;
	scanf("%d", &n);

	int last_data, data, cur_amp = 0, max_amp = 0;
	scanf("%d", &last_data);
	for (int i = 1; i < n; i++) {
		scanf("%d", &data);
		if (data > last_data) {
			cur_amp += data - last_data;
		} else {
			if (cur_amp > max_amp)
				max_amp = cur_amp;
			cur_amp = 0;
		}
		last_data = data;
	}
	if (cur_amp > max_amp)
		max_amp = cur_amp;

	printf("%d\n", max_amp);

	return 0;
}
