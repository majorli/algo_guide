#include <cstdio>

template<typename T>
struct LinkedQueue {
	struct _Node {		// 元素节点的结构，嵌套在队列结构内部
		T _val;		// 元素值
		_Node *_next;	// 后继指针

		_Node() { _next = NULL; }	// 构造一个新的节点，后继为空
	};

	_Node *_head, *_tail;	// 头尾指针，注意可以省略命名限定 LinkedQueue<T>::
	int _size;		// 队列长度

	LinkedQueue()		// 构造一个新的空队列
	{
		_tail = new _Node;
		_head = _tail;
		_size = 0;
	}
	bool empty() const { return _head == _tail; }	// 判断队列是否为空
	int size() const { return _size; }	// 获取队列长度
	void enqueue(const T &val)		// 元素val入队
	{
		_tail->_val = val;
		_tail->_next = new _Node;
		_tail = _tail->_next;
		++_size;
	}
	T &head()				// 访问队头元素
	{
		if (_head == _tail) throw *this;
		return _head->_val;
	}
	void dequeue()				// 队头元素出队
	{
		if (_head == _tail) return;
		_Node *temp = _head;
		_head = temp->_next;
		delete temp;
		--_size;
	}
	~LinkedQueue()		// 析构函数，删除队列，销毁当前队列中所有节点
	{
		while (_head != _tail) dequeue();
		delete _tail;
	}
};

int main()
{
	LinkedQueue<int> q;
	for (int i = 0; i <= 10; i += 2) q.enqueue(i);
	while (!q.empty()) {
		printf("%d\n", q.head());
		q.dequeue();
	}
	printf("%d\n", q.head());

	return 0;
}
