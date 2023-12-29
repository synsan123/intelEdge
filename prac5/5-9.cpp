#include <iostream>
using namespace std;

class Accumulator
{
public:
	Accumulator(int value);
	Accumulator& add(int n);
	int get();
private:
	int value;
};

Accumulator::Accumulator(int value)
{
	this->value = value;
}
Accumulator&Accumulator::add(int n)
{
	value += n;
	return *this; //자기 자신의 참조 리턴 // 포인터의 참조개념 // 자기자신의 값 // this는 자기자신의 주소를 가리킴
}
int Accumulator::get()
{
	return value;
}
int main()
{
	Accumulator acc(10);
	acc.add(5).add(6).add(7);
	cout << acc.get() << endl;
}