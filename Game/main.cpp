#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cassert>
#include <map>

#include "grid.h"
#include "terrains.h"
#include "enemies.h"
#include "player.h"

int main(int argc, char *argv[])
{
    int totalScore = 0;
    std::vector<std::vector<Grid>> map;
    map.resize(8);
    for (int i = 0; i < (int)map.size(); ++i)
    {
        map[i].resize(8);
    }

    std::ifstream puzzle(argv[1]);
    std::ifstream commands(argv[2]);

    std::string line;
    int xcount = 0;
    int ycount = 0;
    std::pair<int, int> playerCoord;
    while (puzzle >> line)
    {
        // casf
        if (xcount == 8)
        {
            xcount = 0;
            ++ycount;
        }
        char t_type = line[0];
        char e_type = line[1];
        map[ycount][xcount] = Grid();
        Grid *tmp = &map[ycount][xcount];
        tmp->t_type.terrType = t_type;
        if(t_type != 'P'){
            tmp->t_type.standable = false;
        }
        if (e_type == 'X')
        {
            xcount += 1;
            continue;
        }
        else if (e_type == 'C')
        {
            tmp->g = true;
            playerCoord = std::make_pair(ycount, xcount);
        }
        else if (e_type == 'A')
        {
            tmp->p_type.cannon = false;
            tmp->g = true;
            tmp->p_type.hp = 2;
            playerCoord = std::make_pair(ycount, xcount);
        }
        else if (e_type == 'S')
        {
            tmp->e_type.atkdir = line[2];
            tmp->b = true;
        }
        else if (e_type == 'F')
        {
            tmp->e_type.atkdir = line[2];
            tmp->e_type.mvm = 2;
            tmp->e_type.scorp = false;
            tmp->b = true;
        }
        xcount += 1;
    }
    while (commands >> line)
    {
        if (line == "move")
        {
            
            commands >> line;
            if (line == "up" && playerCoord.first != 0 && map[playerCoord.first - 1][playerCoord.second].t_type.standable)
            {
                playerCoord.first = playerCoord.first - 1;
                map[playerCoord.first][playerCoord.second].p_type = map[playerCoord.first + 1][playerCoord.second].p_type;
                map[playerCoord.first + 1][playerCoord.second].g = false;
            }
            else if (line == "down" && playerCoord.first != 7 && map[playerCoord.first + 1][playerCoord.second].t_type.standable)
            {
                playerCoord.first = playerCoord.first + 1;
                map[playerCoord.first][playerCoord.second].p_type = map[playerCoord.first - 1][playerCoord.second].p_type;
                map[playerCoord.first - 1][playerCoord.second].g = false;
            }
            else if (line == "left" && playerCoord.second != 0 && map[playerCoord.first][playerCoord.second - 1].t_type.standable)
            {
                playerCoord.second = playerCoord.second - 1;
                map[playerCoord.first][playerCoord.second].p_type = map[playerCoord.first][playerCoord.second + 1].p_type;
                map[playerCoord.first][playerCoord.second + 1].g = false;
            }
            else if (line == "right" && playerCoord.second != 7 && map[playerCoord.first][playerCoord.second + 1].t_type.standable)
            {
                playerCoord.second = playerCoord.second + 1;
                map[playerCoord.first][playerCoord.second].p_type = map[playerCoord.first][playerCoord.second - 1].p_type;
                map[playerCoord.first][playerCoord.second - 1].g = false;
            }
            map[playerCoord.first][playerCoord.second].g = true;
        }
        else if (line == "attack")
        {
            commands >> line;
            if (line[0] == '(')
            {
                int y = line[1] - '0';
                int x = line[3] - '0';
                
                if (!(x != playerCoord.first && y != playerCoord.second))
                {
                    if (map[x][y].t_type.terrType == 'B')
                        totalScore--;
                    if (map[x][y].b)
                        totalScore++;
                    if (x > 1 && map[x - 1][y].b)
                    {
                        Grid *tmp = &map[x - 1][y];
                        if (map[x - 2][y].t_type.standable)
                        {
                            map[x - 2][y].e_type = tmp->e_type;
                            map[x - 2][y].b = true;
                            tmp->b = false;
                        }
                        else
                            totalScore++;
                    }
                    if (x < 6 && map[x + 1][y].b)
                    {   
                        Grid *tmp = &map[x + 1][y];
                        if (map[x + 2][y].t_type.standable)
                        {
                            map[x + 2][y].e_type = tmp->e_type;
                            map[x + 2][y].b = true;
                            tmp->b = false;
                        }
                        else{
                            totalScore++;
                        }
                    }
                    if (x > 1 && map[x][y - 1].b)
                    {
                        Grid *tmp = &map[x][y - 1];
                        if (map[x][y - 2].t_type.standable)
                        {
                            map[x][y - 2].e_type = tmp->e_type;
                            map[x][y - 2].b = true;
                            tmp->b = false;
                        }
                        else
                            totalScore++;
                    }
                    if (y < 6 && map[x][y + 1].b)
                    {
                        Grid *tmp = &map[x][y + 1];
                        if (map[x][y + 2].t_type.standable)
                        {
                            map[x][y + 2].e_type = tmp->e_type;
                            map[x][y + 2].b = true;
                            tmp->b = false;
                        }
                        else
                            totalScore++;
                    }
                }
            }
            else
            {
                commands >> line;
                if (line[0] == 'u' && playerCoord.second != 0)
                {
                    Grid *tmp = &map[playerCoord.first][playerCoord.second - 1];
                    if (tmp->b)
                    {
                        totalScore++;
                        if (playerCoord.second != 1)
                        {
                            if (map[playerCoord.first][playerCoord.second - 2].t_type.standable){
                                map[playerCoord.first][playerCoord.second - 2].e_type = tmp->e_type;
                                map[playerCoord.first][playerCoord.second - 2].b = true;
                                tmp->b = false;
                            }
                            else{
                                totalScore++;
                            }
                        }
                    }
                }
                else if (line[0] == 'd' && playerCoord.second != 7)
                {
                    Grid *tmp = &map[playerCoord.first][playerCoord.second + 1];
                    if (tmp->b)
                    {
                        totalScore++;
                        if (playerCoord.second != 6)
                        {
                            if (map[playerCoord.first][playerCoord.second + 2].t_type.standable){
                                map[playerCoord.first][playerCoord.second + 2].e_type = tmp->e_type;
                                map[playerCoord.first][playerCoord.second + 2].b = true;
                                tmp->b = false;
                            }
                            else{
                                totalScore++;
                            }
                        }
                    }
                }
                else if (line[0] == 'l' && playerCoord.first != 0)
                {
                    Grid *tmp = &map[playerCoord.first - 1][playerCoord.second];
                    if (tmp->b)
                    {
                        totalScore++;
                        if (playerCoord.first != 1)
                        {
                            if (map[playerCoord.first - 2][playerCoord.second].t_type.standable){
                                map[playerCoord.first - 2][playerCoord.second].e_type = tmp->e_type;
                                map[playerCoord.first - 2][playerCoord.second].b = true;
                                tmp->b = false;
                            }
                            else{
                                totalScore++;
                            }
                        }
                    }
                }
                else if (line[0] == 'r' && playerCoord.first != 7)
                {
                    Grid *tmp = &map[playerCoord.first + 1][playerCoord.second];
                    if (tmp->b)
                    {
                        totalScore++;
                        if (playerCoord.first != 6)
                        {
                            if (map[playerCoord.first + 2][playerCoord.second].t_type.standable){
                                map[playerCoord.first + 2][playerCoord.second].e_type = tmp->e_type;
                                map[playerCoord.first + 2][playerCoord.second].b = true;
                                tmp->b = false;
                            }
                            else{
                                totalScore++;
                            }
                        }
                    }
                }
            }
        }
    }
    std::ofstream output("out.txt");
    for (int i = 0; i < (int)map.size(); ++i)
    {
        output << '-';
        for (int j = 0; j < 8; ++j)
        {
            output << "---";
        }
        output << std::endl;
        output << "|";
        for (int j = 0; j < (int)map[i].size(); ++j)
        {
            Grid *curr = &map[i][j];
            output << curr->t_type.terrType;
            if (curr->g)
            {
                output << "C|";
            }
            else if (curr->b)
            {
                if(curr->e_type.scorp){
                    char atkdir = curr->e_type.atkdir;
                    output << 'S';
                    if(atkdir == 'l' && j != 0){
                        if(map[i][j-1].t_type.terrType == 'B')
                            totalScore--;
                        else if(map[i][j-1].g)
                            totalScore--;
                        output << '<';
                    }
                    else if(atkdir == 'r' && j != 7){
                        if(map[i][j+1].t_type.terrType == 'B')
                            totalScore--;
                        else if(map[i][j+1].g)
                            totalScore--;
                        output << '>';
                    }
                    else if(atkdir == 'u' && i != 0){
                        if(map[i - 1][j].t_type.terrType == 'B')
                            totalScore--;
                        else if(map[i - 1][j].g)
                            totalScore--;
                        output<< '^';
                    }
                    else if(atkdir == 'd' && i != 7){
                        if(map[i + 1][j].t_type.terrType == 'B')
                            totalScore--;
                        else if(map[i + 1][j].g)
                            totalScore--;
                        output << 'v';
                    }
                }
                else{
                    output << 'F';
                    if(curr->e_type.atkdir == 'l' && j != 0){
                        for(int k = j - 1; k > 0; k--){
                            if(map[i][k].g || map[i][k].t_type.terrType == 'B'){
                                totalScore--;
                                break;
                            }
                            else if(map[i][k].t_type.terrType == 'M')
                                break;
                            else if(map[i][k].b){
                                totalScore++;
                                break;
                            }
                        }
                        output << '<';
                    }
                    else if(curr->e_type.atkdir == 'r' && j != 7){
                        for(int k = j + 1; k < 8; k++){
                            if(map[i][k].g || map[i][k].t_type.terrType == 'B'){
                                totalScore--;
                                break;
                            }
                            else if(map[i][k].t_type.terrType == 'M')
                                break;
                            else if(map[i][k].b){
                                totalScore++;
                                break;
                            }
                        }
                        output << '>';
                    }
                    else if(curr->e_type.atkdir == 'u' && i != 0){
                        for(int k = i - 1; k >= 0; k--){
                            if(map[k][j].g || map[k][j].t_type.terrType == 'B'){
                                totalScore--;
                                break;
                            }
                            else if(map[k][j].t_type.terrType == 'M')
                                break;
                            else if(map[k][j].b){
                                totalScore++;
                                break;
                            }
                        }
                        output << '^';
                    }
                    else if(curr->e_type.atkdir == 'd' && i != 7){
                        for(int k = i + 1; k < 8; k++){
                            if(map[k][j].g || map[k][j].t_type.terrType == 'B'){
                                totalScore--;
                                break;
                            }
                            else if(map[k][j].t_type.terrType == 'M')
                                break;
                            else if(map[k][j].b){
                                totalScore++;
                                break;
                            }
                        }
                        output << 'v';
                    }
                }
            }
            else{
                output << "X|";
            }
        }
        output << std::endl;
    }
    output << totalScore;
}