#include "Game.h"
#include "MovingObject.h"
#include "Actor.h"
#include "Hero.h"
#include "Actor.h"
#include "Laser.h"
#include <iostream>
#include "Utilities.h"
using namespace std;

int main()
{
	Game g(SCREEN_WIDTH, SCREEN_HEIGHT);
	g.play();
}


