#ifndef __IA_H__
#define __IA_H__

#include "gomoku.h"
#include "ia_tree.h"

class Player_ia
{
private:
        char numPlayer; 
        
public:
       Player_ia(char);
       ~Player_ia();
       void action(Gomoku *, char *);
};

#endif
