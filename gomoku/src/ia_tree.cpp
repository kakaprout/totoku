#include "../include/headers.h"
#include "../include/ia_tree.h"
#include "../include/gomoku_pos.h"

// Classe pour la creation de l'arbre
// La classe Gomoku donne toutes les informations sur le jeu 
// (position des pions, ...)
// on copie la stack pour ne pas agir sur l'objet pointe Gomoku
ia_tree::ia_tree(Gomoku* gom)
{
	int i;
	this->Gom = gom;
	this->p = this->Gom->p;
	this->cout = 0;
	this->c = (char **) malloc (19 * sizeof (*this->c));
	for (i = 0; i < 19; i++)
		this->c[i] = (char *) malloc (19 * sizeof (*this->c[i]));
	/*for (int i = 0; i < 19; i++)
	for (int j = 0; j < 19; j++)
	this->c[i][j] = this->Gom->c[i][j];*/
	for (int i = 0; i < 19; i++)
		for (int j = 0; j < 19; j++)
			this->c[i][j] = this->Gom->c[i][j];

}

ia_tree::~ia_tree()
{
}

ia_tree* ia_tree::give_parent()
{
	return this->parent;
}

int      ia_tree::evaluate_node()
{
	return 0;
}

// Creation de l'arbre
// avec creation du premier noeud
// le parent est mis a NULL car il n'y en a pas
// puis on parcourt le plateau
// Cette methode n'est appelle que lors de la creation de l'arbre
char *ia_tree::create_tree()
{
	this->parent = NULL;
	if (this->p.empty() == true)
	{
		srand(time(NULL));
		this->x = rand() % (19 - 1);
		this->y = rand() % (19 - 1);
		this->fx = this->x - 1;
		this->fy = this->y - 1;
		std::cout << "x debut : " << this->x << " | y debut : " << this->y << std::endl;
	}
	else
	{
		//     }
		//this->browse_board_test(this);
		this->x = this->p.top().x;
		this->y = this->p.top().y;
		this->fx = this->x - 1;
		this->fy = this->y - 1;
		std::cout << "x debut : " << this->x << " | y debut : " << this->y << std::endl;
		this->counter = 0;
		this->browse_board_test(this);
	}
	char *val = (char *) malloc(sizeof(char) * 2);
	printf("RETURN OK : %d %d\n", this->fx, this->fy);
	val[0] = this->fx/* + 1*/;
	val[1] = this->fy/* + 1*/;

	return val;

}

bool ia_tree::is_in_board(int x, int y, char* m)
{
	if (x + m[0] < 0 || x + m[0] > 18)
		return false;
	if (y + m[1] < 0 || y + m[1] > 18)
		return false;
	return true;
}

bool ia_tree::is_free_within_board(int x, int y, char* m)
{
	if (this->c[x + m[0]][y + m[1]] != CASE_EMPTY)
		return false;
	return true;     
}

bool ia_tree::is_playable(int x, int y, int interval)
{
	//  std::cout << "--> " << x << ", " << y << std::endl;

	std::stack<Gomoku_pos> tmp_stack;
	tmp_stack = this->p;
	bool flag;

	if (this->c[y][x] != CASE_EMPTY)
		return false;
	while (!tmp_stack.empty())
	{
		flag = false;
		if (tmp_stack.top().x >= x && tmp_stack.top().y >= y)
		{
			if (tmp_stack.top().x - x <= interval && tmp_stack.top().y - y <= interval)
				flag = true;
		}
		else if (tmp_stack.top().x >= x && tmp_stack.top().y < y)
		{
			if (tmp_stack.top().x - x <= interval && y - tmp_stack.top().y <= interval)
				flag = true;
		}
		else if (tmp_stack.top().x < x && tmp_stack.top().y >= y)
		{
			if (x - tmp_stack.top().x <= interval && tmp_stack.top().y - y <= interval)
				flag = true;
		}
		else if (tmp_stack.top().x < x && tmp_stack.top().y < y)
		{
			if (x - tmp_stack.top().x <= interval && y - tmp_stack.top().y <= interval)
				flag = true;
		}
		if (flag == true)
		{
			//  std::cout << "VALID " << x << ", " << y << std::endl;     
			return true;
		}
		tmp_stack.pop();
	}
	// std::cout << "INVALID " << x << ", " << y << std::endl;     
	return false;
}

/*string ia_tree::name_current_player(ia_tree* t)
{
if (t->Gom->ia1_activated == true && t->Gom->ia2_activated == true)
{
if (t->counter % 2 == 0)
{
// Tour de l'IA 1
}
else
{
// Tour de l'IA 2
}   
}
else if (t->Gom->ia1_activated == true && t->Gom->ia2_activated == false)
{
if (t->counter % 2 == 0)
{
// Tour de l'IA 1
}
else
{
if (t->Gom->check_help() == true)
(
)
}

}
else if (t->Gom->ia1_activated == false && t->Gom->ia2_activated == true)
{
if (t->counter % 2 == 0)
{
if (t->Gom->check_help() == true)
(
)
}
else
{
// Tour de l'IA 2
}        
}
else
(
if (t->Gom->check_help() == true)
(
if (t->counter % 2 == 0)
{
}
else
{
}
)
)
}*/
void ia_tree::browse_board_test(ia_tree* tr)
{
	printf("RECEIVED : %d %d\n", tr->y, tr->x );
	int i, j;
	ia_tree *temp;
	char joueur = 0;
	int cout_en_cours = 0;

	if (tr->counter % 2 == 1)
		joueur = 2;
	else
		joueur = 1;
	//std::cout << " tour du joueur " << (joueur == 2 ? "JOUEUR 2" : "JOUEUR 1") << 
	//     " , counter = " << tr->counter << std::endl;
	if (tr->counter <= 2)
	{
		for (i = 0; i < 19; i++)
		{
			for (j = 0; j < 19; j++)
			{   
				if (is_playable(j, i, 1) == true
					/*&& (cout_en_cours = tr->Gom->validate_case_ia(j, i, joueur, tr->c)) >= 1*/)
				{
					//printf("OK : %d %d\n", j, i );
					//std::cout << "COUP JOUABLE" << std::endl;
					temp = create_node(tr, j, i, cout_en_cours);
					printf("OK : %d %d %d\n", j, i, temp->cout);
					//    std::cout << "Niveau : " << temp->counter << 
					// " Nouvelles coordonnees : x = " << temp->x << " y = " << temp->y << std::endl;
					//this->counter++;
					//this->browse_board(temp);
					if (temp->cout >= 1000)
					{
						temp->counter = tr->counter - 1;
						//        printf("Value modified 1\n");
						tr->fx = temp->x;
						tr->fy = temp->y;
						tr->cout = temp->cout;
						//     std::cout << "Nouvelles coordonnees : x = " 
						// << tr->x << " y = " << tr->y << std::endl;
						temp->browse_board_test(tr);
					}
					else
					{

						if ((temp->counter) < 2)
						{
							//printf("RENVOI SI counter < PR : %d %d %d\n", j, i, temp->cout);
							//temp->counter = tr->counter + 1;
							tr->fx = temp->x;
							tr->fy = temp->y;
							printf("V1 RENVOI SI counter < PR : %d %d %d\n", temp->x, temp->y, temp->cout);
							printf("V2 RENVOI SI counter < PR : %d %d %d\n", tr->fx, tr->fy, temp->cout);
							temp->browse_board_test(temp);
						}
						else
						{
							//printf("RENVOI SI counter = PR : %d %d %d\n", j, i, temp->cout);
							temp->counter = tr->counter - 1;
							tr->fx = temp->x;
							tr->fy = temp->y;
							printf("V1 RENVOI SI counter = PR : %d %d %d\n", temp->x, temp->y, temp->cout);
							printf("V2 RENVOI SI counter = PR : %d %d %d\n", tr->fx, tr->fy, temp->cout);
							//                            printf("Value modified 2 %d %d\n", tr->x, tr->y);
							//      std::cout << "Nouvelles coordonnees : x = " 
							// << tr->x << " y = " << tr->y << std::endl;                                  
							//temp->browse_board_test(tr);
						}  
					}
				}

				/*else
				{
				if (tr->counter > 1)
				{
				temp->counter = tr->counter - 1;
				if (temp->cout > tr->cout && temp->cout > 0 || 
				temp->cout < tr->cout && tr->cout <= 0)
				{
				tr->cout = temp->cout;
				}
				temp->browse_board_test(tr);
				}

				}*/

			}
		}
	}
}

//// Le parcours du plateau s'effectue en parcourant les cases etant dans
//// la profondeur specifiee par counter
//// Si la case est consideree comme valide, on cree un noeud
///*void ia_tree::browse_board(ia_tree* tr)
//{
//     int i, j;
//     ia_tree *temp;
//     char joueur = 0;
//     int cout_en_cours;
//     
//     if (this->counter <= 2)
//     {
//           for (i = 0; i < 19; i++)
//           {
//               for (j = 0; j < 19; j++)
//               {
//                   if (this->counter % 2 == 1)
//                      joueur = 1;
//                   else
//                      joueur = 2;
//                   if (is_playable(j, i, 1) == true
//                      /*&& (cout_en_cours = 
//                         this->Gom->validate_case_ia(j, i, joueur, this->c)) >= 1*/)
//                    {
//                         
//                          /*std::cout << "COUT EN COURS : " << cout_en_cours << std::endl;
//                          temp = create_node(tr, j, i, cout_en_cours);
//                          //this->counter++;
//                          //this->browse_board(temp);
//                          if (this->cout >= 1000)
//                          {
//                              std::cout << "Nouveaux noeud :: joueur = " << 
//              (temp->counter % 2 == 1 ? "JOUEUR 2" : "JOUEUR 1") << " , counter = " << temp->counter << std::endl;
//                             this->counter = tr->counter - 1;
//                             this->browse_board(tr);
//                          }
//                          else
//                          {
//                              if ((this->counter) < 2)
//                              {
//                                 this->counter = tr->counter + 1;
//                                 this->browse_board(temp);
//                              }  
//                          }
//                       }
//                       else
//                       {
//                           if (tr->counter > 1)
//                           {
//                              this->counter = tr->counter - 1;
//                              if (this->cout > tr->cout && this->cout > 0 || this->cout < tr->cout && tr->cout <= 0)
//                              {
//                                  tr->cout = this->cout;
//                              }
//                              this->browse_board(tr);
//                           }
//                           
//                       }
//               }
//           }
//     }
//     if (this->counter == 2)
//     {
//         /* EVALUATIOM DU COUT DU COUP*/
//         if (this->c[tr->x][tr->y] == CASE_EMPTY_IA_IA)
//         {
//             int play_value = 0;
//             
//             //this->Gom->validate_case(tr->x, tr->y, )
//                                
//         }
//         else if (this->c[tr->x][tr->y] == CASE_EMPTY_IA_PLAYER)
//         {
//              int play_value = 0;        
//              }*/
//         //this->counter--;     
//     }
//     /*while (this->counter-- > 0)
//     {
//         EVALUATIOM DU COUT DU COUP
//         if (this->Gom->c[tr->x][tr->y] == CASE_EMPTY_IA_IA)
//         {
//             int play_value = 0;
//             
//             //this->Gom->validate_case(tr->x, tr->y, )
//                                
//         }
//         else if (this->Gom->c[tr->x][tr->y] == CASE_EMPTY_IA_PLAYER)
//         {
//     *


ia_tree* ia_tree::create_node(ia_tree *par, int x, int y, int cout_en_cours)
{
	ia_tree *temp = new ia_tree(par->Gom);
	temp->parent = par;
	//temp->cout += par->cout + (cout_en_cours * 500);
	if (!(x >= 0 && x < 19 && y >= 0 && y < 19))
	{
		exit(1);
	}
	temp->x = x;
	temp->y = y;
	temp->counter = par->counter + 1;
	temp->cout = 0;
	temp->cout += par->cout;
	bool victory;
	bool defeat;
	if (temp->counter % 2 == 1)
	{
		temp->c[y][x] = CASE_EMPTY_IA_IA;
		victory = temp->Gom->check_winner_ia(x, y, 2);
		defeat = temp->Gom->check_winner_ia(x, y, 1);
		if (victory == true || defeat == true)
		{
			if (victory == true)
				temp->cout += 1000;
			else
				temp->cout += 5000;
			temp->parent->cout = temp->cout;
			//this->counter--;           
		}
		//if (this->Gom- == true)
		//   this->cout += 1000;
		//else if (this->Gom->check_winner_ia(x,y, 1) == true)
		//   this->cout += 5000;
		//else

	}
	else
	{
		temp->c[y][x] = CASE_EMPTY_IA_PLAYER;
		victory = temp->Gom->check_winner_ia(x,y, 1);
		defeat = temp->Gom->check_winner_ia(x,y, 2);
		if (victory == true || defeat == true)
		{
			if (victory == true)
				temp->cout -= 1000;
			else
				temp->cout -= 5000;
			temp->parent->cout = temp->cout;
			//this->counter--;            
		}
		//if (this->Gom->check_winner_ia(x,y, 1) == true)
		//   this->cout -= 1000;
		//else if (this->Gom->check_winner_ia(x,y, 2) == true)
		//   this->cout -= 5000;
		//else
	}
	return (temp); 

	//     this->Gom->c[x][y] != CASE_EMPTY

}
