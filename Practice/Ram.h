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
	char mem[100 * 1024];// 100KB �޸�, �� ������ 1Byte
};
#endif
