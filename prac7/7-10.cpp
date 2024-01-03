#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class Statistics {
	int* statistic;
	int size;
public:
	Statistics(int size = 0) { this->size = size; this->statistic = new int[size]; }
	Statistics& operator <<(int x) {
		size++;
		Statistics tmp(size);
		for (int i = 0; i < size - 1; i++)
			tmp.statistic[i] = statistic[i];
		tmp.statistic[size - 1] = x;

		delete[] this->statistic;
		this->statistic = new int[size];
		for (int i = 0; i < size; i++)
			this->statistic[i] = tmp.statistic[i];
		return *this;
	}
	Statistics& operator ~() {
		for (int i = 0; i < size; i++)
			cout << statistic[i] << ' ';
		cout << endl;
		return *this;
	}
	Statistics& operator >>(int& avg) {
		int sum = 0;
		for (int i = 0; i < size; i++)
			sum += statistic[i];
		avg = sum / size;
		return *this;
	}
	bool operator !() {
		if (size == 0) return true;
		else return false;
	}
};

int main() {
	Statistics stat;
	if (!stat) cout << "현재 통계 데이터가 없습니다." << endl;

	int x[5];
	cout << "5개의 정수를 입력하라>>";
	for (int i = 0; i < 5; i++) cin >> x[i];

	for (int i = 0; i < 5; i++) stat << x[i];
	stat << 100 << 200;
	~stat;

	int avg;
	stat >> avg;
	cout << "avg=" << avg << endl;

	return 0;
}