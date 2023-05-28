#ifndef _PACMAN_H_
#define _PACMAN_H_
#include "Creature.h"
#include "Point.h"

class Pacman :public Creature
{
private:
	char arrowKeys[SIZEARROWKEYS];
public:
	Pacman(Point _body, char _figure); //ctor

	//set
	void setArrowKeys(const char* keys);
	void setDirection(int dir);

	//get
	int getDirectionFromKB(char key) const;

	//utiles
	void move(char c, const Point& size);
	void movePacman(int dir, const Point& size);
};

#endif