#include <iostream>
using namespace std;

class ArrayUtillity {
public:
	static void intToDouble(int source[], double dest[], int size);
	static void DoubleToint(double sourcle[], int dest[], int size);
};

void ArrayUtillity::intToDouble(int source[], double dest[], int size) {
	for (int i = 0; i < size; i++) {
		dest[i] = (double)source[i];
	}
}

void ArrayUtillity::DoubleToint(double source[], int dest[], int size) {
	for (int i = 0; i < size; i++) {
		dest[i] = (int)source[i];
	}
}

int main()
{
	int x[] = { 1,2,3,4,5 };
	double y[5];
	double z[] = { 9.9, 8.8, 7.7, 6.6, 5.5 };

	ArrayUtillity::intToDouble(x, y, 5);
	for (int i = 0; i < 5; i++)	cout << y[i] << ' ';
	cout << endl;

	ArrayUtillity::DoubleToint(z, x, 5);
	for (int i = 0; i < 5; i++)	cout << x[i] << ' ';
	cout << endl;
}