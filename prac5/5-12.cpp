#include <iostream>
using namespace std;

#if 0
class Dept
{
public:
	Dept(int size) {
		this->size = size;
		scores = new int[size];
	}
	Dept(Dept& dept);
	~Dept();
	int getSize() { return size; }
	void read();
	bool isOver60(int index);
private:
	int size;
	int* scores;
};

Dept::Dept(Dept& dept)
{
	this->size = dept.size;
	this->scores = new int[this->size];
	for (int i = 0; i < this->size; i++)
	{
		this->scores[i] = dept.scores[i];
	}
}

Dept::~Dept()
{
	delete[] scores;
}

int countPass(Dept dept)
{
	int count = 0;
	for (int i = 0; i < dept.getSize(); i++)
	{
		if (dept.isOver60(i)) count++;
	}
	return count;
}

void Dept::read() {
	cout << size << "�� ���� �Է� >> ";
	for (int i = 0; i < size; i++)
	{
		cin >> scores[i];
	}
}

bool Dept::isOver60(int index)
{
	if (scores[index] > 60) return true;
	else return false;
}

int main()
{
	Dept com(10);
	com.read();
	int n = countPass(com);
	cout << "60�� �̻��� " << n << "��";
}
#endif

// ���� �����ڸ� �����ϰ� �����Ѱ�.
class Dept {
	int size;
	int* scores;
public:
	Dept(int size) {
		this->size = size;
		scores = new int[size];
	}
	~Dept();
	int getSize() { return size; }
	void read();
	bool isOver60(int index);
};

int countPass(Dept& dept) { // ������ ���� ȣ��� ���� 
	int count = 0;
	for (int i = 0; i < dept.getSize(); i++) {
		if (dept.isOver60(i))
			count++;
	}
	return count;
}

Dept::~Dept() {
	delete[] scores;
}
void Dept::read() {
	cout << size << "�� ���� �Է�>> ";
	for (int i = 0; i < size; ++i) {
		cin >> scores[i];
	}
}
bool Dept::isOver60(int index) {
	if (scores[index] > 60)
		return true;
	else
		return false;
}

int main() {
	Dept com(10);
	com.read();
	int n = countPass(com);
	cout << "60�� �̻��� " << n << "��";
}
