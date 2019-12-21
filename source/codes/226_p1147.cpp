#include <iostream>

using namespace std;

int main()
{
	int m;
	cin >> m;
	int mid = m / 2;
	int l = 1, r = 2, sum = 3;
	int loops = 0;
	while (l <= mid) {	// 为什么这里没有用第二个条件 (r <= mid + 1)？
		loops++;
		if (sum >= m) {
			if (sum == m)
				cout << l << " " << r << endl;
			sum -= l++;
			// 没有这句：if (l > r - 1) sum += ++r; 不需要推右端点？
		} else {
			sum += ++r;
		}
	}
	
	return 0;
}
