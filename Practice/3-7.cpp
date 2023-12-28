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
	if (select % 2 == 0) // 짝수 출력
	{
		if ((random_number % 2 == 0)) return random_number;
		else return random_number - 1;
	}
	else // 홀수 출력
	{
		if ((random_number % 2 == 0)) return random_number + 1;
		else return random_number;
	}
}
int SelectableRandom::next()
{
	random_number = rand();
	if (select % 2 == 0) // 짝수 출력
	{
		if ((random_number % 2 == 0)) return random_number;
		else return random_number - 1;
	}
	else // 홀수 출력
	{
		if ((random_number % 2 == 0)) return random_number + 1;
		else return random_number;
	}
}

int main()
{
 	SelectableRandom r1(0);
	cout << "--0에서 " << RAND_MAX << "까지의 랜덤 짝수 정수 10 개 --" << endl; //RAND_MAX는 cstdlib헤어파일에 들어있음
	for (int i = 0; i < 10; i++)
	{
		int n = r1.next(); 
		cout << n << ' ';
	}
	SelectableRandom r2(1);
	cout << endl << endl << "--2에서 " << "9까지의 랜덤 홀수 정수 10 개 --" << endl;
	for (int i = 0; i < 10; i++) {
		int n = r2.nextInRange(2, 9);
		cout << n << ' ';
	}
	cout << endl;
	return 0;
}
