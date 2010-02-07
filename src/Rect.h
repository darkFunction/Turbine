#ifndef RECT_H
#define RECT_H

class Rect
{
public:	
	int x, y, width, height;

	Rect() { }
	Rect(int x, int y, int width, int height)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

	~Rect() {}

private:
	


};


#endif

