#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

//const int MAXN = 2003;
//const int MAXN = 5003;
//const int MAXN = 10007;
const int MAXN = 20011;

struct HashTable {
	int *_dp[MAXN];
	int _size;

	HashTable() { memset(_dp, NULL, sizeof(_dp)); _size = 0; }
	~HashTable()			// 析构函数，释放所有分配到的动态内存
	{
		for (int i = 0; i < MAXN; ++i)
			if (_dp[i]) delete _dp[i];
	}

	int _hash(int key) const { return key % MAXN; }	// 哈希函数，内部使用

	bool empty() const { return !_size; }
	int size() const { return _size; }

	int add(int value);			// 添加数据
	void remove(int value);		// 删除数据
	bool contains(int value) const;	// 判断数据是否存在
	void clear();				// 清空
};

int main()
{
	HashTable ht;
	srand(time(NULL));
	int total_probs = 0;
	double step = 0.05;
	while (ht.size() < MAXN) {
		total_probs += ht.add(rand());
		double alpha = (double)ht.size() / MAXN;
		if (alpha >= step) {
			printf("alpha = %lf, avg probs = %lf\n", alpha,
					(double)total_probs / ht.size());
			step += 0.05;
		}
	}
	printf("alpha = %lf, avg probs = %lf\n", step,
			(double)total_probs / ht.size());

	return 0;
}

// 返回值：探测次数，若是已经存在的则返回0，若已满则返回-1
int HashTable::add(int value)
{
	if (_size == MAXN) return -1;
	int probs = 1;
	int h = _hash(value);
	int pos = h;
	while (_dp[pos] && *_dp[pos] != value) {
		++pos;
		if (pos == MAXN) pos = 0;
		++probs;
	}
	if (!_dp[pos]) {
		_dp[pos] = new int;
		*_dp[pos] = value;
		++_size;
	} else {
		probs = 0;
	}

	return probs;
}

void HashTable::remove(int value)
{
	int h = _hash(value);
	int pos = h;
	while (_dp[pos] && *_dp[pos] != value) {
		++pos;
		if (pos == MAXN) pos = 0;
		if (pos == h) return;
	}
	if (_dp[pos]) {
		delete _dp[pos];
		_dp[pos] = NULL;
		--_size;
	}
}

bool HashTable::contains(int value) const
{
	int h = _hash(value);
	int pos = h;
	while (_dp[pos] && *_dp[pos] != value) {
		++pos;
		if (pos == MAXN) pos = 0;
		if (pos == h) return false;
	}
	if (_dp[pos]) return true;
	return false;
}

void HashTable::clear()
{
	for (int i = 0; i < MAXN; ++i) {
		if (_dp[i]) {
			delete _dp[i];
			_dp[i] = NULL;
		}
	}
	_size = 0;
}
