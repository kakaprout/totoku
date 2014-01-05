#include "../include/player.h"

Player::Player(char case_type, bool is_ia)
{
	this->case_type = case_type;
	this->paires = 0;
	this->y = (this->case_type == CASE_J1) ? 30 : 60;
	this->name = (this->case_type == CASE_J1) ? "Joueur 1" : "Joueur 2";
	this->is_ia = is_ia;

	this->ia_obj = new Player_ia(case_type);
}

void Player::action(Gomoku *g, Player *other)
{
	SDL_Event event;
	bool done = false;
	int x, y;
	char type;

	while (!done)
	{
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				exit(0);
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					if (!this->is_ia && event.button.x < 760)
					{
						x = event.button.x / 40;
						y = event.button.y / 40;
						type = this->get_case();
						if (this->play_case(g, other, x, y, type))
							done = true;
						break;
					}
				}
			}
		}

		if (this->is_ia)
			done = true;
	}

	if (this->is_ia)
	{
		char ia_coord[3], stop;
		stop = 0;
		while (stop++ < 10)
		{
			this->ia_obj->action(g, ia_coord);
			if (this->play_case(g, other, (int) ia_coord[0], (int) ia_coord[1], this->case_type))
				return;
		}
		std::cerr << "error IA : no position" << std::endl;
		exit(0);
	}
}

bool Player::play_case(Gomoku *g, Player *other, int x, int y, char type)
{
	if (g->check_case(x, y, type))
	{
		if (g->can_win_type != CASE_EMPTY)
		{
			if (x == g->can_win_x && y == g->can_win_y)
			{
				g->can_win_type = CASE_EMPTY;
			}
			else
			{
				g->winner = other->case_type;
				g->is_finished();
				return (true);
			}
		}

		g->set_case(x, y, type);

		this->paires += g->check_paire(x, y, type);
		if (this->paires >= 10)
		{
			g->winner = type;
			g->is_finished();
			return (true);
		}
		g->check_winner(x, y, type);
		g->load_grille();
		return (true);
	}

	g->load_grille();
	return (false);
}

void Player::annuler(Gomoku *g, Player *other)
{
	Gomoku_pos p;
	int i, size;

	if (g->p.size() > 0)
	{
		p = g->p.top();
		g->c[p.y][p.x] = CASE_EMPTY;
		if (p.is_paire)
		{
			size = p.paires.size();
			for (i = 0; i < size; i++)
			{
				g->c[p.paires.top()->y][p.paires.top()->x] = this->case_type;
				other->paires--;
				p.paires.pop();
			}
		}
		g->load_grille();
		g->p.pop();
	}
}

char Player::get_case()
{
	return (this->case_type);
}
