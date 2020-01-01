#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

struct Person {
	int a;
	int b;

	bool operator<(const Person p) const;
};

struct BigInt {
	static const int _BASE = 10000;
	vector<int> _s;

	BigInt(int value);
	BigInt &operator*=(int a);
	BigInt operator/(int a) const;
	bool operator<(const BigInt &a) const;
};

ostream &operator<<(ostream &os, const BigInt &bi);

int main()
{
	vector<Person> persons;
	int n;
	cin >> n;
	for (int i = 0; i <= n; ++i) {
		Person p;
		cin >> p.a >> p.b;
		persons.push_back(p);
	}
	sort(persons.begin()+1, persons.end());

	BigInt left(persons[0].a);
	BigInt max(persons[0].a / persons[1].b);
	for (int i = 2; i <= n; ++i) {
		left *= persons[i-1].a;
		BigInt current = left / persons[i].b;
		if (max < current) max = current;
	}
	cout << max << endl;

	return 0;
}

bool Person::operator<(const Person p) const { return a * b < p.a * p.b; }

BigInt::BigInt(int value) { _s.push_back(value); }

BigInt &BigInt::operator*=(int a)
{
	int carry = 0;
	for (int i = 0; i < _s.size(); ++i) {
		_s[i] *= a;
		_s[i] += carry;
		carry = _s[i] / _BASE;
		_s[i] %= _BASE;
	}
	if (carry) _s.push_back(carry);
	return *this;
}

BigInt BigInt::operator/(int a) const
{
	BigInt q(0);
	q._s.resize(_s.size(), 0);
	int part = 0, i = _s.size();
	while (--i >= 0) {
		part = part * _BASE + _s[i];
		q._s[i] = part / a;
		part %= a;
	}
	while (q._s.size() > 1 && q._s.back() == 0) q._s.pop_back();
	return q;
}

bool BigInt::operator<(const BigInt &a) const
{
	if (_s.size() != a._s.size()) return _s.size() < a._s.size();
	for (int i = _s.size() - 1; i >= 0; --i)
		if (_s[i] != a._s[i]) return _s[i] < a._s[i];
	return false;
}

ostream &operator<<(ostream &os, const BigInt &bi)
{
	int i = bi._s.size();
	os << bi._s[--i];
	while (--i >= 0)
		os << right << setw(4) << setfill('0') << bi._s[i];

	return os;
}

