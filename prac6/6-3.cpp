#include <iostream>
using namespace std;

#if 0
int big(int a, int b) {
	int	max = 100;
	if (a > b && a < max) return a;
	else if (b > a && b < max) return b;
	else return max;
}

int big(int a, int b, int c) {
	int max = c;
	if (a > b && a > max) return max;
	else if (b > a && b > max) return max;
	else if (a > b && a < max) return a;
	else b;
}

int main()
{
	int x = big(3, 5);
	int y = big(300, 60);
	int z = big(30, 60, 50);
	cout << x << ' ' << y << ' ' << z << endl;
}
#endif

// �� �ҽ��ڵ带 �� �����ϰ� ���� ��.
#if 0
int big(int a, int b) {
	int max = 100;
	int big = a;
	if (big < b)
		big = b;
	if (big > max)
		big = max;
	return big;
}

int big(int a, int b, int c) {
	int max = c;
	int big = a;
	if (big < b)
		big = b;
	if (big > max)
		big = max;
	return big;
}

int main()
{
	int x = big(3, 5);
	int y = big(300, 60);
	int z = big(30, 60, 50);
	cout << x << ' ' << y << ' ' << z << endl;
}
#endif

//������ �ߺ� ���ְ� ����Ʈ �Ű� ������ �̿��Ͽ� �ۼ�
int big(int a, int b, int c = 100) {
	int max = c;
	int big = a;
	if (big < b)
		big = b;
	if (big > max)
		big = max;
	return big;
}

int main()
{
	int x = big(3, 5);
	int y = big(300, 60);
	int z = big(30, 60, 50);
	cout << x << ' ' << y << ' ' << z << endl;
}