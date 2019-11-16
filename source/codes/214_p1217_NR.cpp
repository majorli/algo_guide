#include <iostream>

using namespace std;

bool is_prime(int a);
bool is_palindrome(int n);

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

	for (int i = a; i <= b; i++) {
		if (i % 2 == 0 || i % 3 == 0 || i % 5 == 0 || i % 7 == 0)
			continue;
		if (is_palindrome(i) && is_prime(i))
			cout << i << endl;
	}

	return 0;
}

bool is_prime(int a)
{
	bool prime = true;
	for (int i = 11; i * i <= a && (prime = a % i); i++);

	return prime;
}

bool is_palindrome(int n)
{
	long long ori = n, rev = n % 10;
	while (n /= 10)
		rev = rev * 10 + n % 10;

	return ori == rev;
}

