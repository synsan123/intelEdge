#include<iostream>
using namespace std;

char& find(char a[], char c, bool& success)
{
	int length = sizeof(a);
	for (int i = 0; i < length; i++)
	{
		if (a[i] == c)
		{
			success = true;
			return a[i];
		}
	}
}

int main()
{
	char s[] = "Mike";
	bool b = false;
	char& loc = find(s, 'M', b);
	if (b == false)
	{
		cout << "M을 찾을 수 없다" << endl;
		return 0;
	}
	loc = 'm';
	cout << s << endl;
}



