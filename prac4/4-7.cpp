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
		cout << "�� " << i + 1 << "�� ������ >> ";
		cin >> radius;
		pArray[i].setradius(radius);
		if (pArray[i].getarea() > 100)
		{
			count++;
		}
	}
	cout << "������ 100���� ū ���� " << count << "�� �Դϴ�." << endl;
}