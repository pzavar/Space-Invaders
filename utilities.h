#ifndef UTILITIES_H
#define UTILITIES_H

//const char LEFT_KEY  = 'a';
//const char RIGHT_KEY= 'd';
//const char UP_KEY    = 'w';
//const char DOWN_KEY = 's';


const int SCREEN_WIDTH = 30;
const int SCREEN_HEIGHT = 20;

const int BOARD_WIDTH = SCREEN_WIDTH - (int)(SCREEN_WIDTH * .1);
const int BOARD_HEIGHT = SCREEN_HEIGHT - (int)(SCREEN_HEIGHT * .1);

const int BOARD_X = 0;
const int BOARD_Y = 0;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int HERO_PROMPT_X = 0;
const int HERO_PROMPT_Y = BOARD_HEIGHT + 1;

#endif
