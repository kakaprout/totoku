#pragma once

#include "headers.h"
#include "gomoku_pos.h"

class Gomoku
{
private:
	int stop;
	bool state;

public:
	char c[19][19];
	SDL_Surface *screen;
	bool ia1_activated;
	bool ia2_activated;
	char winner;
	std::stack<Gomoku_pos> p;
	char can_win_type;
	int can_win_x;
	int can_win_y;

	Gomoku(int);
	~Gomoku();
	void	print_img(int x, int y, const char *str);
	void	load_grille();
	bool	check_case(int case_x, int case_y, char type);
	int		check_paire(int case_x, int case_y, char type);
	void	check_winner(int case_x, int case_y, char type);
	void	set_case(int x, int y, char type);
	bool	game_finished();  
	void	is_finished();
	bool	trois_libre(char, char *, int, int, std::stack<Gomoku_pos> *);
	void	refresh();
	bool	alignement_victorieux(int, int, char *, char, std::stack<Gomoku_pos> *);
};
