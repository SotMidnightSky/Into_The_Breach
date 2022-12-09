#ifndef enemies_h_
#define enemies_h_
#include "grid.h"

class Enemies{
public:
    Enemies(){
        scorp = true;
        hp = 3;
        mvm = 3;
        atkdir = 'd';
    }
    Enemies(int ahp, int amvm):hp(ahp), mvm(amvm), atkdir(' '), scorp(true){
        if (mvm == 2){scorp = false;}
    }
    bool scorp;
    int hp, mvm;
    char atkdir; 
};

// class Firefly{
// public:
//     Firefly(): hp(3), mvm(2){}
//     void attacked(int dmg){hp -= dmg;}
//     void attack(char dir){
//         attacking = atk;
//         }
// private:
//     int hp, mvm;
//     Grid attacking, currGrid;
// };

#endif