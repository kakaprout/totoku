#include "../include/gomoku.h"
#include "../include/players.h"

Gomoku::Gomoku()
  {
    int i;

    this->can_win_type = CASE_EMPTY;
    this->state = false;
    this->additional_rules_1 = true;
    this->additional_rules_2 = true;
    this->ia1_activated = false;
    this->ia2_activated = false;
    this->help_activated = false;
 
    for (i = 0; i < VER; i++)
      {
	memset(this->c[i], CASE_EMPTY, HOR);
	memset(this->c_additional[i], CASE_EMPTY, HOR);
      }
  }
  
void Gomoku::load_header()
  {
    this->print_img(0, 0, "img/menu.png");

    this->load_checkbox(GOM_CHECKBOX_1, this->additional_rules_1);
    this->load_checkbox(GOM_CHECKBOX_2, this->additional_rules_2);
    this->load_checkbox(GOM_CHECKBOX_IA1, this->ia1_activated);
    this->load_checkbox(GOM_CHECKBOX_IA2, this->ia2_activated);
    this->load_checkbox(GOM_CHECKBOX_HELP, this->help_activated);
  }
  
    // Affiche du texte avec la librairie TTF
  void Gomoku::print_text(int x, int y, char *text, int size)
  {
    TTF_Font* Font = TTF_OpenFont("img/TinDog.ttf", size);

    if(!Font)
      {
	printf("Erreur de création de la police : %s\n", TTF_GetError());
	exit(1);
      }
    SDL_Color TextColor;
    TextColor.r = 0;
    TextColor.g = 0;
    TextColor.b = 0;
    
    SDL_Surface* TextSurface = TTF_RenderText_Solid(Font, text, TextColor);
    
    if(!TextSurface)
      {
	printf("Erreur de rendu du texte : %s\n", TTF_GetError());
	exit(1);
      }
    
    SDL_Rect DstRect;
    DstRect.x = x;
    DstRect.y = y;
    DstRect.w = TextSurface->w;
    DstRect.h = TextSurface->h;
    
    /* Affiche toute la surface en 0,0 */
    SDL_BlitSurface(TextSurface, NULL, this->screen, &DstRect);
    
    /* Libère notre surface et notre police */
    SDL_FreeSurface(TextSurface);
    TTF_CloseFont(Font);
  }

   // Coche ou non les checkbox des regles
  void Gomoku::load_checkbox(char type, bool state)
  {
    int x, y;

    x = 0;
    y = 0;
    switch (type)
      {
      case GOM_CHECKBOX_1 :
	x = 575;
	y = 23;
	break;

      case GOM_CHECKBOX_2 :
	x = 575;
	y = 54;
	break;

      case GOM_CHECKBOX_IA1 :
	x = 800;
	y = 23;
	break;

      case GOM_CHECKBOX_IA2 :
	x = 800;
	y = 53;
	break;

      case GOM_CHECKBOX_HELP :
	x = 800;
	y = 84;
	break;
      }

    this->print_img(x, y, (state) ? "img/check_box_plein.png" : "img/check_box_vide.png");
  }
  
    // Affiche une image en SDL
  void Gomoku::print_img(int x, int y, const char *str) 
  {
    SDL_Surface *s;
    SDL_Rect pos;

    pos.x = x;
    pos.y = y;
    s = IMG_Load(str);
    if (!s)
      {
	fprintf(stderr, "Can't find img %s\n", str);
	exit(0);
      }
    SDL_BlitSurface(s, NULL, this->screen, &pos);
    SDL_FreeSurface(s);
  }

void Gomoku::refresh()
{
  if (SDL_Flip(this->screen) == -1)
    {
      fprintf(stderr, "Can't refresh the window\n");
      exit(0);
    }
}
  
    // Verifie si on a cliquer sur le changement des regles
void Gomoku::check_rules(int x, int y, char type)
  {
    std::ostringstream t;
    int i;
    bool *p;

    static int box_coord[5][5] = {
      {GOM_CHECKBOX_1, 575, 125, 23, 14},
      {GOM_CHECKBOX_2, 575, 170, 54, 14},
      {GOM_CHECKBOX_IA1, 800, 100, 20, 18},
      {GOM_CHECKBOX_IA2, 800, 100, 50, 18},
      {GOM_CHECKBOX_HELP, 800, 100, 80, 18}
    };

    static char *box_log[5] = {
      "Regle des 3",
      "Regle de fin de partie",
      "IA Joueur 1",
      "IA Joueur 2",
      "Aide personelle"
    };

    // On verifie si le joueur a cliquer sur une des checkbox
    for (i = 0; i < 5; i++)
      {
	if (x > box_coord[i][1] && x < (box_coord[i][1] + box_coord[i][2]) 
	    && y > box_coord[i][3] && y < (box_coord[i][3] + box_coord[i][4]))
	  {
	    if (box_coord[i][0] == GOM_CHECKBOX_1)
	      p = &this->additional_rules_1;
	    else  if (box_coord[i][0] == GOM_CHECKBOX_2)
	      p = &this->additional_rules_2;
	    else  if (box_coord[i][0] == GOM_CHECKBOX_IA1)
	      p = &this->ia1_activated;
	    else  if (box_coord[i][0] == GOM_CHECKBOX_IA2)
	      p = &this->ia2_activated;
	    else  if (box_coord[i][0] == GOM_CHECKBOX_HELP)
	      p = &this->help_activated;

	    // Interdiction de cocher l'aide personalisee si les deux IA sont cochees
	    if (box_coord[i][0] == GOM_CHECKBOX_HELP && this->ia1_activated && this->ia2_activated)
	      break;

	    // Inversion de la valeur (cochee ou decochee)
	    *p = !*p;
	    this->load_checkbox(box_coord[i][0], *p);


	    // Si on vient de cocher l'aide personalisee
	    if (box_coord[i][0] == GOM_CHECKBOX_HELP)
	      {
		if (this->check_help())
		  this->calcul_help(type);
	      }

	    // Ajout du log pour la checkbox
	    if (*p)
	      t << box_log[i] << " ON";
	    else
	      t << box_log[i] << " OFF";
	      this->log.push(t.str());
	    this->load_tab(false);
	    break;
	  }
      }

    // Desactivation de l'aide si on coche l'IA1 et l'IA2
    if ((box_coord[i][0] == GOM_CHECKBOX_IA1 || box_coord[i][0] == GOM_CHECKBOX_IA2)
	&& this->ia1_activated && this->ia2_activated && this->help_activated)
      {
	this->help_activated = false;
	this->load_checkbox(GOM_CHECKBOX_HELP, this->help_activated);
      }
  }


  void Gomoku::load_tab(bool debug)
  {
    int i, j;
    SDL_Surface *s;
    SDL_Rect pos;

    pos.x = 0;
    pos.y = TOP_SPACE;

    for (i = 0; i < VER; i++)
      {
	for (j = 0; j < HOR; j++)
	  {
	    if (debug)
	      {
		printf("X=%d ; Y=%d ; STATE=%d\n", j, i, this->c[i][j]);
	      }

	    switch (this->c[i][j])
	      {
	      case CASE_EMPTY :
		if (i == 0 && j == 0)
		  s = IMG_Load("img/40px/40px-Go_ul.svg.png");
		else if ((i != 0 && i != HOR - 1) && j == 0)
		  s = IMG_Load("img/40px/40px-Go_l.svg.png");
		else if (i == HOR - 1 && j == 0)
		  s = IMG_Load("img/40px/40px-Go_dl.svg.png");
		else if (i == 0 && j != 0 && j != VER - 1)
		  s = IMG_Load("img/40px/40px-Go_u.svg.png");
		else if (i == HOR - 1 && j != 0 && j != VER - 1)
		  s = IMG_Load("img/40px/40px-Go_d.svg.png");
		else if (i == HOR - 1 && j == VER - 1)
		  s = IMG_Load("img/40px/40px-Go_dr.svg.png");
		else if (i != 0 && i != HOR - 1 && j == VER - 1)
		  s = IMG_Load("img/40px/40px-Go_r.svg.png");
		else if (i == 0 && j == HOR - 1)
		  s = IMG_Load("img/40px/40px-Go_ur.svg.png");
		else
		  s = IMG_Load("img/40px/40px-Go_.svg.png");
		break;
		
	      case CASE_J1 :
		s = IMG_Load("img/40px/40px-Go_w.svg.png");
		break;

	      case CASE_J2 :
		s = IMG_Load("img/40px/40px-Go_b.svg.png");
		break;
	      }

	    switch (this->c_additional[i][j])
	      {
	      case CASE_WARN_J1 :
		s = IMG_Load("img/40px/warning_j1.png");
		break;

	      case CASE_WARN_J2 :
		s = IMG_Load("img/40px/warning_j2.png");
		break;

	      case CASE_RED_J1 :
		s = IMG_Load("img/40px/red_j1.png");
		break;

	      case CASE_RED_J2 :
		s = IMG_Load("img/40px/red_j2.png");
		break;

	      case CASE_HELP_J1 :
		s = IMG_Load("img/40px/help_j1.png");
		break;

	      case CASE_HELP_J2 :
		s = IMG_Load("img/40px/help_j2.png");
		break;
	      }
	    
	    SDL_BlitSurface(s, NULL, this->screen, &pos);
	    SDL_FreeSurface(s);
	    pos.x += 40;
	  }
	pos.x = 0;
	pos.y += 40;
      }

    // Affiche la partie droite
    SDL_Rect r;
    r.x = HOR * GOMOKU_SIZE;
    r.y = TOP_SPACE;
    r.w = RIGHT_SPACE;
    r.h = VER * GOMOKU_SIZE + TOP_SPACE;
    SDL_FillRect(this->screen, &r, SDL_MapRGB(this->screen->format, 220, 179, 92));

    // Affiche les coordonees
    pos.x = 11;
    pos.y = TOP_SPACE - 4;
    static char *alphabet = "ABCDEFGHIJKLMNOPQRS";

    // Affiche les logs
    std::stack<std::string> tmp;
    int size;
    size = this->log.size();
    for (i = 0; i < size; i++)
      {
	if (i < 30 && this->log.top().length() > 0)
	  this->print_text(HOR * GOMOKU_SIZE + 40, TOP_SPACE + (i * 25), (char *) this->log.top().c_str(), 16);
	tmp.push(this->log.top());
	this->log.pop();
      }
 
    for (i = 0; i < size; i++)
      {
	this->log.push(tmp.top());
	tmp.pop();
      }

    this->refresh();
  }

// Verifie s'il y a un trois libre sur la direction qu'on parcours
// a l'aide des positions de depart et de la matrice.
bool Gomoku::trois_libre(char type, char *matrix, int start_x, int start_y, std::stack<Gomoku_pos> *s)
{
  int i, x, y, count;
  char current, last_type;
  Gomoku_pos p;

  // Parours des cases de la direction
  //printf("Matrix: x=%d - y=%d - type = %d\n", start_x, start_y, type);
  count = 0;
  last_type = CASE_EMPTY;
  x = start_x;
  y = start_y;
  for (i = 0; i < 9; i++)
    {
      current = (x < 0 || x > HOR || y < 0 || y > VER) ? CASE_OUTSIDE : this->c[y][x];

      // Si on arrive au milieu du parcours, c'est qu'on est sur la case qu'on veut poser
      // on simule donc la presence de son type
      if (i == 4)
	current = type;

      //printf("X=%d,Y=%d,current=%d,last_type=%d\n", x, y, current, last_type);

      // Si la precedente case etait vide, on peut commencer a compter un alignement de 3
      // OU si un alignement a ete commence et qu'on tombe sur une case du bon type on l'ajoute au compteur
      if ((i > 0 && last_type == CASE_EMPTY && current == type) || (count > 0 && current == type))
	{
	  count++;
	  p.x = x;
	  p.y = y;
	  s->push(p);
	}
 
      // Si on tombe sur une case qui est a l'adversaire, on remet le compteur a 0
      // OU si on tombe sur une case vide, et que la precedente etait vide on remet le compteur a
      if ((current != CASE_EMPTY && current != type) || (current == CASE_EMPTY && last_type == CASE_EMPTY))
	{
	  while (s->size() > 0)
	    s->pop();
	  count = 0;
	}

      // Si on a un alignement de 3 et que la case courrante est vide, on a un alignement correct
      if (count == 3 && current == CASE_EMPTY)
	return (true);

      last_type = current;
      x += matrix[0];
      y += matrix[1];
    }
  return (false);
}


  // retourne TRUE si la case indiquee est valide
bool Gomoku::validate_case(int case_x, int case_y, char type)
{
  if (this->c[case_y][case_x] != CASE_EMPTY)
    {
      return (false);
    }

    // Implentation de la regle des 3
    if (this->additional_rules_1)
      {
	int m, save_m, x, y, total_alignement_3 = 0;
	std::stack<Gomoku_pos> s, save_s;
	char matrix[4][2] = {
	  {1, 1},  // Diagonale haut gauche -  bas droite
	  {0, 1},  // Ligne verticale
	  {-1, 1}, // Diagonale haut droite - bas  gauche
	  {1, 0}   // Ligne horizontale
	};

	// Parcours des 4 directions basees sur la position du pion pose
	for (m = 0; m < 4; m++)
	  {
	    x = case_x - (4 * matrix[m][0]);
	    y = case_y - (4 * matrix[m][1]);

	    // Verification de l'existence d'un trois libre sur la ligne
	    if (this->trois_libre(type, matrix[m], x, y, &s))
	      {
		save_m = m;
		save_s = s;
		total_alignement_3++;
	      }

	    if (total_alignement_3 == 2)
	      return (false);
	  }

	// Si on est tombe sur un seul alignement, on va verifier s'il existe
	// un trois libre sur les pions de cet alignement
	if (total_alignement_3 == 1)
	  {
	    while (save_s.size() > 0)
	      {
		// Pour les deux autres pions de l'alignement qu'on vient de creer, on cherche
		// les alignements de 3
		if (!(save_s.top().x == case_x && save_s.top().y == case_y))
		  {
		    for (m = 0; m < 4; m++)
		      {
			// On parcourt la matrice sauf la direction de l'alignement actuel
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
	  
      }
    return (true);
  }

    // Verifie et mange des paires
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
//	  printf("x : %d, y : %d | case_x : %d, case_y : %d\n", x, y, case_x, case_y);
	  if (this->c[case_y + y][case_x + x] == second_type
	      && this->c[case_y + (2 * y)][case_x + (2 * x)] == second_type
	      && this->c[case_y + (3 * y)][case_x + (3 * x)] == type
	      && (case_x + 3*x) < 19 && (case_y + 3*y) < 19
          )
	    {
//             printf("BON\n");
	      this->c[case_y + y][case_x + x] = CASE_EMPTY;
	      this->c[case_y + (2 * y)][case_x + (2 * x)] = CASE_EMPTY;
	      total += 2;

	      // Ajout dans la pile
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

	      std::ostringstream t;
	      if (type == CASE_J1)
		t << "Joueur 1 vole une paire";
	      else
		t << "Joueur 2 vole une paire";
	      this->log.push(t.str());
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
  //printf("MATRIX ; X=%d, Y=%d\n", start_x, start_y);
  for (i = 0; i < 9; i++)
    {
      //printf("X=%d,Y=%d\n", x, y);
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
	{
	  //printf("TRUE %d !!!!!\n", s->size());
	  return (true);
	}

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
      
      // Parcours des 4 directions basees sur la position du pion pose
      for (m = 0; m < 4; m++)
	{
	  x = case_x - (4 * matrix[m][0]);
	  y = case_y - (4 * matrix[m][1]);
	  
	  if (this->alignement_victorieux(x, y, matrix[m], type, &s))
	    {
	      if (this->additional_rules_2)
		{
		  // Ajout d'une case verte puisque le joueur a (ou va) gagner
		  std::stack<Gomoku_pos> cases = s;
		  while (cases.size() > 0)
		    {
		      this->c_additional[cases.top().y][cases.top().x] = (type == CASE_J1) ? CASE_WARN_J1 : CASE_WARN_J2;
		      cases.pop();
		    }

		  // On parcourt les pions recuperes dans la stack et on regarde si la combinaison est brisable
		  while (s.size() > 0)
		    {
		      x = s.top().x;
		      y = s.top().y;

		      // Pour chaque case de l'alignement on va parcourir une matrix de sens (exepte les deux
		      // sens sur la direction de l'aligement
		      //printf("CHEC_POINT\n");
		      for (m2 = 0; m2 < 8; m2++)
			{
			  count = 0;

			  // Tout sauf les deux sens de la direction de l'alignement
			  if ((matrix2[m2][0] == matrix[m][0] && matrix2[m2][1] == matrix[m][1])
			      || (matrix2[m2][0] == -matrix[m][0] && matrix2[m2][1] == -matrix[m][1]))
			    continue;

			  //printf("MATRIX[%d][%d]\n", matrix2[m2][0], matrix2[m2][1]);

			  // La condition pour savoir si on est prenable est simple :
			  // - Le pion deriere nous doit etre vide
			  // - Le premier pion venant doit etre du meme type que nous
			  // - Le second pion venant doit etre ennemi
			  x2 = x - matrix2[m2][0];
			  y2 = y - matrix2[m2][1];
			  //printf("X2=%d ; Y2=%d ; TYPE=%d\n", x2, y2, this->c[y2][x2]);
			  if (this->c[y2][x2] == CASE_EMPTY)
			    {
			      //printf("COUNT1\n");
			      count++;
			    }

			  x2 = x + matrix2[m2][0];
			  y2 = y + matrix2[m2][1];
			  //printf("X2=%d ; Y2=%d ; TYPE=%d\n", x2, y2, this->c[y2][x2]);
			  if (this->c[y2][x2] == type)
			    {
			      //printf("COUNT2\n");
			      count++;
			    }

			  x2 = x + (2 * matrix2[m2][0]);
			  y2 = y + (2 * matrix2[m2][1]);
			  //printf("X2=%d ; Y2=%d ; TYPE=%d\n", x2, y2, this->c[y2][x2]);
			  if (this->c[y2][x2] != CASE_EMPTY && this->c[y2][x2] != type)
			    {
			      //printf("COUNT3\n");
			      count++;
			    }
			 
			  if (count == 3)
			    {
			      // L'autre joueur devra jouer ici, sinon il perdra ...
			      this->can_win_type = type;
			      this->can_win_x = x - matrix2[m2][0];
			      this->can_win_y = y - matrix2[m2][1];
			      return ;
			    }
			}
		      s.pop();
		    }
		}
	      this->winner = type;
	      this->is_finished();
	      break;
	    }
	}
    }

// Vide le tableau des aides, et retourne TRUE si l'aide est activee
bool Gomoku::check_help()
{
  int x, y;

  for (y = 0; y < VER; y++)
    {
      for (x = 0; x < HOR; x++)
	{
	  if (this->c_additional[y][x] != CASE_WARN_J1 && this->c_additional[y][x] != CASE_WARN_J1
	      && this->c_additional[y][x] != CASE_EMPTY)
	    this->c_additional[y][x] = CASE_EMPTY;
	}
    }

  return (this->help_activated);
}

void Gomoku::calcul_help(char type)
{
/*  int x, y;

  for (y = 0; y < VER; y++)
    {
      for (x = 0; x < HOR; x++)
	{
	  if (this->c_additional[y][x] != CASE_WARN_J1 && this->c_additional[y][x] != CASE_WARN_J1
	      && this->c_additional[y][x] != CASE_EMPTY)
	    this->c_additional[y][x] = CASE_EMPTY;

	  if (this->c[y][x] == CASE_EMPTY)
	    {
	      if (!this->validate_case(x, y, type))
		{
		  this->c_additional[y][x] = (type == CASE_J1) ? CASE_RED_J1 : CASE_RED_J2;
		}
	    }
	}
    }
*/
//this->c_additional[rand() % 10][rand() % 10] =CASE_RED_J1;
   Player_ia *iap;
   char coord[3];
   
   iap = new Player_ia(type);
   iap->action(this, coord);
//   std::cout << coord[0] << coord[1] << std::endl;
   this->c_additional[coord[1]][coord[0]] = ((type == CASE_J1) ? CASE_HELP_J1 : CASE_HELP_J2);
}

  // Assigne une case sur le terrain
  void Gomoku::set_case(int x, int y, char type)
  {
    Gomoku_pos p;

    // Sauvegarde du coup dans la pile
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
	this->rectangle(5, 5, 275, 125);
	if (this->winner == CASE_J1)
	  this->print_text(50, 50, "Le joueur 1 gagne !", 24);
	else
	  this->print_text(35, 50, "Le joueur 2 gagne !", 24);
	this->refresh();
      }

    return (this->state);
  }
  
    void Gomoku::is_finished()
  {
    this->state = true;
  }

  void Gomoku::ligneHorizontale(int x, int y, int w, Uint32 coul)
  {
    SDL_Rect r;
    
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = 1;
    
    SDL_FillRect(this->screen, &r, coul);
  }

  void Gomoku::ligneVerticale(int x, int y, int h, Uint32 coul)
  {
    SDL_Rect r;
    
    r.x = x;
    r.y = y;
    r.w = 1;
    r.h = h;
    
    SDL_FillRect(this->screen, &r, coul);
  }

  void Gomoku::rectangle(int x, int y, int w, int h)
  {
    Uint32 c = SDL_MapRGB(this->screen->format, 0, 0, 0);
    SDL_Rect pos;

    pos.x = x;
    pos.y = y;
    pos.w = w;
    pos.h = h;
    SDL_FillRect(this->screen, &pos, SDL_MapRGB(this->screen->format, 224, 147, 26));

    ligneHorizontale(x, y, w, c);
    ligneHorizontale(x, y + h - 1, w, c);
    ligneVerticale(x, y + 1, h - 2, c);
    ligneVerticale(x + w - 1, y + 1, h - 2, c);
  }

  Gomoku::~Gomoku()
  {

  }
  

