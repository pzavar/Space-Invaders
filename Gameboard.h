#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <vector>
#include<string>
using namespace std;


class Screen;
class Hero;
class Alien;
class Laser;
class Actor;
class Game;

class Gameboard
{
public:
	Gameboard();
	~Gameboard();

	void drawBorder(Screen& screen);
	void drawActor(Screen& screen, Actor * actor);
	void drawLaser(Screen& screen, Laser * actor);
	void displayStats(Screen& screen, Hero * hero);
	void nextLevel(Screen & screen, Game*game);
	void displayScore(Screen & screen, Game * game);
private:
	Hero * m_hero;
	vector<Alien*> m_aliens;
	vector<Laser*> m_lasers;
	//string m_board[30];
};

#endif // GAMEBOARD_INCLUDED

