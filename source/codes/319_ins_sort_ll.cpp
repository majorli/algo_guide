#include <cstddef>
#include <iostream>

using namespace std;

struct Node {
	int value;
	Node *next;
	Node() { next = NULL; }
};

void print(Node *head)
{
	while (head->next) {
		cout << head->next->value << "->";
		head = head->next;
	}
	cout << "^" << endl;
}

void clear(Node *head)
{
	Node *node = head->next, *next;
	while (node) {
		next = node->next;
		delete node;
		node = next;
	}
}

int main()
{
	Node head;		// 头部dummy
	cin >> head.value;	// 头部dummy的值用作存放长度
	Node *prev;
	for (int i = 0; i < head.value; ++i) {
		Node *new_node = new Node;
		cin >> new_node->value;
		cout << new_node->value << ", ";
		prev = &head;
		while (prev->next && prev->next->value <= new_node->value)
			prev = prev->next;
		new_node->next = prev->next;
		prev->next = new_node;
	}
	cout << endl;
	print(&head);
	clear(&head);

	return 0;
}

