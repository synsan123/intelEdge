#include <iostream>
using namespace std;

//�Լ� �ߺ��� �̿��Ͽ��� ��
#if 0
int add(int* p, int number) {
	int sum = 0;
	for (int i = 0; i < number; i++) {
		sum += p[i];
	}
	return sum;
}

int add(int* p, int number, int *q) {
	int sum = 0;
	for (int i = 0; i < number; i++) {
		sum += p[i] + q[i];
	}
	return sum;
}

int main()
{
	int a[] = { 1,2,3,4,5 };
	int b[] = { 6,7,8,9,10 };
	int c = add(a, 5);
	int d = add(a, 5, b);
	cout << c << endl;
	cout << d << endl;

}
#endif

//default �Ű� ���� ��� �Ͽ��� ��.
int add(int* p, int number, int* q = NULL) {
	int sum = 0;
	for (int i = 0; i < number; i++) {
		sum += p[i];
		if (q != NULL)
			sum += q[i];
	}
	return sum;
}

int main()
{
	int a[] = { 1,2,3,4,5 };
	int b[] = { 6,7,8,9,10 };
	int c = add(a, 5);
	int d = add(a, 5, b);
	cout << c << endl;
	cout << d << endl;
}

