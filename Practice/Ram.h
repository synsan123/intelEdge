#ifndef RAM_H
#define RAM_H
class Ram
{
public:
	Ram();
	~Ram();
	char read(int address);
	void write(int address, char value);
private:
	int size;
	char mem[100 * 1024];// 100KB 메모리, 한 번지는 1Byte
};
#endif
