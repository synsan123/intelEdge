#ifndef BOX_H
#define BOX_H
class Box
{
public:
	Box(int w, int h);
	void setfill(char f);
	void setsize(int w, int h);
	void draw();
private:
	int width, height;
	char fill;
};
#endif