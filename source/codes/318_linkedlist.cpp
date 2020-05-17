#include <cstdio>

template<typename T>
struct LinkedList {
	// 节点结构，内部结构
	struct _Node {
		T _value;			// 元素值
		LinkedList<T>::_Node *_next;	// 后继链指针

		// 构造函数
		_Node() { _next = NULL; }
		_Node(const T &val) { _value = val; _next = NULL; }
	};

	// 模仿STL容器的迭代器，包装节点指针为一个可迭代的类型
	struct Index {
		LinkedList<T>::_Node *_ptr;

		// 构造器
		Index(LinkedList<T>::_Node *p = NULL) { _ptr = p; }
		// 重载解指针运算'*'，直接返回节点中的元素值
		T &operator*() { return _ptr->_value; }
		// 重载++运算，实现向后迭代
		Index &operator++() { _ptr = _ptr ? _ptr->_next : NULL; return *this; }
		Index operator++(int) {
			Index temp = *this;
			_ptr = _ptr ? _ptr->_next : NULL;
			return temp;
		}
		// 判断节点指针是否为空，用于判断迭代结束
		bool end() const { return _ptr == NULL; }
	};

	LinkedList<T>::_Node *_head;	// 头指针
	int _size;			// 表长度

	// 构造函数
	LinkedList() { _size = 0; _head = new LinkedList<T>::_Node; }
	// 基本功能
	int size() const { return _size; }
	bool empty() const { return _size == 0; }
	void clear();
	// 迭代访问
	LinkedList<T>::Index begin() const { return LinkedList<T>::Index(_head->_next); }
	// 元素访问
	T &operator[](int i);
	T &front() { return _head->_next->_value; }
	// 增加删除
	void push_front(const T &val);
	void insert(const T &val, const LinkedList<T>::Index prev);
	void pop_front();
	void erase(LinkedList<T>::Index prev);
	// 析构函数
	~LinkedList();
};

template<typename T>
void LinkedList<T>::clear()
{
	LinkedList<T>::_Node *p = _head->_next, *next;
	while (p) {
		next = p->_next;
		delete p;
		p = next;
	}
	_size = 0;
	_head->_next = NULL;
}

template<typename T>
T &LinkedList<T>::operator[](int i)
{
	LinkedList<T>::_Node *h = _head->_next;
	while (i--) h = h->_next;
	return h->_value;
}

template<typename T>
void LinkedList<T>::push_front(const T &val)
{
	LinkedList<T>::_Node *new_node = new LinkedList<T>::_Node(val);
	new_node->_next = _head->_next;
	_head->_next = new_node;
	++_size;
}

template<typename T>
void LinkedList<T>::insert(const T &val, const LinkedList<T>::Index prev)
{
	LinkedList<T>::_Node *new_node = new LinkedList<T>::_Node(val);
	new_node->_next = prev._ptr->_next;
	prev._ptr->_next = new_node;
	++_size;
}

template<typename T>
void LinkedList<T>::pop_front()
{
	if (_size == 0) return;
	LinkedList<T>::_Node *node = _head->_next;
	_head->_next = node->_next;
	delete node;
	--_size;
}

template<typename T>
void LinkedList<T>::erase(LinkedList<T>::Index prev)
{
	LinkedList<T>::_Node *node = prev._ptr->_next;
	prev._ptr->_next = node->_next;
	delete node;
	--_size;
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	LinkedList<T>::_Node *p = _head, *next;
	while (p) {
		next = p->_next;
		delete p;
		p = next;
	}
}

struct Point {
	double x, y;

	Point(double x = 0.0, double y = 0.0) { this->x = x; this->y = y; }
	void show() { printf("(%.3f, %.3f)\n", x, y); }
};

int main()
{
	LinkedList<Point> lst;
	printf("lst.size() = %d\n", lst.size());
	printf("lst.empty() = %s\n", lst.empty() ? "true" : "false");
	LinkedList<Point>::Index ptr = lst.begin();
	while (!ptr.end()) (*ptr++).show();

	lst.push_front(Point(1.0, 2.0));
	lst.push_front(Point(3.0, 4.0));
	lst.push_front(Point(3.1416, 2.7818));
	printf("======================\n");
	printf("lst.size() = %d\n", lst.size());
	printf("lst.empty() = %s\n", lst.empty() ? "true" : "false");
	ptr = lst.begin();
	while (!ptr.end()) (*ptr++).show();

	ptr = lst.begin();
	lst.insert(Point(-1.0, -2.0), ptr);
	++ptr;
	++ptr;
	lst.insert(Point(0, 0), ptr);
	printf("======================\n");
	printf("lst.size() = %d\n", lst.size());
	printf("lst.empty() = %s\n", lst.empty() ? "true" : "false");
	ptr = lst.begin();
	while (!ptr.end()) (*ptr++).show();

	printf("======================\n");
	printf("pop front element ");
	lst.front().show();
	lst.pop_front();
	printf("lst.size() = %d\n", lst.size());
	printf("lst.empty() = %s\n", lst.empty() ? "true" : "false");
	ptr = lst.begin();
	while (!ptr.end()) (*ptr++).show();

	printf("======================\n");
	ptr = lst.begin();
	ptr++;
	printf("erase the next element of ");
	(*ptr).show();
	lst.erase(ptr);
	printf("lst.size() = %d\n", lst.size());
	printf("lst.empty() = %s\n", lst.empty() ? "true" : "false");
	ptr = lst.begin();
	while (!ptr.end()) (*ptr++).show();

	printf("======================\n");
	printf("clear the list\n");
	lst.clear();
	printf("lst.size() = %d\n", lst.size());
	printf("lst.empty() = %s\n", lst.empty() ? "true" : "false");
	ptr = lst.begin();
	while (!ptr.end()) (*ptr++).show();

	return 0;
}
