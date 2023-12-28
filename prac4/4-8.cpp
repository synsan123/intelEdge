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
	cout << "원의 개수 >> ";
	int number;
	cin >> number;
	Circle* pArray = new Circle[number];
	int count = 0;
	int radius;
	for (int i = 0; i < number; i++)
	{
		cout << "원 " << i + 1 << "의 반지름 >> ";
		cin >> radius;
		pArray[i].setradius(radius); //pArray->setradius(radius) 가능
		if (pArray[i].getarea() > 100) //pArray->getarea()
		{
			count++;
		}
		//pArray++;
	}
	cout << "면적이 100보다 큰 원은 " << count << "개 입니다." << endl;
}