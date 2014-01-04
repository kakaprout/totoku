#ifndef __IA_TREE_H__
#define __IA_TREE_H__

#include "gomoku.h"

class    ia_tree
{
  private:
          std::stack<Gomoku_pos> p;
          char **c;
  public:
          ia_tree* parent;
          int x, y;
          int fx, fy;
          int counter;
          int cout;
          Gomoku* Gom;
          ia_tree(Gomoku*);
         ~ia_tree();
         ia_tree* give_parent();
         int      evaluate_node();
         char*     create_tree();
         ia_tree* create_node(ia_tree *, int, int, int);
         bool is_playable(int, int, int);
         bool is_in_board(int, int, char*);
         bool is_free_within_board(int, int, char*);
       //  void browse_board(ia_tree*);
         void browse_board_test(ia_tree*);
         int  eval_cout();
};

#endif
