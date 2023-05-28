#include "System.h"

//the start run function of the game - controls the function that implements the game
bool System::run(int* score, int* lives, int level)
{
	int key = 0, tempKey, dir, movePac = 0, scoreCount, livesCount, i, countFruit = 0, timeFruit = 0, moveGhost = 0, fruitScore, checkScore;
	bool flagGhost = false, eatFruit = false, fruitFlag = false, flag = false;
	char c;
	Pacman pac(board.getPacmanPos(), PACMAN);
	Point location;
	Fruit* newFruit = new Fruit(location, '0');

	if (!board.getVaild())
		return false;

	initGhosts();

	checkScore = board.getScoreWin();
	scoreCount = *score;
	livesCount = *lives;
	
	hideCursor();
	board.printBoard(scoreCount, livesCount);
	showGhosts();

	location = locationForFruit();
	newFruit->setFigure();
	newFruit->show(newFruit->getPoint().getX(), newFruit->getPoint().getY());

	do {
		board.printScore(scoreCount);
		board.printLives(livesCount);
		handleKeyPress(pac, scoreCount, livesCount, board);
		handleFruitMovement(newFruit, fruitFlag, pac, countFruit, timeFruit, eatFruit);
		handleFruitEating(newFruit, eatFruit, scoreCount, countFruit, timeFruit);
		handleFoodEating(pac, scoreCount, checkScore, board);
		handlePacmanKill(pac, livesCount, board, vecGhosts);

		if (pac.isWall(board, pac.getDirection(), pac.getPoint().getX(), pac.getPoint().getY()))
			pac.setDirection(STAY);
		else
		{
			pac.move(SPACE, board.getSize());
			movePac++;
			countFruit++;
			timeFruit++;
			if (movePac == 2)
			{
				flagGhost = true;
				movePac = 0;
			}
			if (flagGhost)
			{
					for (i = 0; i < board.getVecGhostSize(); i++)
						vecGhosts[i].move(board.get(vecGhosts[i].getPoint().getX(), vecGhosts[i].getPoint().getY()), board, pac.getPoint(), level, board.getVecGhostSize());
				moveGhost++;
			
				flagGhost = false;
			}
			if (moveGhost == 2)
			{
				fruitFlag = true;
				moveGhost = 0;
			}
			Sleep(100);

		}
	} while (checkScore > 0 && livesCount != 0);

	clear_screen();
	*score = scoreCount;
	*lives = livesCount;
	if (livesCount == 0)
		return false;
	else
		return true;
}

//initialise ghosts in positionsr
void System::initGhosts()
{
	for (int i = 0; i < board.getVecGhostSize(); i++)
	{
		vecGhosts.push_back(Ghost(board.getGhostPos(i), GHOST));
	}
}

//print pause game
void System::pauseGame() const
{
	clear_screen();
	cout << "Game paused, press ESC again to continue.";
	_kbhit();
}

//boolean check if the pacman eat breadcramb in current point
bool System::isFood(int dir, int x, int y)const
{
	char c = board.get(x, y);
	return(c == FOOD);
}

//boolean check if the ghosts eats the pacman or fruit
bool System::isKill(const Point& cretureLoc)const
{
	for (int i = 0; i < board.getVecGhostSize(); i++)
		if(cretureLoc == vecGhosts[i].getPoint())
			return true;
	return false;
}

//boolean check if the pacman eat the fruit
bool System::isEaten(const Point& pacLoc, const Point& fruitLoc)const
{
	Point temp;
	int i, j;
	for (i = -1; i <= 1; i++)
	{
		for (j = -1; j <= 1; j++)
		{
			temp.setX(pacLoc.getX() + i);
			temp.setY(pacLoc.getY() + j);
			if (temp == fruitLoc)
				return true;
		}
	}
	return false;
}

//draw the char that received to the screen
void System::draw(int x, int y, char ch)const
{
	gotoxy(x, y);
	cout << ch << endl;
}

//showing ghosts
void System::showGhosts() const
{
	for (int i = 0; i < board.getVecGhostSize(); i++)
		vecGhosts[i].show(board.getGhostPos(i).getX(), board.getGhostPos(i).getY());
}

//randomizing valid location for the fruit
Point System::locationForFruit()const
{
	Point temp;
	int x, y;
	srand((unsigned int)time(NULL));
	x = rand() % board.getSize().getX();
	y = rand() % board.getSize().getY();
	while (!isValidLoc(x, y))
	{
		x = rand() % board.getSize().getX();
		y = rand() % board.getSize().getY();
	}
	temp.setX(x);
	temp.setY(y);
	return temp;
}

//boolean check if the location for the fruit is valid
bool System::isValidLoc(int x, int y)const
{
	return ((board.get(x, y) == FOOD) || (board.get(x, y) == SPACE));
}

//controling the kee press of the user and implementing the outcome tof the press
void System::handleKeyPress(Pacman& pac, int& scoreCount, int& livesCount, BoardGame& board)
{
	if (_kbhit())
	{
		int key = _getch();
		if (key == ESC)
		{
			pauseGame();
			key = _getch();
			while (key != ESC)
			{
				_kbhit();
				key = _getch();
			}
			clear_screen();
			board.printBoard(scoreCount, livesCount);
		}
		else
		{
			int tempKey = key;
			if (isupper(tempKey))
				key = tolower(tempKey);

			int dir = pac.getDirectionFromKB(key);
			if (dir != -1)
			{
				pac.setDirection(dir);
			}
		}
	}
}

//controling fruit movement
void System::handleFruitMovement(Fruit* newFruit, bool& fruitFlag, const Pacman& pac, int& countFruit, int& timeFruit, bool& eatFruit)
{
	if (newFruit && fruitFlag)
	{
		fruitFlag = false;
		newFruit->move(board.get(newFruit->getPoint().getX(), newFruit->getPoint().getY()), board);
		eatFruit = isEaten(pac.getPoint(), newFruit->getPoint());
	}
}

//controling fruit eating and outcomes in the game
void System::handleFruitEating(Fruit*& newFruit, bool& eatFruit, int& scoreCount, int& countFruit, int& timeFruit)
{
	if (countFruit == 100 || eatFruit || (newFruit && isKill(newFruit->getPoint())))
	{
		if (newFruit)
		{
			if (eatFruit)
			{
				int fruitScore = int(newFruit->getFigure() - '0');
				scoreCount += fruitScore;
			}
			char c = board.get(newFruit->getPoint().getX(), newFruit->getPoint().getY());
			newFruit->Creature::setFigure(c);
			newFruit->show(newFruit->getPoint().getX(), newFruit->getPoint().getY());
			delete newFruit;
			newFruit = nullptr;
		}
		else if (timeFruit == 200)
		{
			timeFruit = 0;
			Point location = locationForFruit();
			newFruit = new Fruit(location, '0');
			newFruit->setFigure();
			newFruit->show(newFruit->getPoint().getX(), newFruit->getPoint().getY());
		}
		countFruit = 0;
	}
}

//controling food eating and outcomes in the game
void System::handleFoodEating(Pacman& pac, int& scoreCount, int& checkScore, BoardGame& board)
{
	if (isFood(pac.getDirection(), pac.getPoint().getX(), pac.getPoint().getY()))
	{
		if (pac.getDirection() != STAY)
		{
			scoreCount++;
			checkScore--;
			board.updateBoard(pac.getPoint().getX(), pac.getPoint().getY(), SPACE);
		}
	}
}

//controling pacmen lives and outcomes in the game
void System::handlePacmanKill(Pacman& pac, int& livesCount, BoardGame& board, vector<Ghost>& vecGhosts)
{
	if (isKill(pac.getPoint()))
	{
		livesCount--;
		draw(pac.getPoint().getX(), pac.getPoint().getY(), SPACE);
		for (int i = 0; i < board.getVecGhostSize(); i++)
			draw(vecGhosts[i].getPoint().getX(), vecGhosts[i].getPoint().getY(), board.get(vecGhosts[i].getPoint().getX(), vecGhosts[i].getPoint().getY()));
		pac.setBody(board.getPacmanPos());
		pac.setDirection(STAY);
		for (int i = 0; i < board.getVecGhostSize(); i++)
			vecGhosts[i].setBody(board.getGhostPos(i));
		showGhosts();
	}
}
