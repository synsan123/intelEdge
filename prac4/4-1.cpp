#include <iostream>
#include <string>
using namespace std;

#if 0
class Circle
{
public:
	Circle();
	Circle(int r);
	double getarea();
private:
	int radius;
};

Circle::Circle():Circle(1) {}

Circle::Circle(int r)
{
	radius = r;
}

double Circle::getarea()
{
	return 3.14 * radius * radius;
}

int main()
{
	Circle donut;
	Circle pizza(30);
	cout << donut.getarea() << endl;
	cout << pizza.getarea() << endl;

	Circle* p;
	p = &donut;
	cout << p->getarea() << endl;
	cout << (*p).getarea() << endl;
	p = &pizza;
	cout << p->getarea() << endl;
}
#endif

#if 0
class Circle
{
public:
	Circle();
	Circle(int r);
	void setradius(int r);
	double getarea();
private:
	int radius;
};

Circle::Circle():Circle(1){ }

Circle::Circle(int r)
{
	radius = r;
}

double Circle::getarea()
{
	return 3.14 * radius * radius;
}
void Circle::setradius(int r)
{
	radius = r;
}

int main()
{
	Circle CircleArray[3];
	
	CircleArray[0].setradius(10);
	CircleArray[1].setradius(20);
	CircleArray[2].setradius(30);
	for (int i = 0; i < 3; i++) // 3���ٰ� sizeof(CircleArray)/sizeof(CircleArray[0])�� ���� = 12 / 4 = 3;
	{
		cout << "Circle " << i << "�� ������ " << CircleArray[i].getarea() << endl;
	}

	Circle* p;
	p = CircleArray;
	for (int i = 0; i < 3; i++)
	{
		cout << "Circle " << i << "�� ������ " << p->getarea() << endl;
		p++;
	}
}
#endif

#if 0
class Circle
{
public:
	Circle();
	Circle(int r);
	void setradius(int r);
	double getarea();
private:
	int radius;
};

Circle::Circle()
{
	radius = 1;
}
Circle::Circle(int r)
{
	radius = r;
}
void Circle::setradius(int r)
{
	radius = r;
}
double Circle::getarea()
{
	return 3.14 * radius * radius;
}

int main()
{
	Circle CircleArray[3] = { Circle(20),Circle(10), Circle() };
	
	for (int i = 0; i < 3; i++)
	{
		cout << "Circle " << i << "�� ������ " << CircleArray[i].getarea() << endl;
	}
}
#endif

#if 0
class Circle
{
public:
	Circle();
	Circle(int r);
	void setradius(int r);
	double getarea();
private:
	int radius;
};

Circle::Circle()
{
	radius = 1;
}

Circle::Circle(int r)
{
	radius = r;
}

void Circle::setradius(int r)
{
	radius = r;
}
double Circle::getarea()
{
	return 3.14 * radius * radius;
}

int main()
{
	Circle circlearray[2][3] = { Circle(1),Circle(2),Circle(3),Circle(4),Circle(5),Circle() };

	//sizeof(circlearray) = 24 = 4 * 6
	//sizeof(circlearray[0] = 12 = 4 * 3
	//sizeof(circlearray[0][0] = 4

	int rowcount = sizeof(circlearray) / sizeof(circlearray[0]);
	int colcount = sizeof(circlearray[0]) / sizeof(circlearray[0][0]);
	cout << "���� ���� " << rowcount << endl;
	cout << "���� ���� " << colcount << endl;

 	for (int i = 0; i < rowcount; i++) // sizeof(circlearray)/sizeof(circlearray[0])
	{
		for (int j = 0; j < colcount; j++)
		{
			cout << "Circle " << "[ " << i << " , " << j << " ]�� ������ " << circlearray[i][j].getarea() << endl;
		}
	}
}
#endif

#if 0
int main()
{
	int* p;

	p = new int;
	if (!p) // !p�� p = NULL�� ���� => NULL = 0�̰� !NULL�� 1�� �Ǿ� ��. �׷��� if���� �����
	{
		cout << "�޸𸮸� �Ҵ��� �� �����ϴ�." << endl;
		return 0;
	}

	*p = 5;
	int n = *p;
	cout << "*p = " << *p << endl;
	cout << "n = " << n << endl;

	delete p;
}
#endif

#if 0
int main()
{
	cout << "�Է��� ������ ������? ";
	int number;
	cin >> number;
	if (number <= 0) return 0;
	int* p = new int[number];
	if (!p)
	{
		cout << "�޸𸮸� �Ҵ��� �� �����ϴ�." << endl;
		return 0;
	}

	for (int i = 0; i < number; i++)
	{
		cout << i + 1 << "��° ���� = ";
		cin >> p[i];
	}

	int sum = 0;
	for (int i = 0; i < number; i++)
	{
		sum += p[i];
	}
	cout << "����� " << sum / number << endl;

	delete[] p;

}
#endif

#if 0
class Circle
{
public:
	Circle();
	Circle(int r);
	~Circle();
	void setradius(int r);
	double getarea();
private:
	int radius;
};

Circle::Circle()
{
	radius = 1;
}
Circle::Circle(int r)
{
	radius = r;
}
Circle::~Circle()
{
	cout << "�Ҹ��� ���� radius = " << radius << endl;
}
void Circle::setradius(int r)
{
	radius = r;
}
double Circle::getarea() {
	return 3.14 * radius * radius;
}

int main()
{
	Circle* p, * q;
	p = new Circle;
	q = new Circle(30);
	cout << p->getarea() << endl << q->getarea() << endl;
	delete q;
	delete p;
}
#endif

#if 0
class Circle
{
public:
	Circle();
	Circle(int r);
	~Circle();
	void setradius(int r);
	double getarea();
private:
	int radius;
};

Circle::Circle()
{
	radius = 1;
}
Circle::Circle(int r)
{
	radius = r;
}
Circle::~Circle()
{
	cout << "�Ҹ��� ���� radius = " << radius << endl;
}
void Circle::setradius(int r)
{
	radius = r;
}
double Circle::getarea() {
	return 3.14 * radius * radius;
}

int main()
{
	int radius;
	while (true)
	{
		cout << "���� ������ �Է�(�����̸� ����) >> ";
		cin >> radius;
		if (radius < 0) break;
		Circle* p = new Circle(radius);
		cout << p->getarea() << endl;
		delete p;
	}
}
#endif

#if 0
class Circle
{
public:
	Circle();
	Circle(int r);
	~Circle();
	void setradius(int r);
	double getarea();
private:
	int radius;
};

Circle::Circle()
{
	radius = 1;
}
Circle::Circle(int r)
{
	radius = r;
}
Circle::~Circle()
{
	cout << "�Ҹ��� ���� radius = " << radius << endl;
}
void Circle::setradius(int r)
{
	radius = r;
}
double Circle::getarea() {
	return 3.14 * radius * radius;
}

int main()
{
	Circle* parray = new Circle[3];
	parray->setradius(10);
	(parray + 1)->setradius(20);
	(parray + 2)->setradius(30);

	for (int i = 0; i < 3; i++)
	{
		cout << (parray+i)->getarea() << endl;
	}

	delete[] parray;
}
#endif

#if 0
class Circle
{
public:
	Circle();
	~Circle();
	void setradius(int r);
	double getarea();
private:
	int radius;
};

Circle::Circle()
{
	radius = 1;
}
Circle::~Circle()
{
	cout << "�Ҹ��� ���� radius = " << radius << endl;
}
void Circle::setradius(int r)
{
	radius = r;
}
double Circle::getarea() {
	return 3.14 * radius * radius;
}

int main()
{
	cout << "�����ϰ��� �ϴ� ���� ������ ? ";
	int number, radius;
	cin >> number;
	if (number <= 0) return 0;
	Circle* parray = new Circle[number];
	for (int i = 0; i < number; i++)
	{
		cout << "��" << i + 1 << " : ";
		cin >> radius;
		parray[i].setradius(radius);
	}

	int count = 0;
	Circle* p = parray;
	for (int i = 0; i < number; i++)
	{
		cout << p->getarea() << ' ';
		if (p->getarea() >= 100 && p->getarea() <= 200)
		{
			count++;
		}
		p++;
	}
	cout << endl << "������ 100���� 200������ ���� ������ " << count << endl;
	delete[] parray;
}
#endif

#if 0
int main()
{
	string s;

	cout << "�Ʒ��� ���ڿ��� �Է��ϼ���. �� ĭ�� �־ �˴ϴ�. ������ �ѱ��� �ȵſ�." << endl;
	getline(cin, s, '\n');
	int length = s.length();

	for (int i = 0; i < length; i++)
	{
		string first = s.substr(0, 1);
		string sub = s.substr(1, length - 1);
		s = sub + first;
		cout << s << endl;
	}
}
#endif

#if 0
int main()
{
	string s;
	cout << "7+23+5+100+25�� ���� ���� ���ڿ��� �Է��ϼ���." << endl;
	getline(cin, s, '\n');
	int sum = 0;
	int startIndex = 0;
	while (true)
	{
		int findIndex = s.find('+', startIndex);
		if (findIndex == -1)//'+'���� �߰��� �� ����.find(ã�����ϴ� ����, �ε���) �ε� ��ã���� -1 ��ȯ
		{
			string part = s.substr(startIndex); // ��ü s�� 0������ ������ �и�
			if (part == "") break;
			cout << part << endl;
			sum += stoi(part);
			break;
		}
		int count = findIndex - startIndex; //substr���� �ڸ� ���� ����
		string part = s.substr(startIndex, count);

		cout << part << endl;
		sum += stoi(part);
		startIndex = findIndex + 1; //�ε��� ����
	}
	cout << "���ڵ��� ���� " << sum << endl;
}
#endif

#if 0
int main()
{
	string s;
	cout << "���� ���� ���ڿ��� �Է��ϼ���. �Է��� ���� &�����Դϴ�." << endl;
	getline(cin, s, '&');
	cin.ignore(); // &�ڿ� ���� ���� Enter Ű�� �����ϱ� ���� �ڵ�

	string findstring, replacestring;
	cout << endl << "find : ";
	getline(cin, findstring, '\n');
	cout << "replace : ";
	getline(cin, replacestring, '\n');

	int startIndex = 0;
	while (true)
	{
		int findIndex = s.find(findstring, startIndex);
		if (findIndex == -1) break;
		s.replace(findIndex, findstring.length(), replacestring);
		startIndex = findIndex + replacestring.length();
	}
	cout << s << endl;
}
#endif

//4�� �ǽ����� 1��

class Color
{
public:
	Color() { red = blue = green = 0; }
	Color(int r, int g, int b) { red = r; green = g; blue = b; }
	void setColor(int r, int g, int b) { red = r; green = g; blue = b; }
	void show() { cout << red << ' ' << green << ' ' << blue << endl; }
private:
	int red, blue, green;
};

int main() 
{
	Color screenColor(255, 0, 0);
	Color* p;

	p = &screenColor;
	p->show();

	Color colors[3];
	p = colors;

	p[0].setColor(255, 0, 0);
	p[1].setColor(0, 255, 0);
	p[2].setColor(0, 0, 255);

	for (int i = 0; i < 3; i++)
	{
		p[i].show(); // (p+i) -> show();
	}
}
