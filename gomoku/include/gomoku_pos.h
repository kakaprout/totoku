#ifndef __GOMOKU_POS_H__
#define __GOMOKU_POS_H__

#include "headers.h"

class Gomoku_pos
{
public:
  int x;
  int y;
  bool is_paire;
  int paire1_x;
  int paire1_y;
  int paire2_x;
  int paire2_y;
  std::stack<Gomoku_pos*> paires;
};

#endif
