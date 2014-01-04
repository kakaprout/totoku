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

    // Capture des evenements SDL
    while (!done)
      {
	while(SDL_PollEvent(&event))
	  {
	    switch(event.type)
	      {
	      case SDL_QUIT:
		// Evenement quand on kill le jeu
		exit(0);
		break;

	      case SDL_MOUSEBUTTONDOWN :
		// Evenement lors d'un click gauche
		if (event.button.button == SDL_BUTTON_LEFT)
		  {
		    // Si on click au niveau du top space
		    if (event.button.y < TOP_SPACE)
		      {
			g->check_rules(event.button.x, event.button.y, this->case_type);
			if (this->case_type == CASE_J1 && g->ia1_activated && !this->is_ia)
			  this->is_ia = true;
			else if (this->case_type == CASE_J2 && g->ia2_activated && !this->is_ia)
			  this->is_ia = true;

			// Jeu fini ?
			if (event.button.x > 560 && event.button.x < (560 + 170)
			    && event.button.y > 104 && event.button.y < (104 + 18))
			  {
			    exit(0);
			  }
			// Nouvelle partie ?
			else if (event.button.x > 295 && event.button.x < (295 + 115)
				  && event.button.y > 102 && event.button.y < (102 + 18))
			  {
			    delete g;
			    start();
			    exit(0);
			  }
			// Annuler un coup
			else if (event.button.x > 440 && event.button.x < (440 + 85)
				 && event.button.y > 102 && event.button.y < (102 + 18))
			  {
			    this->annuler(g, other);
			    done = true;
			  }
		      }
		    // Si on click sur le jeu
		    else if (!this->is_ia && event.button.x < HOR * GOMOKU_SIZE)
		      {
			// Case X et Y cliquee en fonction des coordonees
			x = event.button.x / GOMOKU_SIZE;
			y = (event.button.y - TOP_SPACE) / GOMOKU_SIZE;
			type = this->get_case();
			
			if (this->play_case(g, other, x, y, type))
			  done = true;
			  break;
		      }
		  }
		break;
	       
	      default:
		break;
	      }
	  }

	if (this->is_ia)
	  done = true;
      }

    // Le calcul de l'IA est apres les evenements SDL pour laisser la possibilite au joueur de stopper
    // l'IA si les deux sont actives et se battent en boucle
    if (this->is_ia)
      {
	char ia_coord[3], stop;
	stop = 0;
	while (stop++ < 10)
	  {
	    this->ia_obj->action(g, ia_coord);
	    if (this->play_case(g, other, (int) ia_coord[0], (int) ia_coord[1], this->case_type))
	      {
		return ;
	      }
	  }
	printf("Gomoku: IA error: can't find real positions\n");
	exit(0);
      }
  }

// Joue la case
bool Player::play_case(Gomoku *g, Player *other, int x, int y, char type)
{
  int i;

  // Validation et ajout de la case
  if (g->validate_case(x, y, type))
    {
      // Si l'autre joueur allait gagner et que le joueur courrant ne joue pas la, tant pis pour lui :p
      if (g->additional_rules_2 && g->can_win_type != CASE_EMPTY)
	{
	  if (x == g->can_win_x && y == g->can_win_y)
	    {
	      g->can_win_type = CASE_EMPTY;
	      for (i = 0; i < VER; i++)
		memset(g->c_additional[i], CASE_EMPTY, HOR);
	    }
	  else
	    {
	      g->winner = other->case_type;
	      g->is_finished();
	      return (true);
	    }
	}

      g->set_case(x, y, type);

      std::ostringstream t;
      t << this->name << " joue en " << (char) (65 + x) << (y + 1);
      g->log.push(t.str());
      this->paires += g->check_paire(x, y, type);
      this->update_paires(g, other);
      if (this->paires >= 10)
	{
	  g->winner = type;
	  g->is_finished();
	  return (true);
	}
      g->check_winner(x, y, type);
      g->load_tab(false);
      return (true);
    }

  // Case non valide ...
  std::ostringstream t;
  t << "Non valide : " << (char) (65 + x) << (y + 1);
  g->log.push(t.str());
  g->load_tab(false);
  return (false);
}

  void Player::annuler(Gomoku *g, Player *other)
  {
    Gomoku_pos p;
    int i, size;

    if (g->p.size() > 0)
      {
	std::ostringstream t;
	t << other->name << " annule son coup";
	g->log.push(t.str());

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
	g->load_tab(false);
	g->p.pop();
	this->update_paires(g, other);
      }
  }

  // Affiche les images du tour courant devant les joueurs
  // Swap permet d'inverser les images
  void Player::round_img(Gomoku *g)  
{
    g->print_img(290, 22, (this->case_type == CASE_J1) ? "img/actif.png" : "img/inactif.png");
    g->print_img(290, 52, (this->case_type == CASE_J2) ? "img/actif.png" : "img/inactif.png");
  }

  // Mise a jour du texte pour les paires
  void Player::update_paires(Gomoku *g, Player *other)
  {
    int i(0);
    int y(0);

    g->load_header();

    for (i = 0; i < this->paires && i < 10; i++)
      {
	g->print_img(400 + (i * 13), this->y, "img/pion.png");
      }

    if (other != NULL)
      {
	for (i = 0; i < other->paires && i < 10; i++)
	  {
	    g->print_img(400 + (i * 13), other->y, "img/pion.png");
	  }
      }
  }
  
  // Retourne le type de case du joueur
  char Player::get_case()
  {
    return (this->case_type);
  }
