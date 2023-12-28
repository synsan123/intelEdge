#include <iostream>
using namespace std;

class Circle
{
public:
	void setradius(int radius);
	double getarea();
private:
	int radius;
};

void Circle::setradius(int radius)
{
	this->radius = radius;
}
double Circle::getarea()
{
	return 3.14 * radius * radius;
}
int main()
{
	Circle* pArray = new Circle[3];
	int count = 0;
	int radius;
	for (int i = 0; i < 3; i++)
	{
		cout << "원 " << i + 1 << "의 반지름 >> ";
		cin >> radius;
		pArray[i].setradius(radius);
		if (pArray[i].getarea() > 100)
		{
			count++;
		}
	}
	cout << "면적이 100보다 큰 원은 " << count << "개 입니다." << endl;
}