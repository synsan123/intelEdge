#include <iostream>
#include <string>
using namespace std;

#if 0
class Point {
	int x, y;
public:
	void setPoint(int x = 0, int y = 0) { this->x = x; this->y = y; }
	void showPoint() { cout << "( " << x << " , " << y << " )" << endl; }
};

class ColorPoint :public Point {
	string color;
public:
	void setColor(string color) { this->color = color; }
	void showColor();
};

void ColorPoint::showColor() {
	cout << color << " : ";
	showPoint();
}

int main()
{
	//Point p; => �ּ������ϸ� �������� ���� ���� ������� ����.(������ ������ warning ���� �Ⱦ �ּ�ó��. �⺻ �����ڰ� ������ �ȉ�...)
	ColorPoint cp;
	cp.setPoint(3, 5);
	cp.setColor("RED");
	cp.showColor();
}
#endif
