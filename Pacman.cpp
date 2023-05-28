#include "Pacman.h"

//c'tor
Pacman::Pacman(Point _body, char _figure) : Creature(_body, _figure)
{
	setArrowKeys("wxads");
	setDirection(STAY);
}

//sets the keys array
void Pacman::setArrowKeys(const char* keys) 
{
	arrowKeys[0] = keys[0];
	arrowKeys[1] = keys[1];
	arrowKeys[2] = keys[2];
	arrowKeys[3] = keys[3];
	arrowKeys[4] = keys[4];
}

//set the direction of pacman
void Pacman::setDirection(int dir) 
{
	direction = dir;
}

//set the pacman direction from keyboard
int Pacman::getDirectionFromKB(char key) const
{
	for (int i = 0; i < SIZEARROWKEYS; i++)
	{
		if (key == arrowKeys[i])
			return i;
	}
	return -1;
}

//move and draw pacman
void Pacman::move(char c, const Point& size)
{
	body.draw(' ');
	movePacman(direction, size);
	body.draw(figure);
}

//move pacman
void Pacman::movePacman(int dir, const Point& size) 
{ 
	int x = body.getX();
	int y = body.getY();
	switch (dir) {
	case UP:
		body.setY(--y);
		if (y < 0) {
			body.setY(size.getY() - 1);
		}
		break;
	case DOWN:
		body.setY(++y);
		if (y >= size.getY()) {
			body.setY(0);
		}
		break;
	case LEFT:
		body.setX(--x);
		if (x < LEFTLIMIT) {
			body.setX(size.getX() - 1);
		}
		break;
	case RIGHT:
		body.setX(++x);
		if (x >= size.getX()) {
			body.setX(LEFTLIMIT);
		}
		break;
	case STAY:
		break;
	default:
		break;
	}
}