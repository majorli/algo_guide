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

	BigInt &operator=(const BigInt &bi) {
		_s.clear();
		_s.assign(bi._s.begin(), bi._s.end());
		return *this;
	}
};

ostream &operator<<(ostream &os, const BigInt &bi);
istream &operator>>(istream &is, BigInt &bi);

int main()
{
	BigInt b1, b2(347), b3(123456789000012), b4(100001);
	cout << "Testing initialization" << endl;
	cout << "======================" << endl;
	cout << b1 << endl;	// 0
	cout << b2 << endl;	// 347
	cout << b3 << endl;	// 123456789000012
	cout << b4 << endl;	// 100001
	cout << "Testing assigning" << endl;
	cout << "======================" << endl;
	BigInt b5 = 0, b6 = 9207358;
	b1 = 37 + 73;
	cout << b1 << endl;		// 110
	cout << (b2 = 666) << endl;	// 666
	cout << (b3 = b4) << endl;	// 100001
	b4 = b6;
	cout << b4 << endl;		// 9207358
	cout << b5 << endl;		// 0
	cout << b6 << endl;		// 9207358
	cout << "Testing string init" << endl;
	cout << "======================" << endl;
	string s1 = "", s2 = "31415926535";
	BigInt b7(s1), b8("987654321012345678909876543210123456789000");
	cout << b7 << endl;		// 0
	cout << b8 << endl;		// 987654321012345678909876543210123456789000
	cout << "Testing string assign" << endl;
	cout << "======================" << endl;
	b7 = s2;
	b8 = "0";
	cout << b7 << endl;		// 31415926535
	cout << b8 << endl;		// 0
	cout << "Testing cin input" << endl;
	cout << "======================" << endl;
	cin >> b7;
	cout << b7 << endl;
	cin >> b7 >> b8;
	cout << b7 << " and " << b8 << endl;

	return 0;
}

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

