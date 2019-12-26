#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

struct BigInt {
	static const int _BASE = 10000;
	static const int _WIDTH = 4;
	vector<int> _s;

	void _assign(unsigned long long value);
	void _assign(const string &str);
	BigInt &_add(BigInt &b1, const BigInt &b2);

	BigInt(unsigned long long value = 0) { _assign(value); }
	BigInt(const string &str) { _assign(str); }

	BigInt &operator=(unsigned long long value) {
		_s.clear();
		_assign(value);
		return *this;
	}

	BigInt &operator=(const string &str) {
		_s.clear();
		_assign(str);
		return *this;
	}

	BigInt &operator+=(const BigInt &a) { return _add(*this, a); }
};

ostream &operator<<(ostream &os, const BigInt &bi);
istream &operator>>(istream &is, BigInt &bi);

void BigInt::_assign(unsigned long long value) {
	_s.push_back(value % _BASE);
	while (value /= _BASE)
		_s.push_back(value % _BASE);
}

void BigInt::_assign(const string &str) {
	int p = str.size(), h, v;
	if (p == 0)
		_s.push_back(0);
	else
		while (p > 0) {
			h = p >= _WIDTH ? p - _WIDTH : 0;
			v = 0;
			while (p > h) v = v * 10 + str[h++] - '0';
			_s.push_back(v);
			p -= _WIDTH;
		}
	while (_s.size() > 1 && _s.back() == 0) _s.pop_back();
}

ostream &operator<<(ostream &os, const BigInt &bi)
{
	int i = bi._s.size();
	os << bi._s[--i];
	while (--i >= 0)
		os << right << setw(4) << setfill('0') << bi._s[i];

	return os;
}

istream &operator>>(istream &is, BigInt &bi)
{
	string str;
	is >> str;
	bi._s.clear();
	bi._assign(str);

	return is;
}

BigInt &BigInt::_add(BigInt &b1, const BigInt &b2)
{
	while (b1._s.size() < b2._s.size()) b1._s.push_back(0);
	int carry = 0, i = 0;
	while (i < b1._s.size()) {
		b1._s[i] += carry;
		b1._s[i] += (i < b2._s.size() ? b2._s[i] : 0);
		carry = b1._s[i] / _BASE;
		b1._s[i] %= _BASE;
		i++;
	}
	if (carry) b1._s.push_back(carry);

	return b1;
}

int main()
{
	BigInt b1, b2;
	cin >> b1 >> b2;
	cout << (b1 += b2) << endl;
	cout << b1 << endl;
	cout << b2 << endl;
	
	return 0;
}
