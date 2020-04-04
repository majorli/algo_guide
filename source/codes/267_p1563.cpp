#include <iostream>
#include <string>

using namespace std;

int main()
{
	int *faces;
	string *names;
	int n, m;

	cin >> n >> m;
	faces = new int[n];
	names = new string[n];
	for (int i = 0; i < n; i++) cin >> faces[i] >> names[i];

	int dir, step, next;
	int id = 0;
	for (int i = 0; i < m; i++) {
		cin >> dir >> step;
		next = faces[id] == dir ? id - step : id + step;
		next %= n;
		id = next < 0 ? next + n : next;
	}
	cout << names[id] << endl;

	delete [] faces;
	delete [] names;

	return 0;
}

