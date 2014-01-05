#include "../include/headers.h"
#include "../include/gomoku.h"
#include "../include/players.h"

int main(int ac, char **av)
{
	int	mode;

	std::cout << "Game mode :" << std::endl << "(1) 2 players" << std::endl << "(2) 1 player vs 1 IA" << std::endl << "(3) 2 IAs" << std::endl;
	std::cin >> mode;
	if (mode != 1 && mode != 2 && mode != 3)
	{
		std::cerr << "Unknown mode" << std::endl;
		return (1);
	}
	start(mode);
	return (0);
}

void start(int mode)
{
	Players		*players = new Players;
	Player		*cur_player;
	Gomoku		*g = new Gomoku(mode);
	SDL_Event	event;

	if(SDL_Init(SDL_INIT_VIDEO)!= 0)
	{
		std::cerr << SDL_GetError() << std::endl;
		exit(1);
	}

	SDL_WM_SetCaption("TOTOKU DE LA MAURE", NULL);

	g->screen = SDL_SetVideoMode(760, 760, 32, SDL_DOUBLEBUF | SDL_HWSURFACE);
	if (g->screen == NULL)
		g->is_finished();

	g->load_grille();

	while (42)
	{
		while (!g->game_finished())
		{
			cur_player = players->get_current(g);
			g->refresh();
			cur_player->action(g, (cur_player->case_type == CASE_J1) ? players->p2 : players->p1);
		}

		g->refresh();

		while (42)
		{
			while(SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					exit(0);
			}
		}
	}

	delete cur_player;
	SDL_Quit();
}
