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
	cout << "���� ���� >> ";
	int number;
	cin >> number;
	Circle* pArray = new Circle[number];
	int count = 0;
	int radius;
	for (int i = 0; i < number; i++)
	{
		cout << "�� " << i + 1 << "�� ������ >> ";
		cin >> radius;
		pArray[i].setradius(radius); //pArray->setradius(radius) ����
		if (pArray[i].getarea() > 100) //pArray->getarea()
		{
			count++;
		}
		//pArray++;
	}
	cout << "������ 100���� ū ���� " << count << "�� �Դϴ�." << endl;
}