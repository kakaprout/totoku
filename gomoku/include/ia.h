#pragma once

#include <list>
#include <array>
#include "gomoku.h"

#define INC(x, z, y) (x + z > y ? y : x + z)
#define DEC(x, z) (x - z < 0 ? 0 : x - z)


struct					t_node
{
	t_node				*parent;
	char				x;
	char				y;
	char				map[19][19];
	char				player;
	int					weight;
	std::list<t_node *>	next;
};

class Player_ia
{
public:
	typedef		int	(Player_ia::*alignPtr)(t_node &to_ev, Gomoku *, int, int ,int);
		typedef		int	(Player_ia::*blockPtr)(t_node &to_ev, Gomoku *, int, int ,int);
	int			_eaten;
	enum					e_action
	{
		ADD = 1,
		CAPTURE = 80,
		BLOCK_1 = 2,
		BLOCK_2 = 5,
		BLOCK_3 = 35,
		BLOCK_4 = 90,
		BLOCK_WIN = 1000,
		COMPLETE_LINE_1 = 3,
		COMPLETE_LINE_2 = 15,
		COMPLETE_LINE_3 = 40,
		COMPLETE_LINE_4 = 80,
		WIN = 5000
	};

private:
		t_node					*_nodePool;
		int							_currentElem;
		char numPlayer;
		t_node		_start;
		int			_buff;
		t_node		*tmp;
		std::list<t_node *>			_goodMoove;
		alignPtr		*_alignPtr;
		blockPtr		*_blockPtr;

		inline int		checkBlock(t_node&, Gomoku*);
		inline int		checkDownBlock(t_node &to_ev, Gomoku *g, int x, int y, int counter);
		inline int		checkTopBlock(t_node &to_ev, Gomoku *g, int x, int y, int counter);
		inline int		checkRightBlock(t_node &to_ev, Gomoku *g, int x, int y, int counter);
		inline int		checkLeftBlock(t_node &to_ev, Gomoku *g, int x, int y, int counter);
		inline int		checkTopLeftBlock(t_node &to_ev, Gomoku *g, int x, int y, int counter);
		inline int		checkTopRightBlock(t_node &to_ev, Gomoku *g, int x, int y, int counter);
		inline int		checkDownLeftBlock(t_node &to_ev, Gomoku *g, int x, int y, int counter);
	    inline int		checkDownRightBlock(t_node &to_ev, Gomoku *g, int x, int y, int counter);
		inline int		checkCapture(t_node &to_ev, Gomoku *g, int x, int y, int counter);

		inline int		checkUpAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter);
		inline int		checkDownAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter);
		inline int		checkLeftAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter);
		inline int		checkRightAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter);
		inline int		checkUpLeftAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter);
		inline int		checkUpRightAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter);
		inline int		checkDownLeftAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter);
		inline int		checkDownRightAlign(t_node &to_ev, Gomoku*g, int x, int y, int counter);

		inline int		checkAlign(t_node&, Gomoku*);

		inline bool			checkIfPionInPerimetre(int x, int y, int rayon, Gomoku *g);
		inline void			buildTree(Gomoku *g, int profondeur);
		inline void			buildLevel(Gomoku *g, int profondeur, char player, t_node *daddy);
		inline t_node*		getNode();
		void				copyMap(char **src, char **dest);
		int					evaluateHeuristic(t_node &to_evaluate, Gomoku*);
public:
       Player_ia(char);
       ~Player_ia();
       void action(Gomoku *, char *);
};
