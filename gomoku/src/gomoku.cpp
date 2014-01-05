#include "../include/gomoku.h"
#include "../include/players.h"

Gomoku::Gomoku(int mode)
{
	int i;

	this->can_win_type = CASE_EMPTY;
	this->state = false;
	if (mode == 1)
	{
		this->ia1_activated = false;
		this->ia2_activated = false;
	}
	else if (mode == 2)
	{
		this->ia1_activated = false;
		this->ia2_activated = true;
	}
	else
	{
		this->ia1_activated = true;
		this->ia2_activated = true;
	}

	for (i = 0; i < 19; i++)
	{
		memset(this->c[i], CASE_EMPTY, 19);
	}
}

void Gomoku::print_img(int x, int y, const char *str) 
{
	SDL_Surface *s;
	SDL_Rect pos;

	pos.x = x;
	pos.y = y;
	s = IMG_Load(str);
	if (!s)
	{
		std::cerr << "img introuvable" << std::endl;
		exit(0);
	}
	SDL_BlitSurface(s, NULL, this->screen, &pos);
	SDL_FreeSurface(s);
}

void Gomoku::refresh()
{
	if (SDL_Flip(this->screen) == -1)
	{
		std::cerr << "refresh de merde" << std::endl;
		exit(0);
	}
}

void Gomoku::load_grille()
{
	int			i;
	int			j;
	SDL_Surface	*s;
	SDL_Rect	pos;

	pos.x = 0;
	pos.y = 0;

	for (i = 0; i < 19; i++)
	{
		for (j = 0; j < 19; j++)
		{
			switch (this->c[i][j])
			{
			case CASE_EMPTY :
				if (i == 0 && j == 0)
					s = IMG_Load("img/coin_haut_gauche.png");
				else if ((i != 0 && i != 19 - 1) && j == 0)
					s = IMG_Load("img/gauche.png");
				else if (i == 19 - 1 && j == 0)
					s = IMG_Load("img/coin_bas_gauche.png");
				else if (i == 0 && j != 0 && j != 19 - 1)
					s = IMG_Load("img/haut.png");
				else if (i == 19 - 1 && j != 0 && j != 19 - 1)
					s = IMG_Load("img/bas.png");
				else if (i == 19 - 1 && j == 19 - 1)
					s = IMG_Load("img/coin_bas_droit.png");
				else if (i != 0 && i != 19 - 1 && j == 19 - 1)
					s = IMG_Load("img/droit.png");
				else if (i == 0 && j == 19 - 1)
					s = IMG_Load("img/coin_haut_droit.png");
				else
					s = IMG_Load("img/centre.png");
				break;

			case CASE_J1 :
				s = IMG_Load("img/j1.png");
				break;

			case CASE_J2 :
				s = IMG_Load("img/j2.png");
				break;
			}

			SDL_BlitSurface(s, NULL, this->screen, &pos);
			SDL_FreeSurface(s);
			pos.x += 40;
		}
		pos.x = 0;
		pos.y += 40;
	}

	SDL_Rect r;
	r.x = 760;
	r.y = 0;
	r.w = 150;
	r.h = 760;
	SDL_FillRect(this->screen, &r, SDL_MapRGB(this->screen->format, 255, 255, 255));

	this->refresh();
}

bool Gomoku::trois_libre(char type, char *matrix, int start_x, int start_y, std::stack<Gomoku_pos> *s)
{
	int i, x, y, count;
	char current, last_type;
	Gomoku_pos p;

	count = 0;
	last_type = CASE_EMPTY;
	x = start_x;
	y = start_y;
	for (i = 0; i < 9; i++)
	{
		current = (x < 0 || x > 19 || y < 0 || y > 19) ? CASE_OUTSIDE : this->c[y][x];

		if (i == 4)
			current = type;

		if ((i > 0 && last_type == CASE_EMPTY && current == type) || (count > 0 && current == type))
		{
			count++;
			p.x = x;
			p.y = y;
			s->push(p);
		}

		if ((current != CASE_EMPTY && current != type) || (current == CASE_EMPTY && last_type == CASE_EMPTY))
		{
			while (s->size() > 0)
				s->pop();
			count = 0;
		}

		if (count == 3 && current == CASE_EMPTY)
			return (true);

		last_type = current;
		x += matrix[0];
		y += matrix[1];
	}
	return (false);
}

bool Gomoku::check_case(int case_x, int case_y, char type)
{
	if (this->c[case_y][case_x] != CASE_EMPTY)
		return (false);

	int m, save_m, x, y, nb_align = 0;
	std::stack<Gomoku_pos> s, save_s;
	char matrix[4][2] = {
		{1, 1},  // Diagonale haut gauche -  bas droite
		{0, 1},  // Ligne verticale
		{-1, 1}, // Diagonale haut droite - bas  gauche
		{1, 0}   // Ligne horizontale
	};

	for (m = 0; m < 4; m++)
	{
		x = case_x - (4 * matrix[m][0]);
		y = case_y - (4 * matrix[m][1]);

		if (this->trois_libre(type, matrix[m], x, y, &s))
		{
			save_m = m;
			save_s = s;
			nb_align++;
		}

		if (nb_align == 2)
			return (false);
	}

	if (nb_align == 1)
	{
		while (save_s.size() > 0)
		{
			if (!(save_s.top().x == case_x && save_s.top().y == case_y))
			{
				for (m = 0; m < 4; m++)
				{
					if (m == save_m)
						continue;

					x = save_s.top().x - (4 * matrix[m][0]);
					y = save_s.top().y - (4 * matrix[m][1]);
					if (this->trois_libre(type, matrix[m], x, y, &s))
						return (false);
				}
			}
			save_s.pop();
		}
	}
	return (true);
}

int Gomoku::check_paire(int case_x, int case_y, char type)
{
	Gomoku_pos save_p, p, *add;
	int i, x, y, total;
	char second_type;
	char matrix[8][2] = {
		{-1, -1},
		{-1, 0},
		{-1, 1},
		{0, -1},
		{0, 1},
		{1, -1},
		{1, 0},
		{1, 1}
	};

	add = new Gomoku_pos;
	second_type = (type == CASE_J1) ? CASE_J2 : CASE_J1;
	for (i = 0, total = 0; i < 8; i++)
	{
		x = matrix[i][0];
		y = matrix[i][1];
		if (this->c[case_y + y][case_x + x] == second_type
			&& this->c[case_y + (2 * y)][case_x + (2 * x)] == second_type
			&& this->c[case_y + (3 * y)][case_x + (3 * x)] == type
			&& (case_x + 3*x) < 19 && (case_y + 3*y) < 19)
		{
			this->c[case_y + y][case_x + x] = CASE_EMPTY;
			this->c[case_y + (2 * y)][case_x + (2 * x)] = CASE_EMPTY;
			total += 2;

			save_p = this->p.top();
			p.x = save_p.x;
			p.y = save_p.y;
			p.paires = save_p.paires;
			p.is_paire = true;

			add->x = case_x + x;
			add->y = case_y + y;
			p.paires.push(add);

			add->x = case_x + (2 * x);
			add->y = case_y + (2 * y);
			p.paires.push(add);
			this->p.pop();
			this->p.push(p);
		}
	}
	return (total);
}

bool Gomoku::alignement_victorieux(int start_x, int start_y, char *matrix, char type, std::stack<Gomoku_pos> *s)
{
	int i, x, y, total;
	Gomoku_pos p;

	x = start_x;
	y = start_y;
	total = 0;
	for (i = 0; i < 9; i++)
	{
		if (this->c[y][x] == type)
		{
			total++;
			p.x = x;
			p.y = y;
			s->push(p);
		}
		else
		{
			total = 0;
			while (s->size() > 0)
				s->pop();
		}

		if (total == 5)
			return (true);

		x += matrix[0];
		y += matrix[1];
	}
	return (false);
}

void Gomoku::check_winner(int case_x, int case_y, char type)
{
	int m, x, y;
	std::stack<Gomoku_pos> s;
	char matrix[4][2] = {
		{1, 1},  // Diagonale haut gauche -  bas droite
		{0, 1},  // Ligne verticale
		{-1, 1}, // Diagonale haut droite - bas  gauche
		{1, 0}   // Ligne horizontale
	};
	int m2, x2, y2, count;
	char matrix2[8][2] = {
		{0, -1},
		{1, -1},
		{1, 0},
		{1, 1},
		{0, 1},
		{-1, 1},
		{-1, 0},
		{-1, -1},
	};

	for (m = 0; m < 4; m++)
	{
		x = case_x - (4 * matrix[m][0]);
		y = case_y - (4 * matrix[m][1]);

		if (this->alignement_victorieux(x, y, matrix[m], type, &s))
		{
			std::stack<Gomoku_pos> cases = s;
			while (cases.size() > 0)
				cases.pop();

			while (s.size() > 0)
			{
				x = s.top().x;
				y = s.top().y;

				for (m2 = 0; m2 < 8; m2++)
				{
					count = 0;

					if ((matrix2[m2][0] == matrix[m][0] && matrix2[m2][1] == matrix[m][1]) || (matrix2[m2][0] == -matrix[m][0] && matrix2[m2][1] == -matrix[m][1]))
						continue;

					x2 = x - matrix2[m2][0];
					y2 = y - matrix2[m2][1];
					if (this->c[y2][x2] == CASE_EMPTY)
						count++;

					x2 = x + matrix2[m2][0];
					y2 = y + matrix2[m2][1];
					if (this->c[y2][x2] == type)
						count++;

					x2 = x + (2 * matrix2[m2][0]);
					y2 = y + (2 * matrix2[m2][1]);
					if (this->c[y2][x2] != CASE_EMPTY && this->c[y2][x2] != type)
						count++;

					if (count == 3)
					{
						this->can_win_type = type;
						this->can_win_x = x - matrix2[m2][0];
						this->can_win_y = y - matrix2[m2][1];
						return ;
					}
				}
				s.pop();
			}
			this->winner = type;
			this->is_finished();
			break;
		}
	}
}

void Gomoku::set_case(int x, int y, char type)
{
	Gomoku_pos p;

	p.x = x;
	p.y = y;
	p.is_paire = false;
	this->p.push(p);

	this->c[y][x] = type;
}

bool Gomoku::game_finished()
{
	if (this->state)
	{
		if (this->winner == CASE_J1)
			std::cout << "j1 gagne" << std::endl;
		else
			std::cout << "j2 gagne" << std::endl;
		this->refresh();
	}
	return (this->state);
}

void Gomoku::is_finished()
{
	this->state = true;
}

Gomoku::~Gomoku()
{

}


