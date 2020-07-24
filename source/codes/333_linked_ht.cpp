#include <cstring>
#include <cstdio>
#include <ctime>
#include <cstdlib>

//const int MAXN = 2003;
//const int MAXN = 5003;
//const int MAXN = 10007;
const int MAXN = 20011;

struct LinkedHashTable {
	struct _Node {
		int _data;
		_Node *_next;

		_Node() { _next = NULL; }
		_Node(int data) { _data = data; _next = NULL; }
	};

	_Node *_table[MAXN];
	int _size;

	LinkedHashTable() { memset(_table, 0, sizeof(_table)); _size = 0; }
	~LinkedHashTable() { clear(); }

	bool empty() const { return !_size; }
	int size() const { return _size; }

	int _hash(int key) { return key % MAXN; }

	void add(int val);
	void remove(int val);
	void clear();
	bool contains(int val);

	double alpha() const { return (double)_size / MAXN; }
	double avg_steps() const;
};

int main()
{
	srand(time(NULL));
	LinkedHashTable t;
	double target = 0.1;
	while (t.size() <= MAXN * 6) {
		t.add(rand());
		if (t.alpha() >= target) {
			printf("size = %6d, alpha = %lf, avg_steps = %lf\n",
					t.size(), t.alpha(), t.avg_steps());
			t.size() < MAXN ? target += 0.1 : target += 1.0;
		}
	}

	return 0;
}

void LinkedHashTable::add(int val)
{
	int h = _hash(val);
	if (!_table[h]) {
		_Node *new_node = new _Node(val);
		_table[h] = new_node;
		++_size;
	} else {
		_Node *p = _table[h];
		while (p && p->_data != val) p = p->_next;
		if (p) return;
		_Node *new_node = new _Node(val);
		new_node->_next = _table[h];
		_table[h] = new_node;
		++_size;
	}
}

void LinkedHashTable::remove(int val)
{
	int h = _hash(val);
	_Node *p = _table[h], *prev = NULL;
	while (p && p->_data != val) {
		prev = p;
		p = p->_next;
	}
	if (!p) return;
	if (prev)
		prev->_next = p->_next;
	else
		_table[h] = p->_next;
	delete p;
	--_size;
}

void LinkedHashTable::clear()
{
	_Node *p;
	for (int h = 0; h < MAXN; ++h)
		while (_table[h]) {
			p = _table[h];
			_table[h] = p->_next;
			delete p;
		}
	_size = 0;
}

bool LinkedHashTable::contains(int val)
{
	int h = _hash(val);
	_Node *p = _table[h];
	while (p && p->_data != val) p = p->_next;
	return p != NULL;
}

double LinkedHashTable::avg_steps() const
{
	int steps = 0;
	for (int h = 0; h < MAXN; ++h) {
		int s = 0;
		_Node *p = _table[h];
		while (p) {
			steps += (++s);
			p = p->_next;
		}
	}
	return (double)steps / _size;
}
