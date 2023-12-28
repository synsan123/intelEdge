#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class SelectableRandom
{
public:
	SelectableRandom(int num);
	int next();
	int nextInRange(int x, int y);
private:
	int random_number = 0;
	int select = 0;
};

SelectableRandom::SelectableRandom(int num)
{
	select = num;
	srand((unsigned)time(0));
}

int SelectableRandom::nextInRange(int x, int y)
{
	random_number = rand() % (y - x + 1) + x;
	if (select % 2 == 0) // ¦�� ���
	{
		if ((random_number % 2 == 0)) return random_number;
		else return random_number - 1;
	}
	else // Ȧ�� ���
	{
		if ((random_number % 2 == 0)) return random_number + 1;
		else return random_number;
	}
}
int SelectableRandom::next()
{
	random_number = rand();
	if (select % 2 == 0) // ¦�� ���
	{
		if ((random_number % 2 == 0)) return random_number;
		else return random_number - 1;
	}
	else // Ȧ�� ���
	{
		if ((random_number % 2 == 0)) return random_number + 1;
		else return random_number;
	}
}

int main()
{
 	SelectableRandom r1(0);
	cout << "--0���� " << RAND_MAX << "������ ���� ¦�� ���� 10 �� --" << endl; //RAND_MAX�� cstdlib������Ͽ� �������
	for (int i = 0; i < 10; i++)
	{
		int n = r1.next(); 
		cout << n << ' ';
	}
	SelectableRandom r2(1);
	cout << endl << endl << "--2���� " << "9������ ���� Ȧ�� ���� 10 �� --" << endl;
	for (int i = 0; i < 10; i++) {
		int n = r2.nextInRange(2, 9);
		cout << n << ' ';
	}
	cout << endl;
	return 0;
}
