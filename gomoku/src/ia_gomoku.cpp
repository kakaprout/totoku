#include "../include/gomoku.h"

int Gomoku::trois_libre_ia(char type, char *matrix, int start_x, int start_y, std::stack<Gomoku_pos> *s)
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
	return (3);

      last_type = current;
      x += matrix[0];
      y += matrix[1];
    }
  return 0;

}


int Gomoku::validate_case_ia(int case_x, int case_y, char type, char **tab_ia)
{
  if (tab_ia[case_y][case_x] != CASE_EMPTY)
    {
      return (0);
    }
    int val = 0;

    // Implentation de la regle des 3
    if (this->additional_rules_1)
      {
	int m, save_m, x, y, total_alignement_3 = 0;
	std::stack<Gomoku_pos> s;
	std::stack<Gomoku_pos> save_s;
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
	    if (val = this->trois_libre_ia(type, matrix[m], x, y, &s) > 0)
	      {
		save_m = m;
		save_s = s;
		total_alignement_3++;
	      }

	    if (total_alignement_3 == 2)
	      return (val);
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
			if (this->trois_libre_ia(type, matrix[m], x, y, &s))
			  return (0);
		      }
		  }
		save_s.pop();
	      }
	  }
	  
      }
    return (3);
  }

    bool Gomoku::check_winner_ia(int case_x, int case_y, char type)
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
			      return false;
			    }
			}
		      s.pop();
		    }
		}
	      return true;
	    }
	}
	return false;
    }
    
        bool Gomoku::alignement_dangereux_ia(int start_x, int start_y, char *matrix, char type, char ** tab_ia)
    {
         int i, x, y, total;
//         Gomoku_pos p;

         x = start_x;
         y = start_y;
         total = 0;
         //printf("MATRIX ; X=%d, Y=%d\n", start_x, start_y);
         for (i = 0; i < 9; i++)
         {
             //printf("X=%d,Y=%d\n", x, y);
             if (tab_ia[y][x] == type) // type = valeur emplacement occupe par autre joeur
	               total++;
             else
	             total = 0;

              if (total == 4)
              	  return (true);
                    
              x += matrix[0];
              y += matrix[1];
        }
        return (false);
    }
    
