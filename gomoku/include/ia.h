#pragma once

#include <list>
#include "gomoku.h"

#define INC(x, y) (x == y > ? 0 : x + 1)
#define DEC(x, y) (x == 0 ? y : x - 1)


struct					t_node
{
	t_node				*parent;
	char				x;
	char				y;
	char				player;
	int					weight;
	std::list<t_node>	next;
};

class Player_ia
{
public:
	typedef		int	(Player_ia::*alignPtr)(t_node &to_ev, Gomoku *, int, int ,int);

	enum					e_action
	{
		ADD = 1,
		CAPTURE = 10,
		BLOCK_1 = 2,
		BLOCK_2 = 4,
		BLOCK_3 = 8,
		BLOCK_4 = 16,
		BLOCK_WIN = 1000,
		COMPLETE_LINE_1 = 3,
		COMPLETE_LINE_2 = 5,
		COMPLETE_LINE_3 = 9,
		COMPLETE_LINE_4 = 17,
		WIN = 5000
	};

private:
		char numPlayer;
		alignPtr		*_alignPtr;

		inline int		checkUpAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter);
		inline int		checkDownAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter);
		inline int		checkLeftAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter);
		inline int		checkRightAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter);
		inline int		checkUpLeftAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter);
		inline int		checkUpRightAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter);
		inline int		checkDownLeftAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter);
		inline int		checkDownRightAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter);

		inline int		checkAlign(t_node&, Gomoku*);
		int		evaluateHeuristic(t_node &to_evaluate, Gomoku*);
public:
       Player_ia(char);
       ~Player_ia();
       void action(Gomoku *, char *);
};
