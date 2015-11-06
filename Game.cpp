#include "Game.h"

Game::Game(NESController *controllerIn, Adafruit_WS2801 *stripIn){
	controller = controllerIn;
	strip = stripIn;
	
	curPos.setPosition(5,0);
}

Game::~Game(){
};

void Game::run(){};
void Game::resume(){};
