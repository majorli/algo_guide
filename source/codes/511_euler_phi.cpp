#include <cstdio>

const int MAXN = 1e6;

int phi_erato[MAXN];			// 埃氏筛打phi函数值的表
int phi_euler[MAXN], primes[MAXN];	// 欧拉筛打phi函数值的表，已知质数表

int phi(int n)
{
	if (n == 0) return 0;		// 特判：输入数据错误
	if (n == 1) return 1;		// 特判：phi(1) = 1
	
	int p = 2, phi = n;
	while (n > 1) {
		if (n % p == 0) {	// p一定是一个质数
			phi -= phi /p;	// 相当于phi = phi * (1 - 1 / p)
			// 除尽n中的所有p，确保下一个能被n整除的p一定是质数
			while (n % p == 0) n /= p;
		}
		p++;
	}
	return phi;
}

void phi_by_erato_seive(int n)
{
	// 初始化为phi[i] = i，一方面先保存好原数值
	// 另一方面作为该数是否被处理过的标志
	for (int i = 1; i <= n; i++)
		phi_erato[i] = i;

	for (int i = 2; i <= n; i++) {
		// 从2开始依序逐一处理，遇到phi[i] == i的则表示i一定是质数
		if (phi_erato[i] == i) {
			phi_erato[i]--;	// 质数的phi值为自己减1
			// 从i的2倍开始对范围内所有i的倍数进行处理，即乘上
			// 关于质因数i的项(1 - 1 / i)
			for (int j = 2; j * i <= n; j++)
				phi_erato[j*i] -= phi_erato[j*i] / i;
		}
	}
	return;
}

void phi_by_euler_seive(int n)
{
	// 初始化为phi[i] = i，一方面先保存好原数值
	// 另一方面作为该数是否被处理过的标志
	for (int i = 1; i <= n; i++)
		phi_euler[i] = i;

	int p = 0;		// 已知质数的个数
	for (int i = 2; i <= n; i++) {
		if (phi_euler[i] == i) {
			// 说明i是一个质数
			primes[p++] = i;
			phi_euler[i]--;
		}
		for (int j = 0; j < p && i * primes[j] <= n; j++) {
			if (i % primes[j] == 0) {
				// phi函数计算性质5
				phi_euler[i * primes[j]] =
					phi_euler[i] * primes[j];
				break;
			} else {
				// phi函数计算性质4
				phi_euler[i * primes[j]] =
					phi_euler[i] * phi_euler[primes[j]];
			}
		}
	}

	return;
}

int main()
{
	printf("compute phi(1) to phi(100) individually.\n");
	for (int n = 1; n <= 100; n++)
		printf("phi(%3d)=%3d%c", n, phi(n), n % 5 == 0 ? '\n' : ',');

	printf("compute phi[1] to phi[100] by erato seive.\n");
	phi_by_erato_seive(100);
	for (int n = 1; n <= 100; n++)
		printf("phi[%3d]=%3d%c", n, phi_erato[n],
				n % 5 == 0 ? '\n' : ',');

	printf("compute phi[1] to phi[100] by euler seive.\n");
	phi_by_euler_seive(100);
	for (int n = 1; n <= 100; n++)
		printf("phi[%3d]=%3d%c", n, phi_euler[n],
				n % 5 == 0 ? '\n' : ',');

	printf("diff:");
	int errors = 0;
	for (int i = 1; i <= 100; i++) {
		int p = phi(i);
		if (phi_erato[i] != p)
			printf("\n%3d: (phi_erato[%d] = %d) != (phi(%d) = %d)",
					++errors, i, phi_erato[i], i, p);
		if (phi_euler[i] != p)
			printf("\n%3d: (phi_euler[%d] = %d) != (phi(%d) = %d)",
					++errors, i, phi_euler[i], i, p);
	}
	if (errors)
		printf("\n%d differences found, check your program.\n", errors);
	else
		printf(" No error.\n");

	return 0;
}
