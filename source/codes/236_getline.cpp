#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

string &getline(string &s);

int main()
{
	string s;
	getline(s);
	cout << s << endl;

	return 0;
}

string &getline(string &s)
{
	char c;
	while ((c = getchar()) != '\n')
		s.push_back(c);
	return s;
}

