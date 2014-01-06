#include "../include/ia.h"

Player_ia::Player_ia(char player)
{
	this->numPlayer = player;
	this->_nodePool = new t_node[500000];
	this->_alignPtr = new alignPtr[8];
	this->_alignPtr[0] = &Player_ia::checkUpAlign;
	this->_alignPtr[1] = &Player_ia::checkDownAlign;
	this->_alignPtr[2] = &Player_ia::checkRightAlign;
	this->_alignPtr[3] = &Player_ia::checkLeftAlign;
	this->_alignPtr[4] = &Player_ia::checkUpRightAlign;
	this->_alignPtr[5] = &Player_ia::checkUpLeftAlign;
	this->_alignPtr[6] = &Player_ia::checkDownLeftAlign;
	this->_alignPtr[7] = &Player_ia::checkDownRightAlign;
	this->_blockPtr = new blockPtr[8];
	this->_blockPtr[0] = &Player_ia::checkTopBlock;
	this->_blockPtr[1] = &Player_ia::checkDownBlock;
	this->_blockPtr[2] = &Player_ia::checkRightBlock;
	this->_blockPtr[3] = &Player_ia::checkLeftBlock;
	this->_blockPtr[4] = &Player_ia::checkTopLeftBlock;
	this->_blockPtr[5] = &Player_ia::checkTopRightBlock;
	this->_blockPtr[6] = &Player_ia::checkDownLeftBlock;
	this->_blockPtr[7] = &Player_ia::checkDownRightBlock;
}

Player_ia::~Player_ia()
{
}

t_node			*Player_ia::getNode()
{
	if (this->_nodePool[this->_currentElem].next.size())
		this->_nodePool[this->_currentElem].next.clear();
//	std::cout << this->_currentElem << std::endl;
	return (&this->_nodePool[this->_currentElem++]);
}

int				Player_ia::checkDownRightBlock(t_node &to_ev, Gomoku *g, int x, int y, int counter)
{
	bool check = false;
	counter = 0;
	x = to_ev.x + 1;
	y = to_ev.y + 1;

	while (y < 20 && x < 20 && g->c[y][x] != to_ev.player && g->c[y][x] > 0)
	{
		++counter;
		++x;
		++y;
	}
	if (x < 20 && y < 20 && g->c[y][x] == to_ev.player)
		check = true;
	if (counter == 2 && g->c[y][x] == to_ev.player)
	{
		this->_eaten += 2;
		return CAPTURE;
	}
	switch (counter)
	{
	case 0:
		return 0;
		break;
	case 1:
		if (check == true)
			return (BLOCK_1 * 2);
		return BLOCK_1;
		break;
	case 2:
		if (check == true)
			return (BLOCK_2 * 2);
		return BLOCK_2;
		break;
	case 3:
		if (check == true)
			return (BLOCK_3 * 2);
		return BLOCK_3;
		break;
	case 4:
		if (check == true)
			return (BLOCK_WIN);
		return BLOCK_4;
		break;
	case 5:
		return BLOCK_WIN;
	}
	return 0;
}

int				Player_ia::checkDownLeftBlock(t_node &to_ev, Gomoku *g, int x, int y, int counter)
{
	bool check = false;
	counter = 0;
	x = to_ev.x - 1;
	y = to_ev.y + 1;

	while (y < 20 && x >= 0 && g->c[y][x] != to_ev.player && g->c[y][x] > 0)
	{
		++counter;
		--x;
		++y;
	}
	if (x >= 0 && y < 20 && g->c[y][x] == to_ev.player)
		check = true;
	if (counter == 2 && g->c[y][x] == to_ev.player)
	{
		this->_eaten += 2;
		return CAPTURE;
	}
	switch (counter)
	{
	case 0:
		return 0;
		break;
	case 1:
		if (check == true)
			return (BLOCK_1 * 2);
		return BLOCK_1;
		break;
	case 2:
		if (check == true)
			return (BLOCK_2 * 2);
		return BLOCK_2;
		break;
	case 3:
		if (check == true)
			return (BLOCK_3 * 2);
		return BLOCK_3;
		break;
	case 4:
		if (check == true)
			return (BLOCK_WIN);
		return BLOCK_4;
		break;
	case 5:
		return BLOCK_WIN;
	}
	return 0;
}

int				Player_ia::checkTopRightBlock(t_node &to_ev, Gomoku *g, int x, int y, int counter)
{
	bool check = false;
	counter = 0;
	x = to_ev.x + 1;
	y = to_ev.y - 1;

	while (y >= 0 && x < 20 && g->c[y][x] != to_ev.player && g->c[y][x] > 0)
	{
		++counter;
		++x;
		--y;
	}
	if (x < 20 && y >= 0 && g->c[y][x] == to_ev.player)
		check = true;
	if (counter == 2 && g->c[y][x] == to_ev.player)
	{
		this->_eaten += 2;
		return CAPTURE;
	}
	switch (counter)
	{
	case 0:
		return 0;
		break;
	case 1:
		if (check == true)
			return (BLOCK_1 * 2);
		return BLOCK_1;
		break;
	case 2:
		if (check == true)
			return (BLOCK_2 * 2);
		return BLOCK_2;
		break;
	case 3:
		if (check == true)
			return (BLOCK_3 * 2);
		return BLOCK_3;
		break;
	case 4:
		if (check == true)
			return (BLOCK_WIN);
		return BLOCK_4;
		break;
	case 5:
		return BLOCK_WIN;
	}
	return 0;
}

int				Player_ia::checkTopLeftBlock(t_node &to_ev, Gomoku *g, int x, int y, int counter)
{
	bool check = false;
	counter = 0;
	x = to_ev.x - 1;
	y = to_ev.y - 1;

	while (y >= 0 && x >= 0 && g->c[y][x] != to_ev.player && g->c[y][x] > 0)
	{
		++counter;
		--x;
		--y;
	}
	if (x >= 0 && y >= 0 && g->c[y][x] == to_ev.player)
		check = true;
	if (counter == 2 && g->c[y][x] == to_ev.player)
	{
		this->_eaten += 2;
		return CAPTURE;
	}
	switch (counter)
	{
	case 0:
		return 0;
		break;
	case 1:
		if (check == true)
			return (BLOCK_1 * 2);
		return BLOCK_1;
		break;
	case 2:
		if (check == true)
			return (BLOCK_2 * 2);
		return BLOCK_2;
		break;
	case 3:
		if (check == true)
			return (BLOCK_3 * 2);
		return BLOCK_3;
		break;
	case 4:
		if (check == true)
			return (BLOCK_WIN);
		return BLOCK_4;
		break;
	case 5:
		return BLOCK_WIN;
	}
	return 0;
}

int				Player_ia::checkLeftBlock(t_node &to_ev, Gomoku *g, int x, int y, int counter)
{
	bool check = false;
	counter = 0;
	x = to_ev.x - 1;

	while (x >= 0 && g->c[to_ev.y][x] != to_ev.player && g->c[to_ev.y][x] > 0)
	{
		++counter;
		--x;
	}
	if (x >= 0 && g->c[to_ev.y][x] == to_ev.player)
		check = true;
	if (counter == 2 && g->c[to_ev.y][x] == to_ev.player)
	{
			this->_eaten += 2;
		return CAPTURE;
	}
	switch (counter)
	{
	case 0:
		return 0;
		break;
	case 1:
		if (check == true)
			return (BLOCK_1 * 2);
		return BLOCK_1;
		break;
	case 2:
		if (check == true)
			return (BLOCK_2 * 2);
		return BLOCK_2;
		break;
	case 3:
		if (check == true)
			return (BLOCK_3 * 2);
		return BLOCK_3;
		break;
	case 4:
		if (check == true)
			return (BLOCK_WIN);
		return BLOCK_4;
		break;
	case 5:
		return BLOCK_WIN;
	}
	return 0;
}

int				Player_ia::checkRightBlock(t_node &to_ev, Gomoku *g, int x, int y, int counter)
{
	bool check = false;
	counter = 0;
	x = to_ev.x + 1;

	while (x < 20 && g->c[to_ev.y][x] != to_ev.player && g->c[to_ev.y][x] > 0)
	{
		++counter;
		++x;
	}
	if (x < 20 && g->c[to_ev.y][x] == to_ev.player)
		check = true;
	if (counter == 2 && g->c[to_ev.y][x] == to_ev.player)
	{
		this->_eaten += 2;
		return CAPTURE;
	}
	switch (counter)
	{
	case 0:
		return 0;
		break;
	case 1:
		if (check == true)
			return (BLOCK_1 * 2);
		return BLOCK_1;
		break;
	case 2:
		if (check == true)
			return (BLOCK_2 * 2);
		return BLOCK_2;
		break;
	case 3:
		if (check == true)
			return (BLOCK_3 * 2);
		return BLOCK_3;
		break;
	case 4:
		if (check == true)
			return (BLOCK_WIN);
		return BLOCK_4;
		break;
	case 5:
		return BLOCK_WIN;
	}
	return 0;
}

int				Player_ia::checkTopBlock(t_node &to_ev, Gomoku *g, int x, int y, int counter)
{
	bool check = false;
	counter = 0;
	y = to_ev.y - 1;

	while (y >= 0 && g->c[y][to_ev.x] != to_ev.player &&  g->c[y][to_ev.x] > 0)
	{
		++counter;
		--y;
	}
	if (y >= 0 && g->c[y][to_ev.x] == to_ev.player)
		check = true;
	if (counter == 2 && g->c[y][to_ev.x] == to_ev.player)
	{
			this->_eaten += 2;
		return CAPTURE;
	}
	switch (counter)
	{
	case 0:
		return 0;
		break;
	case 1:
		if (check == true)
			return (BLOCK_1 * 2);
		return BLOCK_1;
		break;
	case 2:
		if (check == true)
			return (BLOCK_2 * 2);
		return BLOCK_2;
		break;
	case 3:
		if (check == true)
			return (BLOCK_3 * 2);
		return BLOCK_3;
		break;
	case 4:
		if (check == true)
			return (BLOCK_WIN);
		return BLOCK_4;
		break;
	case 5:
		return BLOCK_WIN;
	}
	return 0;
}

int				Player_ia::checkDownBlock(t_node &to_ev, Gomoku *g, int x, int y, int counter)
{
	bool check = false;
	counter = 0;
	y = to_ev.y + 1;

	while (y < 20 && g->c[y][to_ev.x] != to_ev.player &&  g->c[y][to_ev.x] > 0)
	{
		++counter;
		++y;
	}
	if (y < 20 && g->c[y][to_ev.x] == to_ev.player)
		check = true;
	if (counter == 2 && g->c[y][to_ev.x] == to_ev.player)
	{
			this->_eaten += 2;
		return CAPTURE;
	}
	switch (counter)
	{
	case 0:
		return 0;
		break;
	case 1:
		if (check == true)
			return (BLOCK_1 * 2);
		return BLOCK_1;
		break;
	case 2:
		if (check == true)
			return (BLOCK_2 * 2);
		return BLOCK_2;
		break;
	case 3:
		if (check == true)
			return (BLOCK_3 * 2);
		return BLOCK_3;
		break;
	case 4:
		if (check == true)
			return (BLOCK_WIN);
		return BLOCK_4;
		break;
	case 5:
		return BLOCK_WIN;
	}
	return 0;
}

int				Player_ia::checkDownAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter)
{
	counter = 0;
	y = to_ev.y + 1;

	while (y < 19 && g->c[y][to_ev.x] == to_ev.player)
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
	return 0;
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
	return 0;
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
	return (0);
}

int				Player_ia::checkRightAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter)
{
	counter = 0;
	x = to_ev.x + 1;

	while (x < 19 && g->c[to_ev.y][x] == to_ev.player)
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
	return 0;
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
	return 0;
}

int				Player_ia::checkUpRightAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter)
{
	counter = 0;
	x = to_ev.x + 1;
	y = to_ev.y - 1;

	while (x < 19 && y >= 0 && g->c[y][x] == to_ev.player)
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
	return 0;
}

int				Player_ia::checkDownLeftAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter)
{
	counter = 0;
	x = to_ev.x - 1;
	y = to_ev.y + 1;

	while (x >= 0 && y < 19 && g->c[y][x] == to_ev.player)
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
	return 0;
}

int				Player_ia::checkDownRightAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter)
{
	counter = 0;
	x = to_ev.x + 1;
	y = to_ev.y + 1;

	while (x < 19 && y < 19 && g->c[y][x] == to_ev.player)
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
	return 0;
}

int				Player_ia::checkAlign(t_node &to_ev, Gomoku *g)
{
	int			ret = 0;
	int			x = 0;
	int			y = 0;
	int			counter = 0;

	for (int i = 0; i < 8; ++i)
	{
		ret += (this->*_alignPtr[i])(to_ev, g, x, y, counter);
	}
	return ret;
}

int				Player_ia::checkBlock(t_node &to_ev, Gomoku *g)
{
	int			ret = 0;
	int			x = 0;
	int			y = 0;
	int			counter = 0;

	for (int i = 0; i < 8; ++i)
	{
		ret += (this->*_blockPtr[i])(to_ev, g, x, y, counter);
	}
	return ret;
}

int				Player_ia::evaluateHeuristic(t_node &to_ev, Gomoku *g)
{
	int			ret = 0;

	ret += checkAlign(to_ev, g);
	ret += checkBlock(to_ev, g);
	return ret;
}

bool			Player_ia::checkIfPionInPerimetre(int x, int y, int rayon, Gomoku *g)
{
	int x_min = DEC(x, rayon);
	int x_max = INC(x, rayon, 19);
	int y_min = DEC(y, rayon);
	int y_max = INC(y, rayon, 19);

	for (; y_min <= y_max; ++y_min)
		for (x = x_min; x <= x_max; ++x)
			if (g->c[y_min][x])
				return true;
	return false;
}

void			Player_ia::buildLevel(Gomoku *g, int profondeur, char player, t_node *daddy)
{
//	std::cout << "coucou" << std::endl;
	for (int y = 0; y < 19; ++y)
	{
		for (int x = 0; x < 19; ++x)
		{
			if (/*checkIfPionInPerimetre(x, y, 1, g) &&*/ !g->c[y][x] /*g->check_case(x, y, player)*/)
			{
				this->_start.player = player;
				this->_start.x = x;
				this->_start.y = y;
				if ((_buff = this->evaluateHeuristic(this->_start, g)) > 0)
				{
					tmp = this->getNode();
					if (player != this->numPlayer)
						this->_buff *= -1;
					tmp->weight = _buff + daddy->weight;
					tmp->parent = daddy;
					tmp->y = y;
					tmp->x = x;
					copyMap((char **)daddy->map, (char **)tmp->map);
					tmp->map[y][x] = player;
					tmp->player = player;
					daddy->next.push_back(tmp);
					if (tmp->weight > 0)
						this->_goodMoove.push_back(tmp);
				}
			}
		}
	}
	for (std::list<t_node *>::iterator it = daddy->next.begin(); it != daddy->next.end(); ++it)
	{	
		if ((profondeur - 1))
			this->buildLevel(g, profondeur - 1, player == 1 ? 2 : 1, (*it));
	}
}

void			Player_ia::buildTree(Gomoku *g, int profondeur)
{
	buildLevel(g, profondeur, this->numPlayer, &this->_start);
}

void			Player_ia::copyMap(char **src, char **dest)
{
/*	for (int y = 0; y < 19; ++y)
		for (int x = 0; x < 19; ++x)
			dest[y][x] = src[y][x];*/
}

void			Player_ia::action(Gomoku *g, char *coord)
{
	_currentElem = 0;
	copyMap((char **)g->c, (char **)this->_start.map);
	this->_start.weight = 0;
	buildTree(g, 2);
	if (this->_start.next.size())
	{
		this->tmp = *(this->_goodMoove.begin());
		for (std::list<t_node *>::iterator it = this->_goodMoove.begin(); it != this->_goodMoove.end(); ++it)
		{
			if ((*it)->weight > this->tmp->weight && g->check_case((*it)->x, (*it)->y, this->numPlayer))
				this->tmp = (*it);
		}
		coord[0] = this->tmp->x;
		coord[1] = this->tmp->y;
	}
	else
	{
		for (int y = 0; y < 19; ++y)
			for (int x = 0; x < 19; ++x)
			{
				if (g->c[y][x + 1])
				{
					coord[0] = x;
					coord[1] = y;
					x = 19;
					y = 19;
				}
			}
	}
	std::cout << this->_currentElem << std::endl;
	this->_start.next.clear();
	this->_goodMoove.clear();
}	
