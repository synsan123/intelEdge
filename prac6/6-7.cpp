#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

class Random {
public:
	static void seed() { srand((unsigned)time(0)); }
	static int nextInt(int min = 0, int max = 32767);
	static char nextAlphabet();
	static double nextDouble();
};

int Random::nextInt(int min, int max) {
	return rand() % (max - min) + min;
}
char Random::nextAlphabet() {
	if (rand() % 2 == 0) return rand() % 26 + 'a';
	else return rand() % 26 + 'A';
}
double Random::nextDouble() {
	return (double)rand() / RAND_MAX;
}
int main() {
	cout << "1���� 100���� ������ ���� 10���� ����մϴ�" << endl;
	for (int i = 0; i < 10; i++) {
		cout << Random::nextInt(1, 100) << ' ';
	}
	cout << endl;

	cout << "���ĺ��� �����ϰ� 10�� ����մϴ�" << endl;
	for (int i = 0; i < 10; i++) {
		cout << Random::nextAlphabet() << ' ';
	}
	cout << endl;

	cout << "������ �Ǽ� 10���� ����մϴ�" << endl;
	for (int i = 0; i < 10; i++) {
		cout << Random::nextDouble() << ' ';
	}
	cout << endl;
	return 0;
}