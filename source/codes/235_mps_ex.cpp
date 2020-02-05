#include <cstdio>
#include <cstring>
#include <ctime>

int expand(const char *s, int left, int right);

int main()
{
	char s[100010];
	scanf("%100009s", s);

	clock_t start, end;
	start = clock();

	int sz = strlen(s);
	// len1, len2: 以s[i]为中心和以s[i]s[i+1]中间的空隙为中心进行的两次中心扩展得到的回文子串长度
	// len1最小为1，因为单个字符s[i]肯定是回文串
	// len2最小为0，如果s[i] != s[i+1]，那么len2就等于0
	// len：取len1和len2中的大者
	// maxlen：保存下来的到目前为止找到的最长回文子串长度
	// left：保存下来的到目前为止找到的最长回文子串的起始位置（左端点）
	// maxlen初始为1，left初始为0，表示至少字符s[0]肯定是一个回文子串
	int len1, len2, len, maxlen = 1, left = 0;
	for (int i = 0; i < sz; ++i) {
		len1 = expand(s, i, i);		// 以s[i]为中心进行扩展
		len2 = expand(s, i, i+1);	// 以s[i]和s[i+1]中间的空隙为中心进行扩展
		len = len1 > len2 ? len1 : len2;// 取两次扩展得到的回文子串长度中的大者
		if (len > maxlen) {		// 若len大于已知的最长回文子串，则更新maxlen和left
			maxlen = len;
			// 假设len来自于len1，表示以s[i]为中心的长度为len的子串为
			//     目前已知的最长回文子串，此时len必为奇数，最小值为1
			//     设len = len1 = 2 * k + 1，(k=0,1,2,...)
			//     那么此回文子串为s[i-k]...s[i]...s[i+k]
			//     即第一个字符的位置为left = i - k = i - (len - 1) / 2
			// 假设len来自于len2，表示以s[i]和s[i+1]为中心的长度为len的子串为
			//     目前已知的最长回文子串，此时len必为偶数。由于len1至少为1，
			//     而现在len2比len1更大，所以len最小值为2
			//     设len = len2 = 2 * k，(k=1,2,...)
			//     那么此回文子串为s[i-k+1]...s[i]s[i+1]...s[i+k]
			//     即第一个字符的位置为i - k + 1 = i - (k - 1)
			//     因为len为偶数，利用C++整数除法只取商的特性，有：
			//     (len - 1) / 2 = (2*k - 1) / 2 = k - 1
			//     所以这种情况下，同样有left = i - (len - 1) / 2
			left = i - (len - 1) / 2;
		}
	}
	
	end = clock();

	while (maxlen--) putchar(s[left++]);	// 从s[left]开始连续输出maxlen个字符
	putchar('\n');

	printf("time elapsed = %ld ms.\n", (end - start) / (CLOCKS_PER_SEC / 1000));

	return 0;
}

int expand(const char *s, int left, int right)
{
	// left >= 0：表示左边的端点还在字符串s范围内
	// s[right]：利用C-string最后一个字符后面是结束标志'\0'的特点，只要s[right] != 0，就表示还在
	//           字符串s的范围之内。
	// s[left] == s[right]：扩展的两端相等，所以还可以进一步尝试扩展
	while (left >= 0 && s[right] && s[left] == s[right]) {
		--left;		// 进一步扩展左端点
		++right;	// 进一步扩展右端点
	}
	return right - left - 1;	// 能扩展到的最长回文子串长度
}
