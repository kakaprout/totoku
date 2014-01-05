#include "../include/players.h"

Players::Players()
{
	this->change = true;
	this->p1 = new Player(CASE_J1, false);
	this->p2 = new Player(CASE_J2, false);
}

Player * Players::get_current(Gomoku *g)
{
	this->p1->is_ia = g->ia1_activated;
	this->p2->is_ia = g->ia2_activated;

	if (g->p.size() == 0)
	{
		change = true;
	}

	if (change)
	{
		change = false;
		return (this->p1);
	}
	change = true;

	return (this->p2);
}
