#include <cstdio>

int main()
{
	int n;
	scanf("%d", &n);

	int last_ht = 0, ht, ans = 0;
	while (n--) {
		scanf("%d", &ht);
		if (ht > last_ht)
			ans += ht - last_ht;
		last_ht = ht;
	}
	printf("%d\n", ans);

	return 0;
}

