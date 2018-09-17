#ifndef ALIEN_H
#define ALIEN_H

#include "Actor.h"

class Hero;

class Alien : public Actor {
public:
	Alien(int row, int position);
	virtual ~Alien();
	void collide(Hero* hero);
	bool move(char key);
	void shootLaser(Game*game);
private:
	int m_direction;
};

#endif // ALIEN_H
