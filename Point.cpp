#include "Point.h"

//c'tor 
Point::Point(int x, int y)
{
	_x = x;
	_y = y;
}

//draw the char appears on the screen 
void Point::draw(char ch) {
	gotoxy(_x, _y);
	cout << ch << endl;
}

//set x point
void Point::setX(int x)
{
	_x = x;
}

//set y point
void Point::setY(int y)
{
	_y = y;
}

//get x point
int Point::getX() const
{
	return _x;
}

//get y point
int Point::getY() const
{
	return _y;
}

//opertor compare between two points
bool Point::operator==(const Point& p)const
{
	return((this->getX() == p.getX()) && this->getY() == p.getY());
}
