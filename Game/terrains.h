#ifndef terrains_h_
#define terrains_h_

class Terrains{
public:
    Terrains():terrType('P'), standable(true){}
    Terrains(char t){
        terrType = t;
        if(terrType == 'P')
            standable = true;
        else{
            standable = false;
        }
    }
    //chars include W(Water) M(mountain) B(building) P(plains)
    char terrType;
    bool standable;

};


#endif