#include <iostream>
#include <string>
using namespace std;

class Buffer
{
public:
	Buffer(string text) { this->text = text; }
	void add(string next) { text += next; }
	void print() { cout << text << endl; }
private:
	string text;
};

Buffer& append(Buffer& buffer, string add_text)
{
	buffer.add(add_text);
	return buffer;
}
int main()
{
	Buffer buf("Hello");
	Buffer& temp = append(buf, "Guys");
	temp.print();
	buf.print();
}