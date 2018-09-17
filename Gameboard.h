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

class Gameboard
{
public:
	Gameboard();
	~Gameboard();
	void display(Screen& screen, int x, int y);
	Hero* getHero();
	Alien* getAlien();
	Laser* getLaser();

	void draw();
	void drawBorder(Screen& screen);
	void drawActor(Screen& screen, Actor * actor);
	void drawLaser(Screen& screen, Laser * actor);
	void displayStats(Screen& screen, Hero * hero);
	void addLaser(int row, int column);
	void displayVictory();

private:
	Hero * m_hero;
	vector<Alien*> m_aliens;
	vector<Laser*> m_lasers;
	//string m_board[30];
};

#endif // GAMEBOARD_INCLUDED

