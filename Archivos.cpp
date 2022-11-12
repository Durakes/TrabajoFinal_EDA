#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include "Grafos.h"
#include "Playlist.h"
#include "Cancion.h"
#include "Genero.h"

void cargarDatos(Playlist obj, vector<Playlist> *objs)
{
    try
    {
        string linea;
        size_t posicionFinal;
        fstream archivo;

        archivo.open(R"(..\db\Playlist.csv)", ios :: in);
        if(archivo.is_open())
        {
            while (!archivo.eof())
            {
                while (getline(archivo, linea))
                {
                    vector<string> temporal;
                    while ((posicionFinal = linea.find(";")) != string::npos)
                        {
                            temporal.push_back(linea.substr(0, posicionFinal));
                        linea.erase(0, posicionFinal+1);
                    }
                    //T obj;
                    Playlist playlist;
                    playlist.setCodigo(stoi(temporal[0]));
                    playlist.setNombre(temporal[1]);
                    playlist.setUsuario(stoi(temporal[2]));
                    objs->push_back(obj);
                }
            }
        }
        archivo.close();
    }catch(exception e)
    {
        cout << "Ocurrio un error al leer el archivo!!!";
    }
}

void cargarCancionesPlaylist(int idPlaylist, vector<int> *canciones)
{
    try
    {
        string linea;
        size_t posicionFinal;
        fstream archivo;

        archivo.open(R"(..\db\PlaylistCancion.csv)", ios :: in);
        if(archivo.is_open())
        {
            while (!archivo.eof())
            {
                while (getline(archivo, linea))
                {
                    vector<string> temporal;
                    while ((posicionFinal = linea.find(";")) != string::npos)
                    {
                        temporal.push_back(linea.substr(0, posicionFinal));
                        linea.erase(0, posicionFinal+1);
                    }
                    //T obj;
                    if(stoi(temporal[0]) == idPlaylist)
                    {
                        canciones->push_back(stoi(temporal[1]));
                    }
                }
            }
        }
        archivo.close();
    }catch(exception e)
    {
        cout << "Ocurrio un error al leer el archivo!!!";
    }
}

void cargarCanciones(vector<Cancion> *canciones)
{
    try
    {
        string linea;
        size_t posicionFinal;
        fstream archivo;

        archivo.open(R"(..\db\Canciones.csv)", ios :: in);
        if(archivo.is_open())
        {
            while (!archivo.eof())
            {
                while (getline(archivo, linea))
                {
                    vector<string> temporal;
                    while ((posicionFinal = linea.find(";")) != string::npos)
                    {
                        temporal.push_back(linea.substr(0, posicionFinal));
                        linea.erase(0, posicionFinal+1);
                    }
                    
                    Cancion cancion;
                    cancion.setCodigo(stoi(temporal[0]));
                    cancion.setNombre(temporal[1]);
                    cancion.setGenero(stoi(temporal[2]));
                    canciones->push_back(cancion);
                }
            }
        }
        archivo.close();
    }catch(exception e)
    {
        cout << "Ocurrio un error al leer el archivo!!!";
    }
}

void cargarCancionesDetalle(vector<int> idCanciones, vector<Cancion> *canciones)
{
    try
    {
        string linea;
        size_t posicionFinal;
        fstream archivo;

        archivo.open(R"(..\db\Canciones.csv)", ios :: in);
        if(archivo.is_open())
        {
            while (!archivo.eof())
            {
                int idTemp = 0;
                while (getline(archivo, linea))
                {
                    vector<string> temporal;
                    while ((posicionFinal = linea.find(";")) != string::npos)
                    {
                        temporal.push_back(linea.substr(0, posicionFinal));
                        linea.erase(0, posicionFinal+1);
                    }
                    if(idCanciones[idTemp] == stoi(temporal[0]))
                    {
                        Cancion cancion;
                        cancion.setCodigo(stoi(temporal[0]));
                        cancion.setNombre(temporal[1]);
                        cancion.setGenero(stoi(temporal[2]));
                        canciones->push_back(cancion);
                        idTemp++;
                    }
                }
            }
        }
        archivo.close();
    }catch(exception e)
    {
        cout << "Ocurrio un error al leer el archivo!!!";
    }
}

void cargarGeneros(vector<Genero> *generos)
{
    try
    {
        string linea;
        size_t posicionFinal;
        fstream archivo;

        archivo.open(R"(..\db\Generos.csv)", ios :: in);
        if(archivo.is_open())
        {
            while (!archivo.eof())
            {
                while (getline(archivo, linea))
                {
                    vector<string> temporal;
                    while ((posicionFinal = linea.find(";")) != string::npos)
                    {
                        temporal.push_back(linea.substr(0, posicionFinal));
                        linea.erase(0, posicionFinal+1);
                    }
                    
                    Genero genero;
                    
                    genero.setCodigoGenero(stoi(temporal[0]));
                    genero.setNombreGenero(temporal[1]);
                    generos->push_back(genero);
                }
            }
        }
        //cout << generos->size() << endl;
        archivo.close();
        
    }catch(exception e)
    {
        cout << "Ocurrio un error al leer el archivo!!!";
    }
}