#ifndef grid_h_
#define grid_h_

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cassert>
#include <map>
#include "terrains.h"
#include "enemies.h"
#include "player.h"

class Grid
{
public:
    Grid():t_type(), g(false), b(false){}
    //Grid* up,* down, * left, *right;
    Terrains t_type;

    bool g, b;
    // g means friendly on it b means bad guy on it
    Enemies e_type;
    Player p_type;

};
#endif