#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>

const int MAXTOKENS = 100;

struct Token {
	char op;	// 运算符
	int num;	// 运算数
	bool is_op;	// 是否为运算符：+-*/()
};

// 优先级比较
// op1 == op2: 返回0
// op1 < op2 : 返回-1
// op1 > op2 : 返回1
inline int comp(char op1, char op2)
{
	return ((op1 == '+' || op1 == '-') ? 0 : 1) - ((op2 == '+' || op2 == '-') ? 0 : 1);
}

// 解析表达式字符串为token序列
// expr: 表达式字符串
// tokens: 解析得到的token序列数组
// 返回值: 解析得到的token数量
int parse(char *expr, Token tokens[]);

// 将中缀表达式token序列转换为后缀表达式token序列
// tokens: 中缀表达式token序列
// len: 中缀表达式token序列长度
// 返回值: 后缀表达式token序列长度
// 转换得到的后缀表达式token序列仍然存放在数组tokens中
int postfix(Token tokens[], int len);

// 计算后缀表达式的值
double eval(Token tokens[], int len);

int main()
{
	char expr[301];
	fgets(expr, sizeof(expr), stdin);
	Token tokens[MAXTOKENS];

	int len = parse(expr, tokens);
	len = postfix(tokens, len);
	printf("%lf\n", eval(tokens, len));

	return 0;
}

int parse(char *expr, Token tokens[])
{
	int len = 0, i = 0;	// len: tokens下标，i: 字符下标
	int num, sgn = 1;	// num: 数值，sgn: 符号
	bool start = true;
	while (expr[i]) {
		switch (expr[i]) {
			case '+':
			case '-':
				if (start) {
					sgn = expr[i++] == '+' ? 1 : -1;
					start = false;
				} else {
					tokens[len].is_op = true;
					tokens[len++].op = expr[i++];
					sgn = 1;
				}
				break;
			case '*':
			case '/':
			case ')':
			case '(':
				tokens[len].is_op = true;
				tokens[len++].op = expr[i];
				start = expr[i++] == '(';
				sgn = 1;
				break;
			default:
				if (isdigit(expr[i])) {
					num = expr[i] - '0';
					while (isdigit(expr[++i]))
						num = num * 10 + (expr[i] - '0');
					tokens[len].is_op = false;
					tokens[len++].num = num * sgn;
					sgn = 1;
					start = false;
				} else {
					++i;
				}
		}
	}
	return len;
}

int postfix(Token tokens[], int len)
{
	Token s1[MAXTOKENS], s2[MAXTOKENS];
	int len1 = 0, len2 = 0;
	for (int i = 0; i < len; ++i)
		if (tokens[i].is_op)
			switch (tokens[i].op) {
				case '+':
				case '-':
				case '*':
				case '/':
					while (len1 > 0 && s1[len1-1].op != '(' &&
						comp(tokens[i].op, s1[len1-1].op) != 1)
						s2[len2++] = s1[--len1];
					s1[len1++] = tokens[i];
					break;
				case '(':
					s1[len1++] = tokens[i];
					break;
				case ')':
					while (len1 > 0 && s1[len1-1].op != '(')
						s2[len2++] = s1[--len1];
					--len1;
					break;
				default: ;
			}
		else
			s2[len2++] = tokens[i];

	while (len1 > 0) s2[len2++] = s1[--len1];
	memcpy(tokens, s2, len2 * sizeof(Token));
	return len2;
}

double eval(Token tokens[], int len)
{
	double s[MAXTOKENS];
	int top = 0;
	for (int i = 0; i < len; ++i)
		if (tokens[i].is_op) {
			switch (tokens[i].op) {
				case '+':
					s[top-2] += s[top-1];
					break;
				case '-':
					s[top-2] -= s[top-1];
					break;
				case '*':
					s[top-2] *= s[top-1];
					break;
				case '/':
					s[top-2] /= s[top-1];
					break;
				default: ;
			}
			--top;
		} else s[top++] = tokens[i].num;
	return s[0];
}

