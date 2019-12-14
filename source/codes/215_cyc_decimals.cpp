#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int a, b;
	cin >> a >> b;

	if (!a) {				// 特判，被除数为0
		cout << "0.(0)1" << endl;
		return 0;
	}

	bool neg = (a < 0 && b > 0) || (a > 0 && b < 0);
	a = a < 0 ? -a : a;
	b = b < 0 ? -b : b;

	vector<int> quo, rem_pos(b, 0);
	int pos = 1, r = a, cyc_start, cyc_end;
	while (true) {
		quo.push_back(r / b);
		r %= b;
		if (!r) {			// 余数为0，除尽
			quo.push_back(0);
			cyc_start = pos++;
			cyc_end = pos;
			break;
		} else if (rem_pos[r]) {	// 余数非零且第二次出现，循环节结束
			cyc_start = rem_pos[r];
			cyc_end = pos;
			break;
		} else {			// 余数非零且第一次出现，记录位置
			rem_pos[r] = pos++;	// 记录完成后，位置向后推进一位
			r *= 10;		// 余数自乘10，准备下一轮计算
		}
	}

	if (neg) cout << "-";
	cout << quo[0] << ".";
	pos = 1;
	while (pos < cyc_start)
		cout << quo[pos++];
	cout << "(";
	while (pos < cyc_end)
		cout << quo[pos++];
	cout << ")" << (cyc_end - cyc_start) << endl;

	return 0;
}
