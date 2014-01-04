#pragma once

#include "headers.h"
#include "gomoku_pos.h"

class Gomoku
{
private:
  int stop;
  bool state;

public:
  char c[VER][HOR];
  char c_additional[VER][HOR];
  SDL_Surface *screen;
  bool additional_rules_1; // Regle des 3
  bool additional_rules_2; // Regle de fin de partie
  bool ia1_activated;
  bool ia2_activated;
  bool help_activated;
  char winner;
  std::stack<Gomoku_pos> p;
  std::stack<std::string> log;
  char can_win_type;
  int can_win_x;
  int can_win_y;

  Gomoku();
  ~Gomoku();
  void load_header();
  void print_text(int x, int y, char *text, int size);
  void load_checkbox(char type, bool state);
  void print_img(int x, int y, const char *str);  
  void check_rules(int x, int y, char type);
  void load_tab(bool debug);
  bool validate_case(int case_x, int case_y, char type);
  int validate_case_ia(int case_x, int case_y, char type, char**);
  int check_paire(int case_x, int case_y, char type);
  void check_winner(int case_x, int case_y, char type);
  bool check_winner_ia(int case_x, int case_y, char type);
  void set_case(int x, int y, char type);
  bool game_finished();  
  void is_finished();
  void ligneHorizontale(int x, int y, int w, Uint32 coul);
  void ligneVerticale(int x, int y, int h, Uint32 coul);
  void rectangle(int x, int y, int w, int h);
  bool trois_libre(char, char *, int, int, std::stack<Gomoku_pos> *);
  int trois_libre_ia(char, char *, int, int, std::stack<Gomoku_pos> *);
  void refresh();
  bool alignement_victorieux(int, int, char *, char, std::stack<Gomoku_pos> *);
  bool check_help();
  void calcul_help(char type);
  
  bool alignement_dangereux_ia(int, int, char *, char, char **);
};
