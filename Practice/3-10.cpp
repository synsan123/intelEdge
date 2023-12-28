#include <iostream>
#include "3-10.h"
using namespace std;

void Add::setvalue(int x, int y)
{
	a = x;
	b = y;
}
int Add::calculate()
{
	return a + b;
}

void Sub::setvalue(int x, int y)
{
	a = x;
	b = y;
}
int Sub::calculate()
{
	return a - b;
}

void Mul::setvalue(int x, int y)
{
	a = x;
	b = y;
}
int Mul::calculate()
{
	return a * b;
}

void Div::setvalue(int x, int y)
{
	a = x;
	b = y;
}
int Div::calculate()
{
	return a / b;
}

