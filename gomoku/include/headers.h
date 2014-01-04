#pragma once

#include <SDL/SDL.h>
#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#define CASE_EMPTY 0
#define CASE_EMPTY_IA_IA 3
#define CASE_EMPTY_IA_PLAYER 4
#define CASE_J1 1
#define CASE_J2 2
#define CASE_OUTSIDE 5

#define CASE_WARN_J1 6
#define CASE_WARN_J2 7
#define CASE_RED_J1 8
#define CASE_RED_J2 9
#define CASE_HELP_J1 10
#define CASE_HELP_J2 11

#define HOR 19
#define VER 19
#define TOP_SPACE 150
#define RIGHT_SPACE 240
#define GOMOKU_SIZE 40

#define INTERVAL_DEFAULT 1
#define PROFONDEUR_DEFAULT 2

#define GOM_CHECKBOX_1 1
#define GOM_CHECKBOX_2 2
#define GOM_IA 6
#define GOM_HELP 7
#define GOM_CHECKBOX_IA1 3
#define GOM_CHECKBOX_IA2 4
#define GOM_CHECKBOX_HELP 5

void start();