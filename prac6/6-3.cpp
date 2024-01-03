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

// 위 소스코드를 더 간단하게 만든 것.
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

//생성자 중복 없애고 디폴트 매개 변수를 이용하여 작성
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