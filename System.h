#ifndef _System_H_
#define _System_H_

#include "Board.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"
#include "Symbols.h"

class System {
	BoardGame board;
	vector <Ghost> vecGhosts;
public:
	System(string file):board(file) {} //ctor
	
	//utiles
	bool run(int* score, int* lives, int level);
	void initGhosts();
	Point locationForFruit()const;
	bool isFood(int dir, int x, int y)const;
	bool isKill(const Point& cretureLoc)const;
	bool isEaten(const Point& pacLoc, const Point& fruitLoc)const;
	void pauseGame() const;
	void draw(int x, int y, char ch)const;
	void showGhosts() const;
	bool isValidLoc(int x, int y)const;
	void handleKeyPress(Pacman& pac, int& scoreCount, int& livesCount, BoardGame& board);
	void handleFruitMovement(Fruit* newFruit, bool& fruitFlag, const Pacman& pac, int& countFruit, int& timeFruit, bool& eatFruit);
	void handleFruitEating(Fruit*& newFruit, bool& eatFruit, int& scoreCount, int& countFruit, int& timeFruit);
	void handleFoodEating(Pacman& pac, int& scoreCount, int& checkScore, BoardGame& board);
	void handlePacmanKill(Pacman& pac, int& livesCount, BoardGame& board, vector<Ghost>& vecGhosts);
};

#endif
