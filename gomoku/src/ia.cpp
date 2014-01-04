#include "../include/ia.h"

Player_ia::Player_ia(char player)
{
 this->numPlayer = player;
}

Player_ia::~Player_ia()
{
}

void Player_ia::action(Gomoku *g, char *coord)
{
     char *value = (char *) malloc(sizeof(char) * 2);
     
     ia_tree* tr = new ia_tree(g);
     value = tr->create_tree();
     coord[0] = value[0];
     coord[1] = value[1];
}
