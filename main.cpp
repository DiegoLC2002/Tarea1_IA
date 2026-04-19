#include "Map.h"
#include "Search.h"
#include "ColorMap.h"
#include <cassert>
#include <iostream>

#include <fstream>  //Permite trabajar con archivos (leer y escribir).
#include <stdexcept>    //Permite manejar errores (excepciones) en C++.

int main(int argc, char *argv[]){

    //Verify that the amount of arguments is correct
    //6 arguments: program name, map file, x1, y1, x2, y2

    ///1) verificar cantidad de argumentos
    if(argc != 6 && argc != 7)
    {
        std::cerr << "Formato correcto: " << argv[0] << "<mapa> x1 y1 x2 y2\n";
        std::cerr << "Formato correcto (para tests)): " << argv[0] << "<mapa> x1 y1 x2 y2 test\n";
        return 1;
    }

    bool testMode = (argc == 7);

    ///2) obtener nombre del archivo
    std::string fileMapName = argv[1];

    ///2.2) Comprobar que el archivo existe
    std::ifstream file(fileMapName);    //Intenta abrir el archivo
    if(!file)
    {
        std::cerr << "Error: no se pudo abrir el archivo\n";
        return 1;
    }
    file.close();

    ///3) Convertir y Comprobar coordenadas
    int x1, y1, x2, y2;
    try
    {
        //Intenta hacer algo
        x1 = std::stoi(argv[2]);
        y1 = std::stoi(argv[3]);
        x2 = std::stoi(argv[4]);
        y2 = std::stoi(argv[5]);
    }
    catch(const std::exception& e)
    {
        //Si no funciona haz esto
        std::cerr << "Error: Coordenada ingresada es incorrecta. Las coordenadas deben ser un numero entero.\n";
        return 1;
    }

    ///4) Cargar Mapa con clase Map
    Map map(fileMapName);

    ///4.2) Validar coordenadas dentro del mapa
    if(x1 < 0 || x1 >= map.h || y1 < 0 || y1 >= map.w ||
       x2 < 0 || x2 >= map.h || y2 < 0 || y2 >= map.w)
       {
        std::cerr << "Error: coordenadas fuera de rango.\n";
        return 1;
        }

    ///5) Mostrar mapa    
    ColorMap colorMap(map);
    
    //Modo experimento para multiples Runs
    if(testMode)
    {
        int runs = 20; //numero de pruebas realizadas (10 - 30)

        std::cout << "\n===== MODO EXPERIMENTO =====\n";

        for(int i = 0; i < runs; i++)
        {
            std::cout << "\nRun #" << i+1 << "\n";

            Search::BFS(map,{x1,y1},{x2,y2});
            Search::greedyBFS(map,{x1,y1},{x2,y2});
            Search::AStar(map,{x1,y1},{x2,y2});
            Search::WAStar(map,{x1,y1},{x2,y2}, 1.5f); // prueba distintos w
        }

        return 0;
    }

    //Modo normal
    colorMap.print();
    //std::cout << "\nMapa (Inicio = S, Meta = G):\n";
    //colorMap.printStartGoal({x1,y1}, {x2,y2});


    //6)Ejecutar Metodo de busqueda
    int opcionBFS;

    std::cout << "Seleccione metodo de busqueda de caminos:\n";
    std::cout << "1.- BFS\n";
    std::cout << "2.- BFS Greedy\n";
    std::cout << "3.- A*\n";
    std::cout << "4.- Weighted A*\n";
    std::cout << "Opcion: ";
    std::cin >> opcionBFS;

    std::vector<std::pair<int,int>> path;

    switch(opcionBFS)
    {
        case 1: path = Search::BFS(map,{x1,y1},{x2,y2}); //Calculate path distance
                break;
            
        case 2: path = Search::greedyBFS(map,{x1,y1},{x2,y2});
                break;

        case 3: path = Search::AStar(map,{x1,y1},{x2,y2});
                break;

        case 4: float w;
                std::cout << "Ingrese peso (ej: 1.0 - 2.0): ";
                std::cin >> w;

                path = Search::WAStar(map,{x1,y1},{x2,y2}, w);
                break;
            
        default: std::cout<<"Opcion invalida\n";
                 return 1;
    }


    //Verificar que el camino no este vacio
    if(path.empty())
    {
        std::cout << "No se encontro camino\n";
        return 0;
    }

    //Mensaje debug tamaño camino
    std::cout << "Path size: " << path.size() << std::endl;

    for(auto p : path)
    {
        std::cout << "(" << p.first << "," << p.second << ") ";
    }
    std::cout << std::endl;

    //Tarea 6: Imprimir distancia
    std::cout << "Distancia del Camino:" << path.size() - 1 << std::endl;

    //Tarea 7:Imprimir mapa
    colorMap.print(path);       //Print path distance
    
    return 0;
}

/*
Para compilar ingresa en WSL: make

Coordenadas de prueba al ajecutar:
    *Nota: si se ingresa un septimo argumento, se ingresa el modo test, ej: ./busqueda mapa.txt 1 1 5 4 test*
    *por otro lado si se ingresan 6 argumentos se ingresa al menu de metodos de busqueda, ej: ./busqueda mapa.txt 1 1 5 4 *


*/