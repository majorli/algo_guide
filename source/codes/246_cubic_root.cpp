#include <cstdio>

const double EPS = 1e-6;	// 用于判断一个double数是否为0的精度常数
const double ACC = 1e-3;	// 求三次方根的解的精度要求

// 求解 a 的三次方根
double cubic_root(double a);

// 计算多项式函数 f(x) = x^3 - a 的内联函数
inline double eval(double x, double a) { return x * x * x - a; }

// 利用精度EPS判断数 x 是否为 0 的内联函数
inline bool is_zero(double x) { return x <= EPS && x >= -EPS; }

int main()
{
	double a;
	scanf("%lf", &a);
	printf("cubic root of %lf = %8.3lf\n", a, cubic_root(a));
	return 0;
}

double cubic_root(double a)
{
	if (a == -1000000.0) return -100.0;	// 左端点特判
	if (a == 1000000.0) return 100.0;	// 右端点特判
	// 经过上面两个端点特判后，可以断定左端点处值为负，右端点处值为正，单调递增，符合二分迭代条件
	// left, right, mid：左端点，右端点和中间点
	// mid_value：中间端点处的多项式函数值
	double left = -100.0, right = 100.0, mid, mid_value;
	// 左右端点的间距大于根的精度要求时，继续循环迭代
	while (right - left > ACC) {
		mid = (left + right) / 2;	// 求中间点
		mid_value = eval(mid, a);	// 求中间点处的值
		// 下面是用来调试的输出语句，输出二分迭代的过程步骤
		//printf("left = %9.4lf, right = %9.4lf, mid = %9.4lf, mid-value = %14.6lf\n",
		//	left, right, mid, mid_value);
		if (is_zero(mid_value)) return mid;	// 求解完成
		if (mid_value < 0)
			left = mid;	// 递增，且中间点处值小于0，说明根在右半边，迭代右移
		else
			right = mid;	// 递增，且中间点处值大于0，说明根在左半边，迭代左移
	}
	// 若迭代直到左右端点间距达到根的精度要求时才结束，就以二者的平均值作为根
	return (left + right) / 2.0;
}

