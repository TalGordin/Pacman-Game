#ifndef _POINT_H_
#define _POINT_H_

#include "io_utils.h"

class Point {
	unsigned int _x;
	unsigned int _y;
public:
	Point() { _x = 0, _y = 0; };//defult ctor
	Point(int x, int y); //ctor
	bool operator==(const Point& p)const;

	//set
	void setX(int x);
	void setY(int y);
	//get
	int getX() const;
	int getY() const;
	//utiles
	void draw(char ch);
	
	
	
};

#endif