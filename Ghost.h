#ifndef GHOST_H_
#define GHOST_H_

#include "Point.h"
#include "Creature.h"

class Ghost : public Creature
{
private:
	int possibleDir[SIZEDIR];
public:
	Ghost(Point _body, char _figure);//ctor
	//set
	void setPossibleDir();
	void setDirection();
	void setSmartDirection(int dir);
	//get

	//utiles
	
	void move(char ch, const BoardGame& board, const Point& pacPoint, int level, int numOfGhosts);
	void moveByLevel(const BoardGame& board, const Point& pacPoint, int level, int numOfGhosts);
	void moveGhost(int dir, const BoardGame& board);
	void smartMove(const BoardGame& board, const Point& pacPoint);
	bool isValidStep(const vector<vector<bool>> visit, int row, int col, const BoardGame& board)const;
	Point BFS(const BoardGame& board, vector<vector<bool>> visit, const Point& pacPoint)const;
	
};
#endif 

