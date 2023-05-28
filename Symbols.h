#ifndef SYMBOLS_H_
#define SYMBOLS_H_

/*All symbols in the game*/

enum 
{
	SPACE = ' ',
	WALL = '#',
	FOOD = '.',
	PACMAN = (char)002,
	GHOST = (char)234,
	LEGEND = '&',
	UP = 0, 
	DOWN,
	LEFT, 
	RIGHT,
	STAY,
	LEFTLIMIT = 0,
	UPLIMIT = 0,
	LIMIT = 2,
	SIZEDIR = 4,
	SIZEFIGUREARR = 5,
	SIZEARROWKEYS = 5,
	ESC = 27,
	MAXROWS = 25, 
	MAXCOLS = 80,
	BEST = 'a',
	GOOD = 'b',
	NOVICE = 'c',
	MOVEBOARD = 1,
	FINISH = 2,
	WINNER = 3,
	NEWGAME = '1',
	SCREENUSER = '2',
	INSTRUCTIONS = '8',
	EXITGAME = '9'
};
#endif // !SYMBOLS_H_
