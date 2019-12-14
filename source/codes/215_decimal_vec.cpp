#include <cstdio>
#include <vector>

using namespace std;

int main()
{
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);

	if (!a) {
		printf("0\n");
		return 0;
	}

	bool neg = (a < 0 && b > 0) || (a > 0 && b < 0);
	a = a < 0 ? -a : a;
	b = b < 0 ? -b : b;

	vector<int> digits;
	digits.push_back(a / b);
	int r = a % b * 10;

	while (c-- && r) {
		digits.push_back(r / b);
		r = r % b * 10;
	}

	digits.back() += (r / b > 4);
	while (digits.size() > 1 && digits.back() == 10) {
		digits.pop_back();
		digits.back()++;
	}

	if (neg) printf("-");
	printf("%d", digits.front());
	if (digits.size() > 1) printf(".");
	vector<int>::iterator it = digits.begin() + 1;
	while (it != digits.end())
		printf("%d", *it++);
	printf("\n");
	
	return 0;
}

