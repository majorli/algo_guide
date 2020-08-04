#include <cstddef>
#include <cstdio>

struct Node {
	int _value;
	Node *_left;
	Node *_right;

	Node(int value) { _value = value; _left = NULL; _right = NULL; }

	int &value() { return _value; }
};

int main()
{
	Node *root = new Node(4);
	printf("%d\n", root->value());
	++root->value();
	printf("%d\n", root->value());
	delete root;
	
	return 0;
}
