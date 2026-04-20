#include "ColorMap.h"
#include <iostream>
#include <unordered_set>
#include "PairHash.h"

/*
red 31
green 32
yellow 33
blue 34
pink 35
white 37
*/

ColorMap::ColorMap(const Map& rhs):Map(rhs){}

//Mapa simple solo con terreno
void ColorMap::print() const
{
    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++)
        {
            if(_map[i][j] == 1)
            {
                int value = _map[i][j];
                std::cout << "\033[1;34m" << value << " \033[0m";  //azul
            }
            else
            {
                int value = _map[i][j];
                int color;

                if(value <= 3) color = 33;      // amarillo (bajo)
                else if(value <= 5) color = 35; // rosado (medio)
                else color = 31;                // rojo (alto)

                std::cout << "\033[1;" << color << "m" 
                          << value << " \033[0m";
            }
        }
        std::cout<<std::endl;
    }
    std::cout<<"\033[1;37m\n"; 
}

//Mapa con camino
void ColorMap::print(std::vector<std::pair<int,int>> path) const
{
    /*auto __map=_map;

    __map[path[0].first][path[0].second]=2;

    for(int i=1;i<(int)path.size()-1;i++)
    {
         __map[path[i].first][path[i].second]=4;
    }

    __map[path[path.size()-1].first][path[path.size()-1].second]=3;

    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++)
        {
            //std::cout<<"\033[1;" << colors[__map[i][j]] << "m"<<__map[i][j]<<" ";
            int value = __map[i][j];

            if(value < 0 || value >= (int)colors.size()){
                std::cout << value << " ";
            } 
            else 
            {
                std::cout << "\033[1;" << colors[value] << "m" << value << " ";
            }
        }
        std::cout<<std::endl;
    }
    std::cout<< "\033[1;37m\n";*/

    std::unordered_set<std::pair<int,int>> pathSet(path.begin(), path.end());

    auto start = path.front();
    auto goal = path.back();

    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++)
        {
            std::pair<int,int> pos = {i,j};

            if(i == start.first && j == start.second)
            {
                std::cout << "\033[1;34mS \033[0m";     //Blaco
            }
            else if(i == goal.first && j == goal.second)
            {
                std::cout << "\033[1;34mG \033[0m";     //Blanco
            }
            else if(pathSet.count(pos))
            {
                int value = _map[i][j];
                std::cout << "\033[1;32m" << value << " \033[0m";  //verde
            }
            else if(_map[i][j] == 1)
            {
                int value = _map[i][j];
                std::cout << "\033[1;34m" << value << " \033[0m";  //azul
            }
            else
            {
                int value = _map[i][j];
                int color = 37;

                if(value <= 3) color = 33;      //Amarilla (bajo)
                else if(value <= 5) color = 35; //Rosado (medio)
                else color = 31;                //Roja (alta)

                std::cout << "\033[1;" << color << "m" << value << " \033[0m";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

// 🔹 SOLO inicio y meta (para preview)
void ColorMap::printStartGoal(std::pair<int,int> start, std::pair<int,int> goal) const
{
    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++)
        {
            if(i == start.first && j == start.second)
                std::cout << "S ";
            else if(i == goal.first && j == goal.second)
                std::cout << "G ";
            else if(_map[i][j] == 1)
            {   
                int value = _map[i][j];
                std::cout << "\033[1;34m" << value << " \033[0m";  //azul
            }
            else
                std::cout << ". ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}