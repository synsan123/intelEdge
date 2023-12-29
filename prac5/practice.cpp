#include <iostream>
using namespace std;

#if 0
class Rect;
bool equals(Rect w, Rect h);

class Rect {
	int width, height;
public:
	Rect(int width, int height) {
		this->width = width;
		this->height = height;
	}
	friend bool equals(Rect w, Rect h);
};

bool equals(Rect w, Rect h)
{
	if (w.width == h.width && w.height == h.height) return true;
	else return false;
}

int main()
{
	Rect a(5, 10), b(5, 10);
	if (equals(a, b)) cout << "same" << endl;
	else cout << "Not same" << endl;
}
#endif

#if 0
class Rect;

class RectManager {
public:
	bool equals(Rect w, Rect h);
	void copy(Rect& dest, Rect& src);
};

class Rect {
	int width, height;
public:
	Rect(int width, int height) {
		this->width = width;
		this->height = height;
	}
	friend RectManager;
};

bool RectManager::equals(Rect w, Rect h)
{
	if (w.width == h.width && w.height == h.height) return true;
	else return false;
}

void RectManager::copy(Rect& dest, Rect& src)
{
	dest.width = src.width;
	dest.height = src.height;
}

int main()
{
	Rect a(5, 10), b(1, 2);
	RectManager man;

	man.copy(b, a);
	if (man.equals(a, b)) cout << "same" << endl;
	else cout << "Not same" << endl;
}
#endif

#if 0
class Power {
	int kick;
	int punch;
public:
	Power(int kick = 0, int punch = 0) {
		this->kick = kick;
		this->punch = punch;
	}
	Power operator + (Power op2); // Power& op2 도 가능
	void show() {
		cout << "kick " << kick << " punch " << punch << endl;
	}
};

Power Power::operator+(Power op2) { // kick이랑 punch는 this->kick, this->punch가능
	Power tmp;
	tmp.kick = kick + op2.kick;
	tmp.punch = punch + op2.punch;
	return tmp;
}

int main()
{
	Power a(10, 20), b(20, 30), c;
	c = a + b; 
	a.show();
	b.show();
	c.show();
}
#endif

#if 0
class Power {
	int kick;
	int punch;
public:
	Power(int kick, int punch) { this->kick = kick; this->punch = punch; }
	bool operator ==(Power op2);
	void show() {
		cout << "kick " << kick << " punch " << punch << endl;
	}
};

bool Power::operator==(Power op2) // this ->kick이랑 punch는 kick과 punch 가능
{
	if (kick == op2.kick && punch == op2.punch) return true;
	else return false;
}

int main()
{
	Power a(3, 5), b(3, 5);
	a.show();
	b.show();
	if (a == b) cout << "same" << endl;
	else cout << "No same" << endl;
}
#endif

#if 0
class Power {
	int kick;
	int punch;
public:
	Power(int kick = 0, int punch = 0) {
		this->kick = kick; this->punch = punch;
	}
	Power& operator +=(Power op2);
	void show() { cout << "kick = " << kick << " punch = " << punch << endl; }
};

Power& Power::operator+=(Power op2) { //this->kick이랑 this->punch는 kick이랑 punch만 해도됨.
	kick = this->kick + op2.kick;
	punch = this->punch + op2.punch;
	return *this;
}

int main()
{
	Power a(5, 10), b(15, 20), c;
	a.show();
	b.show();
	c = a += b;
	c.show();
}
#endif

#if 0
class Power {
	int kick;
	int punch;
public:
	Power(int kick = 0, int punch = 0) {
		this->kick = kick; this->punch = punch;
	}
	Power operator+(int op2);
	void show() { cout << "kick = " << kick << " punch = " << punch << endl; }
};

Power Power::operator+(int op2)
{
	Power tmp;
	tmp.kick = kick + op2;
	tmp.punch = punch + op2;
	return tmp;
}

int main()
{
	Power a(5, 10), b;
	a.show();
	b.show();
	b = a + 2;
	a.show();
	b.show();
}
#endif

#if 0
class Power {
	int kick;
	int punch;
public:
	Power(int kick = 0, int punch = 0) {
		this->kick = kick; this->punch = punch;
	}
	Power& operator ++();
	void show() { cout << "kick = " << kick << " punch = " << punch << endl; }
};

Power& Power::operator++() {
	this->kick++;  //kick++ 가능
	this->punch++; //punch++ 가능
	return *this;
}

int main()
{
	Power a(5, 10), b;
	a.show();
	b.show();
	b = ++a;
	a.show();
	b.show();
}
#endif

#if 0
class Power {
	int kick;
	int punch;
public:
	Power(int kick = 0, int punch = 0) {
		this->kick = kick; this->punch = punch;
	}
	bool operator !();
};

bool Power::operator!() {
	if (kick == 0 && punch == 0) return true;
	else return false;
}

int main()
{
	Power a(0, 0), b(10, 20);
	if (!a)cout << "a의 파워는 0이다" << endl;
	else cout << "a의 파워는 0이 아니다" << endl;
	if (!b)cout << "b의 파워는 0이다" << endl;
	else cout << "b의 파워는 0이 아니다" << endl;
}
#endif

#if 0
class Power {
	int kick;
	int punch;
public:
	Power(int kick = 0, int punch = 0) {
		this->kick = kick; this->punch = punch;
	}
	Power operator++(int x);
	void show() { cout << "kick = " << kick << " punch = " << punch << endl; }
};

Power Power::operator++(int x)
{
	Power tmp = *this;
	kick++;
	punch++;
	return tmp;
}

int main()
{
	Power a(5, 10), b;
	a.show();
	b.show();
	b = a++;
	a.show();
	b.show();
}
#endif

#if 0
class Power {
	int kick;
	int punch;
public:
	Power(int kick = 0, int punch = 0) {
		this->kick = kick; this->punch = punch;
	}
	friend Power operator+(int op1, Power op2);
	void show() { cout << "kick = " << kick << " punch = " << punch << endl; }
};

Power operator+(int op1, Power op2) {
	Power tmp;
	tmp.kick = op1 + op2.kick;
	tmp.punch = op1 + op2.punch;
	return tmp;
}

int main()
{
	Power a(2, 5), b;
	a.show();
	b.show();
	b = 2 + a;
	a.show();
	b.show();
}
#endif

#if 0
class Power {
	int kick;
	int punch;
public:
	Power(int kick = 0, int punch = 0) {
		this->kick = kick; this->punch = punch;
	}
	friend Power operator+(Power op1, Power op2);
	void show() { cout << "kick = " << kick << " punch = " << punch << endl; }
};

Power operator+(Power op1, Power op2)
{
	Power tmp;
	tmp.kick = op1.kick + op2.kick;
	tmp.punch = op1.punch + op2.punch;
	return tmp;
}

int main()
{
	Power a(5, 10), b(15, 20), c;
	a.show();
	b.show();
	c = a + b;
	c.show();
}
#endif

#if 0
class Power {
	int kick;
	int punch;
public:
	Power(int kick = 0, int punch = 0) {
		this->kick = kick; this->punch = punch;
	}
	void show() { cout << "kick = " << kick << " punch = " << punch << endl; }
	friend Power& operator++(Power& op1);
	friend Power operator++(Power& op1, int x);
};

Power& operator++(Power& op1) {
	op1.kick++;
	op1.punch++;
	return op1;
}

Power operator++(Power& op1, int x) {
	Power tmp = op1;
	op1.kick++;
	op1.punch++;
	return tmp;
}

int main()
{
	Power a(3, 5), b;
	b = ++a;
	a.show(); b.show();

	b = a++;
	a.show(); b.show();
}
#endif

#if 0
class Power {
	int kick, punch;
public:
	Power(int kick = 0, int punch = 0) {
		this->kick = kick; this->punch = punch;
	}
	void show() { cout << "kick = " << kick << " punch = " << punch << endl; }
	Power& operator <<(int n);
};

Power& Power::operator<<(int n) {
	kick += n;
	punch += n;
	return *this;
}

int main()
{
	Power a(1,2);
	a.show();
	a << 3 << 6 << 9;
	a.show();
}
#endif

#if 0
class Power {
	int kick, punch;
public:
	Power(int kick = 0, int punch = 0) {
		this->kick = kick; this->punch = punch;
	}
	void show() { cout << "kick = " << kick << " punch = " << punch << endl; }
	friend Power& operator<<(Power& op, int n);
};

Power& operator<<(Power& op, int n) {
	op.kick += n;
	op.punch += n;
	return op;
}

int main()
{
	Power a(1, 2);
	a.show();
	a << 3 << 6 << 9;
	a.show();
}
#endif