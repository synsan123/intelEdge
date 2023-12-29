#include <iostream>
using namespace std;

class Square {
	int width, height;
public:
	Square(int x, int y)
	{
		width = x;
		height = y;
	}
	friend void addSquare(Square A, Square B);
	friend void addwidthheightSquarr(Square A, Square B);
};

class Triangle {
	int width, height;
public:
	Triangle(int x, int y)
	{
		width = x;
		height = y;
	}
	friend void addTriangle(Triangle A, Triangle B);
	friend void addxy(Triangle A, Triangle B);
};

void addSquare(Square A, Square B)
{
	int area_A = A.width * A.height;
	int area_B = B.width * B.height;
	cout << "넓이의 합은 " << area_A + area_B << endl;
}

void addwidthheightSquarr(Square A, Square B)
{
	int width_AplusB = A.width + B.width;
	int height_AplusB = A.height + B.height;
	int addSquareAB = width_AplusB * height_AplusB;
	cout << "widht + height 후 Square의 넓이는 " << addSquareAB << endl;
}

void addTriangle(Triangle A, Triangle B)
{
	int area_A = A.width * A.height / 2;
	int area_B = B.width * B.height / 2;
	int plus = area_A + area_B;
	cout << "삼각형 넓이의 합은 " << plus << endl;
}

void addxy(Triangle A, Triangle B)
{
	int plus_width = A.width + B.width;
	int plus_height = A.height + B.height;
	double plusarea = plus_width * plus_height / 2.0;
	cout << "x와 y의 값을 모두 합쳐 나온 삼각형 넓이의 합은 " << plusarea << endl;
}

int main(int argc, char* argv[])
{
	Square A(3,5), B(4,4);
	addSquare(A, B);
	addwidthheightSquarr(A, B);
	Triangle C(5, 10), D(6, 5);
	addTriangle(C, D);
	addxy(C, D);
	return 0;

}
