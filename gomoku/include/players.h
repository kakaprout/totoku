#ifndef __PLAYERS_H__
#define __PLAYERS_H__

#include "headers.h"
#include "player.h"
#include "gomoku.h"

class Players
{
public:
	Player *p1;
	Player *p2;
	bool change;

	Players();
	Player *get_current(Gomoku *g);
};

#endif
