#include <iostream>

int digit_at(int num, int d)
{
	while (--d) num /= 10;
	return num % 10;
}

long long reverse(int n)
{
	long long r = n % 10;
	while (n /= 10) r = 10 * r + n % 10;
	return r;
}

bool is_palin_num(int n)
{
	return reverse(n) == (long long)n;
}

int main()
{
	using namespace std;

	int num;
	cin >> num;

	for (int i = 1; i <= 10; i++)
		cout << digit_at(num, i) << endl;
	cout << "=================" << endl << reverse(num) << endl;
	cout << "is " << (is_palin_num(num) ? "" : "not")
		<< " a palindrom" << endl;

	return 0;
}
