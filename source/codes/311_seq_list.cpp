#include <iostream>
using namespace std;

const int MAXN = 1e6;

struct List {
	int data[MAXN];
	int size;

	List() { size = 0; }
	int insert(int val, int pos = -1);
	int remove(int pos = -1);
	int get(int pos) const;
};

int List::insert(int val, int pos)
{
	if (size == MAXN)
		return -1;
	if (pos < 0 || pos > size)
		pos = size;
	for (int i = size - 1; i >= pos; i--)
		data[i+1] = data[i];
	data[pos] = val;
	size++;
	return pos;
}

int List::remove(int pos)
{
	if (pos < 0 || pos >= size)
		pos = size - 1;
	int t = data[pos];
	for (int i = pos + 1; i < size; i++)
		data[i-1] = data[i];
	size--;
	return t;
}

int List::get(int pos) const
{
	if (pos < 0 || pos >= size)
		throw "pos error";
	return data[pos];
}

int main()
{
	List l;
	for (int i = 0; i < 10; i++)
		cout << "insert at " << l.insert(i * i, 0) << endl;
	for (int i = 0; i < l.size; i++)
		cout << l.get(i) << ", ";
	cout << endl;

	cout << "remove, get " << l.remove() << endl;
	for (int i = 0; i < l.size; i++)
		cout << l.get(i) << ", ";
	cout << endl;

	cout << "remove, get " << l.remove(0) << endl;
	for (int i = 0; i < l.size; i++)
		cout << l.get(i) << ", ";
	cout << endl;

	cout << "remove, get " << l.remove(3) << endl;
	for (int i = 0; i < l.size; i++)
		cout << l.get(i) << ", ";
	cout << endl;

	return 0;
}
