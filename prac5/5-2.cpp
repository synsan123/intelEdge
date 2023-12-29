#include <iostream>
using namespace std;

void half(double& number)
{
	number = number / 2;
}

int main()
{
	double n = 20;
	half(n);
	cout << n;
}
