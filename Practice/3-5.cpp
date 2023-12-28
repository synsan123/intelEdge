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
	random_number = rand() % (y - x + 1) + x; // rand() % 5 = 0부터 4까지의 범위의 난수를 발생시킨다.
											  // rand() % a = 0부터 a-1까지의 범위의 난수를 발생시킨다.
											  // rand() % (y-x) = 0부터 y-x-1까지의 범위의 난수를 발생시킨다.
										      // rand() % (y-x+1) = 0부터 y-x까지의 범위의 난수를 발생시킨다.
											  // rand() % (y-x+1) + x = x부터 y까지의 범위의 난수를 발생시킨다.
	return random_number;
}
Random::Random()
{
	srand((unsigned)time(0));
}

int main()
{
	Random r;
	cout << "--0에서 " << RAND_MAX << "까지의 랜덤 정수 10 개 --" << endl; //RAND_MAX는 cstdlib헤어파일에 들어있음
	for (int i = 0; i < 10; i++)
	{
		int n = r.next(); // 0에서 32767사이의 랜덤한 정수
		cout << n << ' ';
	}
	cout << endl << endl << "--2에서 " << "4까지의 랜덤 정수 10 개 --" << endl;
	for (int i = 0; i < 10; i++) {
		int n = r.nextInRange(2, 4); // 2에서 4사이의 랜덤한 정수
		cout << n << ' ';
	}
	cout << endl;
	return 0;
}
