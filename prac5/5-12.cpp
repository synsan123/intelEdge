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
	cout << size << "개 점수 입력 >> ";
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
	cout << "60점 이상은 " << n << "명";
}
#endif

// 복사 생성자를 제거하고 수정한거.
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

int countPass(Dept& dept) { // 참조에 의한 호출로 변경 
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
	cout << size << "개 점수 입력>> ";
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
	cout << "60점 이상은 " << n << "명";
}
