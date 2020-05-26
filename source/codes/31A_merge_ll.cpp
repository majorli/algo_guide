#include <cstdio>

struct Node {
	int value;
	Node *next;
	Node() { next = NULL; }
};

void clear(Node *head);
void print(Node *head);

void merge(Node *head_a, Node *head_b);

int main()
{
	Node *head_a = new Node;
	Node *head_b = new Node;
	Node *tail_a = head_a, *tail_b = head_b;
	scanf("%d %d", &(head_a->value), &(head_b->value));
	for (int i = 0; i < head_a->value; ++i) {
		Node *temp = new Node;
		scanf("%d", &(temp->value));
		tail_a->next = temp;
		tail_a = temp;
	}
	for (int i = 0; i < head_b->value; ++i) {
		Node *temp = new Node;
		scanf("%d", &(temp->value));
		tail_b->next = temp;
		tail_b = temp;
	}
	print(head_a);
	print(head_b);

	merge(head_a, head_b);
	printf("merged\n");
	print(head_a);
	print(head_b);

	clear(head_a);
	clear(head_b);
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
	Node *temp = head->next;
	while (temp) {
		printf("%d->", temp->value);
		temp = temp->next;
	}
	printf("^\n");
}

void merge(Node *head_a, Node *head_b)
{
	Node *i = head_a, *j, *temp;
	while (head_b->next) {
		while (i->next && i->next->value <= head_b->next->value)
			i = i->next;
		if (i->next) {
			j = head_b;
			while (j->next && j->next->value < i->next->value)
				j = j->next;
			temp = i->next;
			i->next = head_b->next;
			head_b->next = j->next;
			j->next = temp;
			i = j->next;
		} else {
			i->next = head_b->next;
			head_b->next = NULL;
		}
	}
}

