#include <cstddef>
#include <cstring>
#include <cstdio>

typedef unsigned int Node;	// 用数组下标来代指节点，定义一个类型别名

// 计算父节点编号
inline Node parent(Node n) { return (n - 1) / 2; }
// 计算左子节点编号
inline Node left_child(Node n) { return n + n + 1; }
// 计算右子节点编号
inline Node right_child(Node n) { return n + n + 2; }

const int MAXN = 1023;		// 1024个节点，支持最大10层的二叉树

template<typename T>
struct BiTree {
	T *_nodes[MAXN];

	BiTree() { memset(_nodes, 0, sizeof(_nodes)); }
	~BiTree()
	{
		for (int i = 0; i < MAXN; ++i)
			if (_nodes[i]) delete _nodes[i];
	}

	// 判断节点是否存在
	bool has_node(Node n) const { return _nodes[n]; }
	// 重载[]运算，使得可以按下标值访问节点
	T &operator[](Node n) { return *_nodes[n]; }
	// 插入一个新的节点
	void insert(Node n, const T &value)
	{
		if (!_nodes[n]) {
			_nodes[n] = new T;
			*_nodes[n] = value;
		}
	}
	// 删除一个节点
	void erase(Node n)
	{
		if (_nodes[n]) {
			delete _nodes[n];
			_nodes[n] = NULL;
		}
	}
};

int main()
{
	Node root = 0;
	// 生成一棵二叉树，数据项为int型
	BiTree<int> tree;
	// 插入根节点，数据值为4
	tree.insert(root, 4);
	printf("root = %d\n", tree[root]);
	// 修改根节点的值
	++tree[0];
	printf("root = %d\n", tree[root]);
	// 添加左右子节点
	tree.insert(left_child(root), 10);
	tree.insert(right_child(root), 20);
	printf("left = %d, right = %d\n", tree[left_child(root)], tree[right_child(root)]);

	return 0;
}
