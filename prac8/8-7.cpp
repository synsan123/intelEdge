#include <iostream>

using namespace std;

class BaseMemory {
	char* mem;
protected:
	BaseMemory(int size) { mem = new char[size]; }
	void setData(char x, int length) { mem[length] = x; }
	void setData(char x[], int length) { for (int i = 0; i < length; i++) mem[i] = x[i]; }
	char getData(int index) { return mem[index]; }
};

class ROM : public BaseMemory {
public:
	ROM(int size, char x[], int length) :BaseMemory(size) { setData(x, length); }
	char read(int index) { return getData(index); }
};

class RAM : public BaseMemory {
public:
	RAM(int size) : BaseMemory(size) {}
	void write(int index, char data) { setData(data, index); }
	char read(int index) { return getData(index); }
};

int main() {
	char x[5] = { 'h','e','l','l','o' };
	ROM biosROM(1024 * 10, x, 5);
	RAM mainMemory(1024 * 1024);

	for (int i = 0; i < 5; i++) mainMemory.write(i, biosROM.read(i));
	for (int i = 0; i < 5; i++) cout << mainMemory.read(i);
	return 0;
}