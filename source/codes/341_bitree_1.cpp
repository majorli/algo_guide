#include <cstddef>
#include <cstdio>

template<typename T>
struct Node {
	T _value;
	Node *left;
	Node *right;

	Node(const T &value) { _value = value; left = NULL; right = NULL; }
	T &value() { return _value; }
};

typedef Node<int> *BiTree;	// 定义一个具体的二叉树指针类型，数据为int型

int main()
{
	// 生成根节点，值为4
	BiTree root = new Node<int>(4);
	printf("root = %d\n", root->value());
	// 修改根节点的值
	++root->value();
	printf("root = %d\n", root->value());
	// 添加左右子节点
	BiTree left_child = new Node<int>(10);
	root->left = left_child;
	root->right = new Node<int>(20);
	printf("left = %d, right = %d\n", root->left->value(), root->right->value());
	delete root->left;
	delete root->right;
	delete root;
	
	return 0;
}
