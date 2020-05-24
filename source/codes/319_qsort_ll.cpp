#include <cstdio>

struct Node {
	int value;
	Node *next;
	Node() { next = NULL; }
};

void clear(Node *head);
void print(Node *head);

Node *partition(Node *left, Node *right);
void qsort(Node *left, Node *right);

int main()
{
	Node *head = new Node;
	Node *tail = head;
	scanf("%d", &(head->value));
	for (int i = 0; i < head->value; ++i) {
		Node *temp = new Node;
		scanf("%d", &(temp->value));
		tail->next = temp;
		tail = temp;
	}
	print(head);

	qsort(head, tail);
	print(head);

	clear(head);
	return 0;
}

void clear(Node *head)
{
	Node *temp = head, *next;
	while (temp) {
		next = temp->next;
		delete temp;
		temp = next;
	}
}

void print(Node *head)
{
	Node *temp = head;
	while (temp->next) {
		printf("%d->", temp->next->value);
		temp = temp->next;
	}
	printf("^\n");
}

Node *partition(Node *left, Node *right)
{
	Node *i = left, *j = left;
	int pivot = right->value;
	while (j->next != right) {
		if (j->next->value < pivot) {
			right->value = i->next->value;
			i->next->value = j->next->value;
			j->next->value = right->value;
			i = i->next;
		}
		j = j->next;
	}
	right->value = i->next->value;
	i->next->value = pivot;
	return i;
}

void qsort(Node *left, Node *right)
{
	if (left == right || left->next == right) return;
	Node *sp = partition(left, right);
	qsort(left, sp);
	qsort(sp->next, right);
}

