#include <cstdio>

struct Node {
	int value;
	Node *next;
	Node() { next = NULL; }
};

inline int digit(int n, int radix) { return (n / radix) % 10; }

void print(Node *list)
{
	Node *d = list->next;
	while (d) {
		printf("%d->", d->value);
		d = d->next;
	}
	printf("^\n");
}

void clear(Node *list)
{
	Node *temp = list, *next;
	while (temp) {
		next = temp->next;
		delete temp;
		temp = next;
	}
}

void radix_sort(Node *list);

int main()
{
	Node *list = new Node;
	scanf("%d", &(list->value));
	for (int i = 0; i < list->value; ++i) {
		Node *new_node = new Node;
		scanf("%d", &(new_node->value));
		new_node->next = list->next;
		list->next = new_node;
	}
	print(list);

	printf("sorting...\n");
	radix_sort(list);
	print(list);

	clear(list);
	return 0;
}

void radix_sort(Node *list)
{
	Node buckets[10], *tails[10];
	int radix = 1, d;
	while (buckets[0].value != list->value) {
		for (int i = 0; i < 10; ++i) {
			buckets[i].value = 0;
			buckets[i].next = NULL;
			tails[i] = &buckets[i];
		}
		while (list->next) {
			d = digit(list->next->value, radix);
			Node *node = list->next;
			list->next = node->next;
			node->next = NULL;
			tails[d]->next = node;
			tails[d] = node;
			++buckets[d].value;
		}
		Node *p = list;
		for (int i = 0; i < 10; ++i) {
			if (buckets[i].next) {
				p->next = buckets[i].next;
				p = tails[i];
			}
		}
		radix *= 10;
	}
}
