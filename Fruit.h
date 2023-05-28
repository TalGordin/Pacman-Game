#ifndef FRUIT_H_
#define FRUIT_H_

#include "Creature.h"

class Fruit : public Creature
{
private:
	int* possibleDir;
	char* figureArr;

public:
	Fruit(Point _body, char _figure);//ctor
	~Fruit()//dtor
	{
		delete[] possibleDir;
		delete[] figureArr;
	}

	//set
	void setFigure();
	void setPossibleDir();
	void setDirection();
	void setDirection(int dir);
	void setFigureArr();
	
	// utiles
	void move(char ch, const BoardGame& board);
	void moveFruit(int dir, const BoardGame& board);
	
};


#endif // !FRUIT_H_
