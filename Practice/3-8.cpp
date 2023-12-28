#include <iostream>
#include <string>
using namespace std;

class Integer
{
public:
	Integer(int x);
	Integer(string Date);
	int get();
	int set(int b);
	int isEven();
private:
	int a;
};

Integer::Integer(int x)
{
	a = x;
}

Integer::Integer(string Date)
{
	a = stoi(Date);
}

int Integer::get()
{
	return a;
}

int Integer::set(int b)
{
	return a = b;
}

int Integer::isEven()
{
	return true;
}

int main()
{
	Integer n(30);
	cout << n.get() << ' ';
	n.set(50);
	cout << n.get() << ' ';

	Integer m("300");
	cout << m.get() << ' ';
	cout << m.isEven();
}