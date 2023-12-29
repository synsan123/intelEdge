#include <iostream>
using namespace std;

class MyIntStack
{
public:
	MyIntStack() { tos = 0; }
	bool push(int n);
	bool pop(int& n);
private:
	int p[10] = { 0 };
	int tos;
};

bool MyIntStack::push(int n)
{
	if (tos > 9) return false;
	else
	{
		p[tos] = n;
		tos++;
		return true;
	}
}

bool MyIntStack::pop(int& n)
{
	tos--;
	if (tos < 0) return false;
	else
	{
		n = p[tos];
		return true;
	}
}
int main()
{
	MyIntStack a;
	for (int i = 0; i < 11; i++)
	{
		if (a.push(i)) cout << i << ' ';
		else cout << endl << i + 1 << " 번째 stack full" << endl;
	}
	int n;
	for (int i = 0; i < 11; i++)
	{
		if (a.pop(n)) cout << n << ' ';
		else cout << endl << i + 1 << " 번째 stack empty" << endl;
	}
	cout << endl;
}