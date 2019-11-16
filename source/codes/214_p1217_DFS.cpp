#include <iostream>

using namespace std;

bool is_prime(int a);
int palindromes(int size, int pos, int lb, int ub);

int digits[4];

int main()
{
	int a, b;
	cin >> a >> b;

	if (a <= 5 && b >= 5)
		cout << "5" << endl;
	if (a <= 7 && b >= 7)
		cout << "7" << endl;
	if (a <= 11 && b >= 11)
		cout << "11" << endl;
	a = a > 101 ? a : 101;
	b = b > 9989899 ? 9989899 : b;

	for (int size = 3; size <= 7; size += 2)
		palindromes(size, 0, a, b);

	return 0;
}

bool is_prime(int a)
{
	bool prime = true;
	for (int i = 3; i * i <= a && (prime = a % i); i++);

	return prime;
}

int palindromes(int size, int pos, int lb, int ub)
{
	for (int d = 0; d < 10; d++) {
		if (pos == 0 && (d % 2 == 0 || d == 5))
			continue;
		digits[pos] = d;
		if (pos == size / 2) {
			int palin = 0;
			for (int j = 0; j <= pos; j++)
				palin = palin * 10 + digits[j];
			for (int j = pos - 1; j >= 0; j--)
				palin = palin * 10 + digits[j];
			if (palin >= lb && palin <= ub && is_prime(palin))
				cout << palin << endl;
		} else {
			palindromes(size, pos + 1, lb, ub);
		}
	}

	return 0;
}
