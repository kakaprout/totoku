#include "../include/headers.h"
#include "../include/gomoku.h"
#include "../include/players.h"

int main(int ac, char **av)
{
  start();
  return (0);
}

void start()
{
	Players *gamers = new Players;
	Player *current;
	Gomoku *g = new Gomoku;
	SDL_Event event;

	if(SDL_Init(SDL_INIT_VIDEO)!= 0)
	{
		std::cerr << SDL_GetError() << "\n";
		exit(1);
	}
  
	if(TTF_Init() < 0 )
	{
		std::cerr << TTF_GetError() << "\n";
		exit(1);
	}
  
	SDL_WM_SetCaption("TOTOKU DE LA MAURE", NULL);
  
	g->screen = SDL_SetVideoMode(GOMOKU_SIZE * HOR + RIGHT_SPACE, TOP_SPACE + GOMOKU_SIZE * VER, 32, SDL_DOUBLEBUF | SDL_HWSURFACE);
	if (g->screen == NULL)
		g->is_finished();

	g->load_header();

	g->load_tab(false);

	while (42)
	{
		while (!g->game_finished())
		{
			current = gamers->get_current(g);
			current->round_img(g);
			if (g->check_help())
			{
				g->calcul_help(current->case_type);
				g->load_tab(false);
			}
			g->refresh();
			current->action(g, (current->case_type == CASE_J1) ? gamers->p2 : gamers->p1);
		}

		current->round_img(g);
		g->refresh();
	}

	delete current;
	SDL_Quit();
}