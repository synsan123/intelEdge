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
	//Point p; => 주석해제하면 참조되지 않은 지역 변수라고 나옴.(문제는 없지만 warning 보기 싫어서 주석처리. 기본 생성자가 실행이 안됌...)
	ColorPoint cp;
	cp.setPoint(3, 5);
	cp.setColor("RED");
	cp.showColor();
}
#endif
