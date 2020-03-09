#include <cstdio>

const double EPS = 1e-6;
const double ACC = 1e-2;

inline bool is_zero(double x) { return x <= EPS && x >= -EPS; }

double poly(double e[], double x);

double solve(double e[], double left, double right, bool inc);

int main()
{
	double e[4];
	scanf("%lf %lf %lf %lf", &e[3], &e[2], &e[1], &e[0]);

	double s[3];	// 三个解
	int cnt = 0;	// 已经获得的解个数
	double left, right, lvalue, rvalue;
	bool inc;	// 是否递增
	// 共有200个长度为1的子区间，分别为[-100,-99], ..., [99,100]
	for (int i = -100; i < 100; ++i) {
		left = (double)i;
		right = (double)(i+1);
		lvalue = poly(e, left);
		if (is_zero(lvalue)) {	// 左端点是一个解
			s[cnt++] = left;	// 记录解
			if (cnt == 3) break;	// 已找到3个解，直接退出求解过程
			// 若左端点是一个解，那么下一个解至少是右端点
			// 但是右端点是下一个区间的左端点，所以可以直接
			// 跳转到下一轮循环去，在下一轮循环中会先检查这
			// 个点的，本轮循环就不用管了
			continue;
		}
		// 现在已经排除了左端点为解的情况，再来判断右端点
		rvalue = poly(e, right);
		if (is_zero(rvalue)) {	// 右端点是一个解
			s[cnt++] = right;	// 记录解
			if (cnt == 3) break;	// 已找到3个解，直接退出求解过程
			// 若右端点是一个解，那么下一个可能的解至少是
			// 下一个区间的右端点，也是下下个区间的左端点
			// 所以可以直接跳过下一个区间，进入下下轮
			++i;
			continue;
		}
		// 现在已经排除了两个端点处是解的情况，可以进行本区间有无解了
		if (lvalue < 0 && rvalue > 0)
			inc = true;	// 本区间递增，有一解
		else if (lvalue > 0 && rvalue < 0)
			inc = false;	// 本区间递减，有一解
		else
			continue;	// 左右端点值同号，本区间内无解
		// 现在可以确定本区间内有一个根了，调用二分迭代法求根
		s[cnt++] = solve(e, left, right, inc);
		if (cnt == 3) break;
	}
	// 上述算法过程在一种特殊条件下会遗漏一个根：
	// 如果最后两个根是99.0和100.0，最后一个区间[99,100]会在判断到左端点是
	// 一个根后就continue，然后整个算法过程结束，最后一个根100.0会被遗漏。
	// 会遗漏最后一个根的唯有这一种情况，被遗漏的根必是100.0
	if (cnt == 2) s[2] = 100.0;
	printf("%.2lf %.2lf %.2lf\n", s[0], s[1], s[2]);
	
	return 0;
}

/*
 * 要计算的多项式可以进行如下变形：
 * P(x) = e[0] + e[1] * x + e[2] * x^2 + e[3] * x^3
 *      = e[0] + x * (e[1] + e[2] * x + e[3] * x^2)
 *      = e[0] + x * (e[1] + x * (e[2] + e[3] * x))
 * 所以，我们可以这样来进行循环计算：
 * P_0(x) = e[3]
 * P_1(x) = e[2] + P_0(x) * x
 * P_2(x) = e[1] + P_1(x) * x
 * P_3(x) = e[0] + P_2(x) * x
 * 最后得到的 P(x) = P_3(x)，只需要进行3次乘法
 * 注意：题目中的参数 a, b, c, d 对应的是 e[3], e[2], e[1], e[0]
 */
double poly(double e[], double x)
{
	double p = e[3];
	for (int i = 2; i >= 0; --i)
		p = x * p + e[i];
	return p;
}

// 标准的二分迭代法求根
double solve(double e[], double left, double right, bool inc)
{
	double mid, mvalue;
	while (right - left > ACC) {
		mid = (left + right) / 2.0;
		mvalue = poly(e, mid);
		if (is_zero(mvalue)) return mid;
		if ((mvalue < 0 && inc) || (mvalue > 0 && !inc))
			left = mid;
		else
			right = mid;
	}
	return (left + right) / 2.0;
}

