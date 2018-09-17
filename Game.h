#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Gameboard.h"
#include "UserInterface.h"
using namespace std;


class Board;
class Hero;
class Alien;
class Laser;

class Game {
public:
	Game(int width, int height);
	~Game();
	void play();
	bool playOneLevel();
	void displayPrompt(std::string s);
	void displayStatus();
	void initState();
	void addLaser(Laser*laser);
	int die(const char * msg);
private:
	Gameboard m_board;
	Screen  m_screen;
	Hero* m_hero;
	vector<Alien*> m_aliens;
	vector<Laser*> m_lasers;
};

#endif // GAME_H
