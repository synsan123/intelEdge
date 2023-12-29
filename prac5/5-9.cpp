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
	return *this; //�ڱ� �ڽ��� ���� ���� // �������� �������� // �ڱ��ڽ��� �� // this�� �ڱ��ڽ��� �ּҸ� ����Ŵ
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