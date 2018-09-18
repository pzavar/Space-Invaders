#include "Gameboard.h"
#include "UserInterface.h"
#include "Utilities.h"
#include "Actor.h"
#include "Laser.h"
#include "Hero.h"
#include "Game.h"

#include <iostream>
using namespace std;

void Gameboard::drawBorder(Screen& screen) {
	//top side
	//0 - 26

	for (int i = 0; i < BOARD_WIDTH; i++) {

		//system("Color C");

		screen.gotoXY(i, 0);
		screen.printChar('#');
	}
	//bottom side
	//The minus 1 helps it print
	//Loops only go up to SIZE - 1
	// 0 - 26

	for (int i = 0; i < BOARD_WIDTH; i++) {

		//system("Color C");
		screen.gotoXY(i, BOARD_HEIGHT - 1);
		screen.printChar('#');
	}
	//left side
	for (int i = 0; i < BOARD_HEIGHT; i++) {

		//system("Color C");
		screen.gotoXY(0, i);
		screen.printChar('#');
	}
	//right side
	for (int i = 1; i < BOARD_HEIGHT; i++) {


		//system("Color 9");
		screen.gotoXY(BOARD_WIDTH - 1, i);
		screen.printChar('#');
	}
	//system("Color 1");
	screen.printChar('\n');
}

void Gameboard::displayStats(Screen& screen, Hero * hero) {

	//Make hearts for health
	string hearts;
	for (int i = 0; i < hero->getHP(); i++) {
		hearts += "<3";
	}
	screen.gotoXY(HERO_PROMPT_X, HERO_PROMPT_Y);
	// This adding a string to an int causes weird issue
	//screen.printString("Hero: " + hero->getHP());
	string health = to_string(hero->getHP());
	string heroString = "Hero: " + health + '\n';

	screen.printString(heroString);
	screen.gotoXY(HERO_PROMPT_X, HERO_PROMPT_Y + 1);
	screen.printString("Weapon: |");
}

void Gameboard::nextLevel(Screen & screen, Game*game)
{
	screen.clear();
	screen.gotoXY(0,0);
	string level = to_string(game->getLevel());
	string message = "\tLevel completed.\n\tMoving on to Level " + level;
	message += "...\n";
	message += "\t+1 Alien @_@\n";
	screen.printString(message);
}

void Gameboard::displayScore(Screen & screen, Game * game)
{
	screen.gotoXY(0,0);
	string message = "GAME OVER!\n";
	message += "Level: " + to_string(game->getLevel()) + "\n";
	message += "Score: " + to_string(game->getScore()) + "\n";
	float floatTime = (float)game->getTimePlayed() / 1000;
	floatTime = (floatTime*100.0) / 100.0;
	message += "Time Played: " + to_string(floatTime) + " seconds\n";
	screen.printString(message);
}


void Gameboard::drawActor(Screen& screen, Actor * actor) {
	screen.gotoXY(actor->getPosition().column, actor->getPosition().row);
	screen.printChar(actor->getSymbol());
}

void Gameboard::drawLaser(Screen& screen, Laser * laser) {
	screen.gotoXY(laser->getPosition().column, laser->getPosition().row);
	screen.printChar(laser->getSymbol());
}



Gameboard::Gameboard() {

}


Gameboard::
~Gameboard() {

}