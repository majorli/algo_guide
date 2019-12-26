#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

struct BigInt {
	static const int _BASE = 10000;
	static const int _WIDTH = 4;
	vector<int> _s;
	// 内部功能函数
	void _assign(unsigned long long value);
	void _assign(const string &str);
	// 辅助功能函数
	bool zero() const { return _s.size() == 1 && _s[0] == 0; }
	// 构造器
	BigInt(unsigned long long value = 0) { _assign(value); }
	BigInt(const string &str) { _assign(str); }
	// 赋值运算
	BigInt &operator=(unsigned long long value)
	{
		_s.clear();
		_assign(value);
		return *this;
	}
	BigInt &operator=(const string &str)
	{
		_s.clear();
		_assign(str);
		return *this;
	}
	// 加法运算
	BigInt &operator+=(const BigInt &a);
	BigInt operator+(const BigInt &a) const
	{
		BigInt temp = a;		// 生成一个临时的BigInt变量等于加数a
		return temp += *this;		// 直接返回temp加上自身之后的值
	}
	BigInt &operator++() { return *this += 1; }	// 前置++
	BigInt operator++(int)				// 后置++
	{
		BigInt temp = *this;
		*this += 1;
		return temp;
	}
	// 乘法运算
	BigInt operator*(const BigInt &a) const;
	BigInt &operator*=(const BigInt &a) { return *this = *this * a; }
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

BigInt &BigInt::operator+=(const BigInt &a)
{
	if (_s.size() < a._s.size())		// 把长度调整到不短于a，方法是在高位补0
		_s.resize(a._s.size(), 0);	// 使用vector容器的resize成员函数一次性补足
	int carry = 0, i = 0;			// carry：进位数，初始为0
	while (i < _s.size()) {			// 循环到所有节全部计算完为止
		_s[i] += (i < a._s.size() ? a._s[i] : 0);	// a有可能比自己更短
		_s[i] += carry;			// 加上从前面来的进位
		carry = _s[i] / _BASE;		// 本节产生的进位
		_s[i] %= _BASE;			// 本节的和
		i++;				// 进入下一节
	}
	if (carry) _s.push_back(carry);		// 最后有可能还有一次进位，要进成更高的一节

	return *this;
}

BigInt BigInt::operator*(const BigInt &a) const
{
	BigInt p;				// 积
	if (zero() || a.zero()) return p;	// 特判
	int size1 = _s.size(), size2 = a._s.size();
	int d1, d2, carry;
	p._s.resize(size1 + size2, 0);		// 将积的节数设置为最大可能，初始值全部为0
	for (d2 = 0; d2 < size2; ++d2) {	// 乘数从最低到最高各节循环
		if (a._s[d2] == 0) continue;	// 乘数遇到等于0的节，直接跳到下一节
		carry = 0;			// 开始一轮部分乘，进位数清零
		for (d1 = 0; d1 < size1; ++d1) {	// 自己从最低到最高各节循环
			p._s[d2+d1] += (a._s[d2] * _s[d1]);// 乘数的节号同时是本次部分积的左移量
			p._s[d2+d1] += carry;		// 加上从前面来的进位
			carry = p._s[d2+d1] / _BASE;	// 新的进位数
			p._s[d2+d1] %= _BASE;		// 从该节中去除进位部分
		}
		if (carry) p._s[d2+d1] = carry;		// 最后有可能还有一次向更高位的进位
	}
	while (p._s.size() > 1 && p._s.back() == 0) p._s.pop_back();

	return p;
}

int main()
{
	BigInt b1 = 4, b2 = 8;
	cout << b1 << " + " << b2 << " = " << b1 + b2 << endl;

	cout << b1 << endl;
	for (int i = 1; i <= 50; i++)
		cout << (b1 += b1) << endl;

	int x = 13;
	cout << b1 + (b2 += x) << endl;
	cout << b1 << endl << b2 << endl;

	return 0;
}
