#include <iostream>
using namespace std;

class Shape {
protected:
	virtual void draw() {
		cout << "Shape Draw" << endl;
	}
public:
	friend void paint(Shape* p);
};

class Circle :public Shape {
protected:
	virtual void draw() {
		cout << "Circle Draw" << endl;
	}
};

class Rect : public Shape {
protected:
	virtual void draw() {
		cout << "Rectangle Draw" << endl;
	}
};

class Line : public Shape {
protected:
	virtual void draw() {
		cout << "Line draw" << endl;
	}
};

void paint(Shape * p) {
	p->draw();
}

int main()
{
	Shape *shape = new Shape();
	paint(shape);
	Shape* shape1 = new Circle();
	paint(shape1);
	Shape* shape2 = new Rect();
	paint(shape2);
	Shape* shape3 = new Line();
	paint(shape3);
	delete shape;
	delete shape1;
	delete shape2;
	delete shape3;

	return 0;

	
}