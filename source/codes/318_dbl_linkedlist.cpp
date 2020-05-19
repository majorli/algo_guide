#include <cstddef>

template<typename T>
struct DblLinkedList {
	struct _Node {
		T _value;
		DblLinkedList<T>::_Node *next;
		DblLinkedList<T>::_Node *prev;
		_Node() { /* TODO 构造节点 */ }
		_Node(const T &val) { /* TODO 使用val值构造节点 */ }
	};
	struct Indicator {
		DblLinkedList<T>::_Node *_ptr;
		Indicator(DblLinkedList<T>::_Node *p = NULL) { /* TODO 构造指示器 */ }
		T &operator*() { /* TODO 解指针 */ }
		Indicator &operator++() { /* TODO 前置向后迭代 */ }
		Indicator operator++(int) { /* TODO 后置向后迭代 */ }
		Indicator &operator--() { /* TODO 前置向前迭代 */ }
		Indicator operator--(int) { /* TODO 后置向前迭代 */ }
	};
	DblLinkedList<T>::_Node *_head;
	DblLinkedList<T>::_Node *_tail;
	int _size;
	DblLinkedList() { /* TODO 构造双链表 */ }
	int size() const { return _size; }
	bool empty() const { return _size == 0; }
	DblLinkedList<T>::Indicator begin() const { /* TODO 返回表首指示器 */ }
	DblLinkedList<T>::Indicator end() const { /* TODO 返回表尾指示器 */ }
	T &operator[](int i);	// TODO 使用下标值直接访问元素
	T &back();		// TODO 访问尾元素
	void push_front(const T &val);	// TODO 表首插入元素
	void push_back(const T &val);	// TODO 表尾添加元素
	void insert(const T &val, const DblLinkedList<T>::Indicator ind); // TODO 指示位置插入元素
	void pop_front();		// TODO 删除首元素
	void pop_back();		// TODO 删除尾元素
	void erase(DblLinkedList<T>::Indicator ind);	// TODO 删除指示器所指元素
	void clear();			// TODO 清空所有元素
	~DblLinkedList();		// TODO 析构函数
};
