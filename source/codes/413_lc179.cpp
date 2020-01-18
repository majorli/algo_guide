#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Element {
	int num;
	long long pow;

	bool operator<(const Element &b) const
	{
		return num * b.pow + b.num > b.num * pow + num;
	}
};

istream &operator>>(istream &is, Element &e)
{
	is >> e.num;
	e.pow = 10;
	while (e.num / e.pow) e.pow *= 10;
	return is;
}

int main()
{
	int n;
	cin >> n;
	vector<Element> elements(n);
	for (int i = 0; i < n; ++i) cin >> elements[i];
	sort(elements.begin(), elements.end());
	cout << elements[0].num;
	if (elements[0].num)
		for (int i = 1; i < n; ++i) cout << elements[i].num;
	cout << endl;

	return 0;
}
