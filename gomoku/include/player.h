#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "headers.h"
#include "gomoku.h"
#include "ia.h"

// Represente un joueur
class Player
{
public:
  std::string name;
  char case_type;
  int paires;
  int y;
  bool is_ia;
  Player_ia *ia_obj;

  Player(char case_type, bool is_ia);
  void action(Gomoku *g, Player *other);
  void annuler(Gomoku *g, Player *other);
  void round_img(Gomoku *g);
  void update_paires(Gomoku *g, Player *other);
  char get_case();
  bool play_case(Gomoku *g, Player *p, int x, int y, char type);
};

#endif
