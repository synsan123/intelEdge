#include <iostream>
using namespace std;

class CoffeeMachine
{
public:
	CoffeeMachine(int x, int y, int z);
	void drinkEspresso();
	void drinkAmericano();
	void drinkSugarCoffee();
	void fill();
	void show();
private:
	int coffee;
	int water;
	int sugar;
};

CoffeeMachine::CoffeeMachine(int x, int y, int z)
{
	coffee = x;
	water = y;
	sugar = z;
}
void CoffeeMachine::drinkEspresso()
{
	coffee -= 1;
	water -= 1;
}
void CoffeeMachine::drinkAmericano()
{
	coffee -= 1;
	water -= 2;
}
void CoffeeMachine::drinkSugarCoffee()
{
	coffee -= 1;
	water -= 2;
	sugar -= 1;
}
void CoffeeMachine::show()
{
	cout << "Ŀ�� �ӽ� ����, Ŀ�� : " << coffee << "\t�� : " << water << "\t���� : " << sugar << endl;
}
void CoffeeMachine::fill()
{
	coffee = 10;
	water = 10;
	sugar = 10;
}

int main()
{
	CoffeeMachine java(5, 10, 3);
	java.drinkEspresso();
	java.show();
	java.drinkAmericano();
	java.show();
	java.drinkSugarCoffee();
	java.show();
	java.fill();
	java.show();
	return 0;
}