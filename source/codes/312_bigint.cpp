#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

struct BigInt {
	static const int _BASE = 10000;	// 基，每个节的数值范围为0-9999
	static const int _WIDTH = 4;	// 节数码宽度，每节4个十进制数码
	vector<int> _s;			// 用于存放数值的节向量，小端序存放
	// 内部功能函数
	void _assign(unsigned long long value);
	void _assign(const string &str);
	// 构造器
	BigInt(unsigned long long value = 0);
	BigInt(const string &str);
	// 辅助功能函数
	bool zero() const;		// 判断是不是等于0
	// 赋值运算
	BigInt &operator=(unsigned long long value);
	BigInt &operator=(const string &str);
	// 加法运算
	BigInt &operator+=(const BigInt &a);
	BigInt operator+(const BigInt &a) const;
	BigInt &operator++();		// 前置++
	BigInt operator++(int);		// 后置++
	// 乘法运算
	BigInt operator*(const BigInt &a) const;
	BigInt &operator*=(const BigInt &a);
	// 减法运算
	BigInt &operator-=(const BigInt &a);
	BigInt operator-(const BigInt &a) const;
	BigInt &operator--();		// 前置--
	BigInt operator--(int);		// 后置--
	// 比较运算
	bool operator<(const BigInt &a) const;
	bool operator>(const BigInt &a) const;
	bool operator<=(const BigInt &a) const;
	bool operator>=(const BigInt &a) const;
	bool operator==(const BigInt &a) const;
	bool operator!=(const BigInt &a) const;
	// 除法运算
	BigInt operator/(const BigInt &a) const;
	BigInt &operator/=(const BigInt &a);
	// 取余运算
	BigInt operator%(const BigInt &a) const;
	BigInt &operator%=(const BigInt &a);
};

// 输入输出流运算不能重载为成员函数，只能重载为普通函数
ostream &operator<<(ostream &os, const BigInt &bi);
istream &operator>>(istream &is, BigInt &bi);

// 以下为函数定义。算法编程中通常函数定义放在main()函数的后面，工程编程中则往往写在另一个单独的程序文件里
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

BigInt::BigInt(unsigned long long value) { _assign(value); }

BigInt::BigInt(const string &str) { _assign(str); }

bool BigInt::zero() const { return _s.size() == 1 && _s[0] == 0; }

BigInt &BigInt::operator=(unsigned long long value)
{
	_s.clear();
	_assign(value);
	return *this;
}

BigInt &BigInt::operator=(const string &str)
{
	_s.clear();
	_assign(str);
	return *this;
}

BigInt &BigInt::operator+=(const BigInt &a)
{
	if (_s.size() < a._s.size())		// 把长度调整到不短于a，方法是在高位补0
		_s.resize(a._s.size(), 0);	// 使用vector容器的resize成员函数一次性补足
	int carry = 0, i = 0;			// carry：进位数，初始为0
	while (i < _s.size()) {		// 循环到所有节全部计算完为止
		_s[i] += (i < a._s.size() ? a._s[i] : 0);	// a有可能比自己更短
		_s[i] += carry;			// 加上从前面来的进位
		carry = _s[i] / _BASE;		// 本节产生的进位
		_s[i] %= _BASE;			// 本节的和
		i++;				// 进入下一节
	}
	if (carry) _s.push_back(carry);	// 最后有可能还有一次进位，要进成更高的一节

	return *this;
}

BigInt BigInt::operator+(const BigInt &a) const
{
	BigInt temp = a;		// 生成一个临时的BigInt变量等于加数a
	return temp += *this;		// 直接返回temp加上自身之后的值
}

BigInt &BigInt::operator++() { return *this += 1; }

BigInt BigInt::operator++(int)
{
	BigInt temp = *this;
	*this += 1;
	return temp;
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
		if (carry) p._s[d2+d1] = carry;	// 最后有可能还有一次向更高位的进位
	}
	while (p._s.size() > 1 && p._s.back() == 0) p._s.pop_back();

	return p;
}

BigInt &BigInt::operator*=(const BigInt &a) { return *this = *this * a; }

BigInt &BigInt::operator-=(const BigInt &a)
{
	if (a.zero()) return *this;	// 特判，减数为0的情况

	while (_s.size() < a._s.size()) _s.push_back(0);	// 补齐被减数的长度
	_s.push_back(1);	// 被减数最高位上在增加一个节，以应对小数减大数的情况

	for (int i = 0; i < a._s.size(); i++) {	// 从低到高开始逐节相减
		_s[i] -= a._s[i];	// 对应的节相减
		if (_s[i] < 0) {	// 借位
			int j = i;	// 准备从低向高逐节去找最近那个能借出一个1的节
			while (_s[++j] == 0) _s[j] = _BASE - 1;	// 循环直到真正借到位
			_s[j]--;		// 被借走一个1
			_s[i] += _BASE;		// 加上借到的位
		}
	}
	// 去除被减数被增加的位并清除高位上的0
	do { _s.pop_back(); } while (_s.size() > 1 && _s.back() == 0);

	return *this;
}

BigInt BigInt::operator-(const BigInt &a) const
{
	BigInt temp = *this;
	return temp -= a;
}

BigInt &BigInt::operator--() { return *this -= 1; }

BigInt BigInt::operator--(int)
{
	BigInt temp = *this;
	*this -= 1;
	return temp;
}

bool BigInt::operator<(const BigInt &a) const
{
	if (_s.size() != a._s.size()) return _s.size() < a._s.size();
	for (int i = _s.size() - 1; i >= 0; --i)
		if (_s[i] != a._s[i]) return _s[i] < a._s[i];
	return false;
}

bool BigInt::operator>(const BigInt &a) const { return a < *this; }

bool BigInt::operator<=(const BigInt &a) const { return !(a < *this); }

bool BigInt::operator>=(const BigInt &a) const { return !(*this < a); }

bool BigInt::operator==(const BigInt &a) const { return _s == a._s; }

bool BigInt::operator!=(const BigInt &a) const { return _s != a._s; }

BigInt BigInt::operator/(const BigInt &a) const
{
	BigInt q;
	if (a.zero()) throw "divided by zero";	// 除数为0，抛出异常
	if (zero()) return q;			// 特判：被除数为0，直接返回0

	q._s.resize(_s.size(), 0);	// 预留商最多所需的节数，初始全0，商的长度最多和被除数相等
	BigInt part;		// 用做部分除的被除数
	int i = _s.size();	// 当前部分除进行到的位置
	while (--i >= 0) {	// 从最高节到最低节进行部分除，进入循环时i已经指向本次部分商应在的位置
		// 1. 取本次部分被除数，就是将被除数的当前节添加进part
		if (part.zero()) part = _s[i];
		else part._s.insert(part._s.begin(), _s[i]);
		// 2. 用多次减法模拟部分除，减到part小于除数为止
		while (part >= a) {
			part -= a;
			++q._s[i];	// 每减一次，部分商就加1
		}
	}
	while (q._s.size() > 1 && q._s.back() == 0) q._s.pop_back();

	return q;
}

BigInt &BigInt::operator/=(const BigInt &a) { return *this = *this / a; }

BigInt BigInt::operator%(const BigInt &a) const
{
	BigInt r;
	if (a.zero()) throw "divided by zero";	// 除数为0，抛出异常
	if (zero()) return r;			// 特判：被除数为0，直接返回0
	// 模拟一次整数竖式除法，但不用保留商
	int i = _s.size();
	while (--i >= 0) {
		if (r.zero()) r = _s[i];
		else r._s.insert(r._s.begin(), _s[i]);
		while (r >= a) r -= a;
	}
	return r;
}

BigInt &BigInt::operator%=(const BigInt &a) { return *this = *this % a; }

int main()
{
	return 0;
}
