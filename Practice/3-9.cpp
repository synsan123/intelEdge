#include <iostream>
using namespace std;

class Oval
{
public:
	Oval();
	Oval(int x, int y);
	~Oval();
	int getwidth();
	int getheight();
	void set(int w, int h);
	void show();
private:
	int width, height;
};

Oval::Oval()
{
	width = 1;
	height = 1;
}
Oval::Oval(int x, int y)
{
	width = x;
	height = y;
}

Oval::~Oval()
{
	cout << "Oval ¼Ò¸ê : width = " << width << ',' << " height = " << height << endl;
}

int Oval::getwidth()
{
	return width;
}

int Oval::getheight()
{
	return height;
}

void Oval::set(int w, int h)
{
	width = w;
	height = h;
}
void Oval::show()
{
	cout << "width = " << width << " height = " << height << endl;
}
int main()
{
	Oval a, b(3, 4);
	a.set(10, 20);
	a.show();
	cout << b.getwidth() << "," << b.getheight() << endl;
}