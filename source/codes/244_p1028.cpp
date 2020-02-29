#include <cstdio>

int main()
{
	int n, count[1002] = { 1, 1 };	// C(0) = C(1) = 1
	scanf("%d", &n);
	int i = 2;
	// 从C(2)开始向后递推，每次推算2个数，直到超过n
	// 由于最大可能n=1000，每次循环判断时i为偶数，所以最后一次循环
	//   时i最大可能为1000，向后再推导一个，最多会算到第1001个数，
	//   因此数组count至少开到1002的长度就够了
	while (i <= n) {
		// 从2开始，每次推2个数，所以第一次推算i一定为偶数
		// 使用递推规则(B)：C(2k) = C(2k-1) + C(k) 推算C(i)
		count[i] = count[i-1] + count[i / 2];
		// 使用递推规则(A)：C(2k+1) = C(2k) 直接得到C(i+1)
		count[i+1] = count[i];
		i += 2;
	}
	printf("%d\n", count[n]);

	return 0;
}

