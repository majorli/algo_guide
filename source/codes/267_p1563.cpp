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

	int dir, step;	// 指令：dir = 方向，step = 步数
	int id = 0;
	for (int i = 0; i < m; i++) {
		cin >> dir >> step;
		id += faces[id] == dir ? -step : step;
		id %= n;		// 根据虚拟环状结构下标计算出真正的数组下标
		if (id < 0) id += n;
	}
	cout << names[id] << endl;

	delete [] faces;
	delete [] names;

	return 0;
}

