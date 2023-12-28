#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Random
{
public:
	Random();
	int next();
	int nextInRange(int x, int y);
private:
	int random_number = 0;
};

int Random::next()
{
	random_number = rand();
	return random_number;
}
int Random::nextInRange(int x, int y)
{
	random_number = rand() % (y - x + 1) + x; // rand() % 5 = 0���� 4������ ������ ������ �߻���Ų��.
											  // rand() % a = 0���� a-1������ ������ ������ �߻���Ų��.
											  // rand() % (y-x) = 0���� y-x-1������ ������ ������ �߻���Ų��.
										      // rand() % (y-x+1) = 0���� y-x������ ������ ������ �߻���Ų��.
											  // rand() % (y-x+1) + x = x���� y������ ������ ������ �߻���Ų��.
	return random_number;
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
		int n = r.next(); // 0���� 32767������ ������ ����
		cout << n << ' ';
	}
	cout << endl << endl << "--2���� " << "4������ ���� ���� 10 �� --" << endl;
	for (int i = 0; i < 10; i++) {
		int n = r.nextInRange(2, 4); // 2���� 4������ ������ ����
		cout << n << ' ';
	}
	cout << endl;
	return 0;
}
