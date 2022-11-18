#include <iostream>
#include "Grafo.h"
#include "Cancion.h"
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include "Playlist.h"
#include "Genero.h"
#include "Archivos.cpp"

using namespace std;
int main()
{
    /* Grafo Generos */
    int cantGeneros = 13;
    Grafo grafoGenero(cantGeneros);
    grafoGenero.agregarArista(0,1);
    grafoGenero.agregarArista(0,2);
    grafoGenero.agregarArista(0,5);
    grafoGenero.agregarArista(0,9);
    grafoGenero.agregarArista(2,3);
    grafoGenero.agregarArista(3,4);
    grafoGenero.agregarArista(9,11);
    grafoGenero.agregarArista(11,10);
    grafoGenero.agregarArista(11,12);
    grafoGenero.agregarArista(5,6);
    grafoGenero.agregarArista(6,7);
    grafoGenero.agregarArista(6,8);

    //grafoGenero.imprimir();
    vector<Playlist> playlists;
    vector<Genero> generosPrueba;
    vector<Cancion> cancionesGeneral;
    vector<Cancion> cancionesPlaylist;
    vector<Cancion> cancionesRecomendadas;
    vector<int> idCanciones;

    //Genero genero;
    Playlist playlist;
    int idPlaylist;
    cargarGeneros(&generosPrueba);
    cargarDatos(playlist, &playlists);
    cargarCancionesPlaylist(0,&idCanciones);
    cargarCanciones(&cancionesGeneral);
    cargarCancionesDetalle(idCanciones, &cancionesPlaylist);

    //int sizeGeneros = generos.size();
    /*for(Genero genero: *generos)
    {
        cout << genero.getNombreGenero() << endl;
    }*/

    map<int,int> generoMap;
    map<int,int> generoFinal;
    for(int i = 0; i < generosPrueba.size(); i++)
    {
        generoMap[generosPrueba[i].getCodigoGenero()] = 0;
        generoFinal[generosPrueba[i].getCodigoGenero()] = 0;
    }

    /*map<int,int> generoMap = {{0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},
                                {7,0},{8,0},{9,0},{10,0},{11,0},{12,0}};*/
    
    for(Cancion cancion : cancionesPlaylist)
    {
        generoMap[cancion.getGenero()]++;
    }
    
    map<int,int> ::iterator itr;

    /*for(itr = generoMap.begin(); itr != generoMap.end(); itr++)
    {
        if(itr->second != 0)
            cout << itr->first << "\t" << itr->second << endl;
    }*/

    /*cout << count(cancionesPlaylist.begin(), cancionesPlaylist.end()) << endl;*/

    /*cout << generosPrueba.size() << endl;
    cout << playlists.size() << endl;
    cout << idCanciones.size() << endl;
    cout << cancionesGeneral.size() << endl;
    cout << cancionesPlaylist.size() << endl;*/

    vector<bool> visitados(cantGeneros,false);

    for(int i = 0; i < cantGeneros ; i++)
    {
        if(generoMap[i]!=0)
        {
            for(int j = 0; j < cantGeneros ; j++)
            {
                if(grafoGenero.verificarArista(i,j))
                {
                    generoFinal[j]++;
                }
            }
            generoFinal[i] += generoMap[i];
        }
    }

    //cout << endl;

    /*for(itr = generoFinal.begin(); itr != generoFinal.end(); itr++)
    {
        if(itr->second != 0)
            cout << itr->first << "\t" << itr->second << endl;
    }*/
    //grafoGenero.bfs(0,&generoMap);

    cout << endl;
    cout << cancionesGeneral.size() << endl;

    /*for(Cancion cancion: cancionesGeneral)
    {
        cout << cancion.getNombre() << endl;
    }*/

    for(int i = 0; i < cantGeneros; i++)
    {
        if(generoFinal[i] != 0)
        {
            for(Cancion cancion: cancionesGeneral)
            {
                if(cancion.getGenero() == i)
                {
                    for(Cancion cancionP: cancionesPlaylist)
                    {
                        if(cancionP.getCodigo() != cancion.getCodigo())
                        {
                            cancionesRecomendadas.push_back(cancion);
                        }
                    }
                }
            }
        }
    }
    

    for(Cancion cancion1:cancionesRecomendadas)
    {
        for(Cancion cancion2:cancionesPlaylist)
        {
            if (cancion1.getCodigo() == cancion2.getCodigo())
                break;
        }

        
    }

    return 0;
}