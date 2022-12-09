#ifndef player_h_
#define player_h_

#include "enemies.h"

class Player{
public:
    Player(): hp(3), mvm(3), cannon(true){}
    
    Player(int ahp, int amvm):hp(ahp), mvm(amvm), cannon(true), atkdir('x'){
        if(ahp == 2)
            cannon = false;
    }

    int hp, mvm;
    bool cannon;
    char atkdir;

};

#endif