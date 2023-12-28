#include <iostream>
using namespace std;

class Container
{
public:
	Container() { size = 10; }
	void fill();
	void consume();
	int getSize();
private:
	int size;
};

class CoffeeVendingMachine
{
public:
	void run();
private:
	Container tong[3];
	void fill();
	void selectEspresso();
	void selectAmericano();
	void selectSugarCoffee();
	void show();
};

int start = 0;

void Container::fill()
{
	size = 10;
}
void Container::consume()
{
	size--;
}
int Container::getSize()
{
	return size;
}

void CoffeeVendingMachine::run()
{
	int number;
	if (start == 0) cout << "***** Ŀ�����Ǳ⸦ �۵��մϴ� *****" << endl;
	start++;
	while (true)
	{
		cout << "�޴��� �����ּ���(1:����������, 2:�Ƹ޸�ī��, 3:����Ŀ��, 4:�ܷ�����, 5:ä���) >> ";
		cin >> number;
		switch (number)
		{
		case 1:selectEspresso(); break;
		case 2:selectAmericano(); break;
		case 3:selectSugarCoffee(); break;
		case 4:show(); break;
		case 5:fill(); break;
		default:break;
		}
	}
}

void CoffeeVendingMachine::selectEspresso()
{
	for (int i = 0; i < 3; i++)
	{
		if (tong[i].getSize() == 0)
		{
			cout << "���ᰡ �����մϴ�." << endl;
			run();
		}
	}
	tong[0].consume();
	tong[1].consume();
	cout << "���������� ���Խ��ϴ�." << endl;
}
void CoffeeVendingMachine::selectAmericano()
{
	for (int i = 0; i < 3; i++)
	{
		if (tong[i].getSize() == 0)
		{
			cout << "���ᰡ �����մϴ�." << endl;
			run();
		}
	}
	tong[0].consume();
	tong[1].consume();
	tong[1].consume();
	cout << "�Ƹ޸�ī�� ���Խ��ϴ�." << endl;
}
void CoffeeVendingMachine::selectSugarCoffee()
{
	for (int i = 0; i < 3; i++)
	{
		if (tong[i].getSize() == 0)
		{
			cout << "���ᰡ �����մϴ�." << endl;
			run();
		}
	}
	tong[0].consume();
	tong[1].consume();
	tong[1].consume();
	tong[2].consume();
	cout << "����Ŀ�� ���Խ��ϴ�." << endl;
}
void CoffeeVendingMachine::show()
{
	cout << "Ŀ�� " << tong[0].getSize();
	cout << " ,�� " << tong[1].getSize();
	cout << " ,���� " << tong[2].getSize() << endl;
}
void CoffeeVendingMachine::fill()
{
	for (int i = 0; i < 3; i++)
	{
		tong[i].fill();
	}
	show();
}
int main()
{	
	CoffeeVendingMachine* coffee = new CoffeeVendingMachine;
	coffee->run();
	delete coffee;
}