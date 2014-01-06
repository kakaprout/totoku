#include "../include/ia.h"

Player_ia::Player_ia(char player)
{
	this->numPlayer = player;
	this->_alignPtr = new alignPtr[8];
	this->_alignPtr[0] = &Player_ia::checkUpAlign;
	this->_alignPtr[1] = &Player_ia::checkDownAlign;
	this->_alignPtr[2] = &Player_ia::checkRightAlign;
	this->_alignPtr[3] = &Player_ia::checkLeftAlign;
	this->_alignPtr[4] = &Player_ia::checkUpRightAlign;
	this->_alignPtr[5] = &Player_ia::checkUpLeftAlign;
	this->_alignPtr[6] = &Player_ia::checkDownLeftAlign;
	this->_alignPtr[7] = &Player_ia::checkDownRightAlign;
}

Player_ia::~Player_ia()
{
}

int				Player_ia::checkDownAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter)
{
	counter = 0;
	y = to_ev.y + 1;

	while (y < 20 && g->c[y][to_ev.x] == to_ev.player)
	{
		++counter;
		++y;
	}
	switch (counter)
	{
	case 0:
		return 0;
		break;
	case 1:
		return COMPLETE_LINE_1;
		break;
	case 2:
		return COMPLETE_LINE_2;
		break;
	case 3:
		return COMPLETE_LINE_3;
		break;
	case 4:
		return COMPLETE_LINE_4;
		break;
	case 5:
		return WIN;
		break;
	}
}

int				Player_ia::checkUpAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter)
{
	counter = 0;
	y = to_ev.y - 1;

	while (y >= 0 && g->c[y][to_ev.x] == to_ev.player)
	{
		++counter;
		--y;
	}
	switch (counter)
	{
	case 0:
		return 0;
		break;
	case 1:
		return COMPLETE_LINE_1;
		break;
	case 2:
		return COMPLETE_LINE_2;
		break;
	case 3:
		return COMPLETE_LINE_3;
		break;
	case 4:
		return COMPLETE_LINE_4;
		break;
	case 5:
		return WIN;
		break;
	}
}

int				Player_ia::checkLeftAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter)
{
	counter = 0;
	x = to_ev.x - 1;

	while (x >= 0 && g->c[to_ev.y][x] == to_ev.player)
	{
		++counter;
		--x;
	}
	switch (counter)
	{
	case 0:
		return 0;
		break;
	case 1:
		return COMPLETE_LINE_1;
		break;
	case 2:
		return COMPLETE_LINE_2;
		break;
	case 3:
		return COMPLETE_LINE_3;
		break;
	case 4:
		return COMPLETE_LINE_4;
		break;
	case 5:
		return WIN;
		break;
	}
}

int				Player_ia::checkRightAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter)
{
	counter = 0;
	x = to_ev.x + 1;

	while (x < 20 && g->c[to_ev.y][x] == to_ev.player)
	{
		++counter;
		++x;
	}
	switch (counter)
	{
	case 0:
		return 0;
		break;
	case 1:
		return COMPLETE_LINE_1;
		break;
	case 2:
		return COMPLETE_LINE_2;
		break;
	case 3:
		return COMPLETE_LINE_3;
		break;
	case 4:
		return COMPLETE_LINE_4;
		break;
	case 5:
		return WIN;
		break;
	}
}

int				Player_ia::checkUpLeftAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter)
{
	counter = 0;
	x = to_ev.x - 1;
	y = to_ev.y - 1;

	while (x >= 0 && y >= 0 && g->c[y][x] == to_ev.player)
	{
		++counter;
		--x;
		--y;
	}
	switch (counter)
	{
	case 0:
		return 0;
		break;
	case 1:
		return COMPLETE_LINE_1;
		break;
	case 2:
		return COMPLETE_LINE_2;
		break;
	case 3:
		return COMPLETE_LINE_3;
		break;
	case 4:
		return COMPLETE_LINE_4;
		break;
	case 5:
		return WIN;
		break;
	}
}

int				Player_ia::checkUpRightAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter)
{
	counter = 0;
	x = to_ev.x + 1;
	y = to_ev.y - 1;

	while (x < 20 && y >= 0 && g->c[y][x] == to_ev.player)
	{
		++counter;
		++x;
		--y;
	}
	switch (counter)
	{
	case 0:
		return 0;
		break;
	case 1:
		return COMPLETE_LINE_1;
		break;
	case 2:
		return COMPLETE_LINE_2;
		break;
	case 3:
		return COMPLETE_LINE_3;
		break;
	case 4:
		return COMPLETE_LINE_4;
		break;
	case 5:
		return WIN;
		break;
	}
}

int				Player_ia::checkDownLeftAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter)
{
	counter = 0;
	x = to_ev.x - 1;
	y = to_ev.y + 1;

	while (x >= 0 && y < 20 && g->c[y][x] == to_ev.player)
	{
		++counter;
		--x;
		++y;
	}
	switch (counter)
	{
	case 0:
		return 0;
		break;
	case 1:
		return COMPLETE_LINE_1;
		break;
	case 2:
		return COMPLETE_LINE_2;
		break;
	case 3:
		return COMPLETE_LINE_3;
		break;
	case 4:
		return COMPLETE_LINE_4;
		break;
	case 5:
		return WIN;
		break;
	}
}

int				Player_ia::checkDownRightAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter)
{
	counter = 0;
	x = to_ev.x + 1;
	y = to_ev.y + 1;

	while (x < 20 && y < 20 && g->c[y][x] == to_ev.player)
	{
		++counter;
		++x;
		++y;
	}
	switch (counter)
	{
	case 0:
		return 0;
		break;
	case 1:
		return COMPLETE_LINE_1;
		break;
	case 2:
		return COMPLETE_LINE_2;
		break;
	case 3:
		return COMPLETE_LINE_3;
		break;
	case 4:
		return COMPLETE_LINE_4;
		break;
	case 5:
		return WIN;
		break;
	}
}

int				Player_ia::checkAlign(t_node &to_ev, Gomoku *g)
{
	int			ret = 0;
	int			x;
	int			y;
	int			counter;

	for (int i = 0; i < 8; ++i)
		ret += (this->*_alignPtr[i])(to_ev, g, x, y, counter);
	return ret;
}

int				Player_ia::evaluateHeuristic(t_node &to_ev, Gomoku *g)
{
	int			ret;

	ret += checkAlign(to_ev, g);
	ret += checkBlock(to_ev, g);

	return ret;
}

void			Player_ia::action(Gomoku *g, char *coord)
{
	//TODO
}
