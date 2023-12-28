#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Random
{
public:
	Random();
	int even_next();
	int even_nextInRange(int x, int y);
private:
	int random_number = 0;
};

int Random::even_next()
{
	random_number = rand();
	if (random_number % 2 == 0) return random_number;
	else return random_number - 1;
}
int Random::even_nextInRange(int x, int y)
{
	random_number = rand() % (y - x + 1) + x; // rand() % 5 = 0���� 4������ ������ ������ �߻���Ų��.
	// rand() % a = 0���� a-1������ ������ ������ �߻���Ų��.
	// rand() % (y-x) = 0���� y-x-1������ ������ ������ �߻���Ų��.
	// rand() % (y-x+1) = 0���� y-x������ ������ ������ �߻���Ų��.
	// rand() % (y-x+1) + x = x���� y������ ������ ������ �߻���Ų��.
	if (random_number % 2 == 0) return random_number;
	else return random_number - 1;
}
Random::Random()
{
	srand((unsigned)time(0));
}

int main()
{
	Random r;
	cout << "--0���� " << RAND_MAX << "������ ���� ���� 10 �� --" << endl; //RAND_MAX�� cstdlib������Ͽ� �������
	for (int i = 0; i < 10; i++)
	{
		int n = r.even_next(); // 0���� 32767������ ������ ����
		cout << n << ' ';
	}
	cout << endl << endl << "--2���� " << "10������ ���� ���� 10 �� --" << endl;
	for (int i = 0; i < 10; i++) {
		int n = r.even_nextInRange(2, 10); // 2���� 4������ ������ ����
		cout << n << ' ';
	}
	cout << endl;
	return 0;
}