#ifndef Game_h
#define Game_h

#include "NESController.h"
#include "Adafruit_WS2801.h"

#include "Color.h"
#include "Point.h"

class Game{
public:
	Game(NESController *controllerIn, Adafruit_WS2801 *stripIn);
	virtual ~Game();
	virtual void run();
	virtual void resume();
protected:
	NESController * controller;
	Adafruit_WS2801 * strip;
	
	Point curPos;
	const static int boardWidth = 10;
	const static int boardHeight = 20;
	Color board[boardWidth][boardHeight];
};

#endif
