#include "Game.h"
#include "Gameboard.h"
#include "UserInterface.h"
#include <iostream>
#include <string>
#include "Utilities.h"
#include "Actor.h"
#include "Alien.h"
#include "Hero.h"
#include "Laser.h"
#include <stdlib.h>
using namespace std;


Game::Game(int width, int height)
	: m_screen(SCREEN_WIDTH, SCREEN_HEIGHT)
{
}

Game::~Game() {
	delete m_hero;
	//m_aliens.clear();
	m_aliens.~vector();
	m_lasers.~vector();
}

void Game::addLaser(Laser *laser) {
	m_lasers.push_back(laser);
}

void Game::initState() {
	m_hero = new Hero(BOARD_HEIGHT - 2, BOARD_WIDTH / 2);
	//For arrays we have default constructor
	//		BUT using an array of ptrs works since ptrs have a default constructor

	//CHANGE. POORLY MADE ALIENS 
	//CHANGE. POORLY MADE ALIENS 
	//CHANGE. POORLY MADE ALIENS 
	for (int i = 1; i < 5; i++) {
		m_aliens.push_back(new Alien(3, i * 5));
	}
}



void Game::play()
{
	initState();
	/*
	// init everything
	// every 5s aliens move down a row // if collision: end game
	// if key pressed: perform action
	//	if ARROW_RIGHT: move right
	//	if SPACEBAR: shoot laser
	// every 1s lasers move/collide
	//

	*/
	

	displayPrompt("Press the Enter key to begin ENTER GAME NAME ");
	waitForEnter();  // [in UserInterface.h]



	m_screen.clear();
	m_board.drawBorder(m_screen);
	m_board.drawActor(m_screen, m_hero);
	/*m_board.display(m_screen, BOARD_X, BOARD_Y);
	displayStatus();*/

	char keyPressed;
	Timer timer;
	Timer timerDown;
	timer.start();
	timerDown.start();
	while (m_hero->getHP() > 0) {
		m_screen.clear();
		m_board.drawBorder(m_screen);
		m_board.displayStats(m_screen, m_hero);

		if (m_aliens.empty()) {
			m_board.displayVictory();
			//die("DIE");
		}

		if (getCharIfAny(keyPressed)) {
			//If the user moves
			if (keyPressed == ARROW_LEFT || keyPressed == ARROW_RIGHT) {
				m_hero->move(keyPressed);
			}
			//If user shoots laser
			if (keyPressed == ARROW_UP) {
				m_hero->shootLaser(this);
			}
		}//if(getChar)


		 //Draw Hero
		m_board.drawActor(m_screen, m_hero);

		//CHANGE. POORLY MADE ALIENS 
		//CHANGE. POORLY MADE ALIENS 
		//CHANGE. POORLY MADE ALIENS 
		//Draw aliens
		for (unsigned i = 0; i < m_aliens.size(); i++) {
			Alien * alienToDisplay = m_aliens.at(i);
			m_board.drawActor(m_screen, alienToDisplay);
		}

		//aliens shoot
		for (unsigned i = 0; i < m_aliens.size(); i++) {
			Alien *alienToShoot = m_aliens.at(i);
			if (!alienToShoot->hasShotAlready()) {
				alienToShoot->shootLaser(this);
			}
		}

		//Draw lasers if any
		for (unsigned i = 0; i < m_lasers.size(); i++) {
			Laser *laserToDisplay = m_lasers.at(i);
			m_board.drawLaser(m_screen, laserToDisplay);
		}

		//Move aliens
		for (unsigned i = 0; i < m_aliens.size(); i++) {
			Alien *alienToMove = m_aliens.at(i);
			alienToMove->move('&');
		}

		//Move laser
		for (unsigned i = 0; i < m_lasers.size(); i++) {
			Laser *laserToDisplay = m_lasers.at(i);
			Actor * shooter = laserToDisplay->getShooter();
			bool isFriendly = laserToDisplay->isFriendly();
			bool laserMoved = laserToDisplay->move('^');
			//If this is false we deleted the laserToDisplay
			//The laser in the vector works as a temp. WRONG!!!
			if (!laserMoved) {
				if (!isFriendly) {
					shooter->setHasShotAlready(false);
				}
				m_lasers.erase(m_lasers.begin() + i);
			}
		}

		//Check collisions
		for (unsigned i = 0; i < m_lasers.size(); i++) {
			Laser *laserToCheck = m_lasers.at(i);
			int laserRow = laserToCheck->getPosition().row;
			int laserColumn = laserToCheck->getPosition().column;

			//Check collision between aliens
			for (unsigned j = 0; j < m_aliens.size(); j++) {
				Alien *alienToCheck = m_aliens.at(j);
				int alienRow = alienToCheck->getPosition().row;
				int alienColumn = alienToCheck->getPosition().column;
				if ((abs(alienRow - laserRow) <= 1) && (abs(alienColumn - laserColumn) == 0) && laserToCheck->isFriendly()) {
					laserToCheck->collide(alienToCheck);
					m_lasers.erase(m_lasers.begin() + i);
					if (alienToCheck->getHP() <= 0) {
						m_aliens.erase(m_aliens.begin() + j);
					}
					cout << "ALIEN HIT" << endl;
				}
			}

			//Check collision with hero
			//Shouldn't use absolute value
			//The logic checks if the laser is about to hit
			//In the beginning when the user or alien just shoots the laser will be close to the person that shot
			//Using absolute value ignores direction
			int heroRow = m_hero->getPosition().row;
			int heroColumn = m_hero->getPosition().column;

			if (abs(heroRow - laserRow <= 1) && abs(heroColumn - laserColumn == 0)) {
				if (!laserToCheck->isFriendly()) {
					//need to set has shot already to false since that controls whether or not an alien shoots
					laserToCheck->getShooter()->setHasShotAlready(false);
					laserToCheck->collide(m_hero);
					m_lasers.erase(m_lasers.begin() + i);
					cout << "HERO HIT" << endl;
				}
			}
		}

		if (timerDown.elapsed() > 500)
		{
			for (unsigned i = 0; i < m_aliens.size(); i++) {
				Alien * alien = m_aliens.at(i);
				alien->move('d');
			}
			if (m_aliens.front()->getPosition().row == m_hero->getPosition().row) {
				m_aliens.front()->collide(m_hero);
			}
			timerDown.start();
		}

		while (timer.elapsed() < 100) {
		}
		timer.start();
	}

	//system("pause");
	m_screen.clear();
	displayPrompt("Level completed. Press Enter for next level\n.");

	waitForEnter();
}


void Game::displayPrompt(std::string s)
{
	m_screen.gotoXY(0, PROMPT_Y);
	m_screen.printStringClearLine(s);   // overwrites previous text
	m_screen.refresh();
}

void Game::displayStatus()
{
	// [Replace this with code to display the status.]
}



bool Game::playOneLevel()
{

	return false;  // [Replace this with the code to play a level.]
}

int Game::die(const char * msg)
{
	m_screen.gotoXY(0, 1);
	m_screen.printString("Fatal error: %s\n");
	exit(EXIT_FAILURE);
}
