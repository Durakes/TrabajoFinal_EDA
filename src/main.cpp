#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <memory>
#include <functional>
#include <map>
#include <cmath>
#include <random>
#include <conio.h>
#include "../include/Usuario.h"
#include "../include/Playlist.h"
#include "../include/Cancion.h"
#include "../include/Grafo.h"
#include "../include/Genero.h"
#include "../include/ArbolAVL.h"
using namespace std;

Grafo grafoGeneros()
{
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

    return grafoGenero;
}

bool randomBool()
{
    static auto gen = std::bind(std::uniform_int_distribution<>(0,1),std::default_random_engine());
    return gen();
}

bool existeCancion(int cod, vector<Cancion> *canciones)
{
    for(Cancion cancion: canciones[0])
    {
        if(cancion.getCodigo() == cod)
            return true;
    }
    return false;
}

void recomendarRandom(map<int,int> generosMap, float tot, vector<Cancion> cancionesTot, int index, vector<Cancion>* ultVector)
{
    int nuevaPlaylistsize = 20;
    float canciones = ceil((generosMap[index] / tot) * nuevaPlaylistsize);
    int i = 0;
    while(i < canciones)
    {
        for(Cancion cancion: cancionesTot)
        {
            if(cancion.getGenero() == index && randomBool())
            {
                if(existeCancion(cancion.getCodigo(), ultVector))
                    continue;
                else
                {
                    ultVector[0].push_back(cancion);
                    i++;
                    break;
                }
            }
        }
    }
}


void generarPlaylist(int cod, vector<Cancion> playlistEsp, vector<Cancion> cancionesTotales)
{
    std::system("cls");
    int cantidadGeneros = 13;
    Grafo grafoGenero = grafoGeneros();
    vector<Genero> generos;
    vector<Cancion> nuevaPlaylist;
    nuevaPlaylist.clear();
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
                    generos.push_back(genero);
                }
            }
        }
        archivo.close();
        
    }catch(exception e)
    {
        cout << "Ocurrio un error al leer el archivo!!!";
    }

    map<int,int> generoMap;
    map<int,int> generoFinal;
    for(int i = 0; i < generos.size(); i++)
    {
        generoMap[generos[i].getCodigoGenero()] = 0;
        generoFinal[generos[i].getCodigoGenero()] = 0;
    }

    for(Cancion cancion : playlistEsp)
    {
        generoMap[cancion.getGenero()]++;
    }

    for(int i = 0; i < cantidadGeneros ; i++)
    {
        if(generoMap[i]!=0)
        {
            for(int j = 0; j < cantidadGeneros ; j++)
            {
                if(grafoGenero.verificarArista(i,j))
                {
                    generoFinal[j]++;
                }
            }
            generoFinal[i] += generoMap[i];
        }
    }

    map<int,int> ::iterator itr;
    int totalPlaylistNueva = 0;
    for(itr = generoFinal.begin(); itr != generoFinal.end(); itr++)
    {
        if(itr->second != 0)
        {
            totalPlaylistNueva += itr->second;
        }
    }

    vector<Cancion> cancionesRecomendadas;
    for(int i = 0; i < cantidadGeneros; i++)
    {
        if(generoFinal[i] != 0)
        {
            for(Cancion cancion: cancionesTotales)
            {
                if(cancion.getGenero() == i)
                {
                    cancionesRecomendadas.push_back(cancion);
                }
            }
        }
    }

    for(int i = 0; i < cancionesRecomendadas.size(); i++)
    {
        for(Cancion cancion: playlistEsp)
        {
            if(cancion.getCodigo() == cancionesRecomendadas[i].getCodigo())
            {
                cancionesRecomendadas.erase(cancionesRecomendadas.begin() + i);
            }
        }
    }

    vector<Cancion> cancionesFinal;
    for(int i = 0; i < generoFinal.size(); i++)
    {
        recomendarRandom(generoFinal,totalPlaylistNueva, cancionesRecomendadas, i, &cancionesFinal);
    }

    for(Cancion cancion:cancionesFinal)
    {
        cout << cancion.getNombre() << endl;
    }
    std::system("pause");
}

void detallePlaylist(int codUsuario, Playlist playlistUsuario)
{
    std::system("cls");
    cout << playlistUsuario.getNombre() << endl;

    vector<int> codCanciones;
    vector<Cancion> cancionesPlay;
    vector<Cancion> cancionesDet;

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
                    
                    if(stoi(temporal[0]) == playlistUsuario.getCodigo())
                    {
                        codCanciones.push_back(stoi(temporal[1]));
                    }
                }
            }
        }
        archivo.close();
    }catch(exception e)
    {
        cout << "Ocurrio un error al leer el archivo!";
    }

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

                    cancionesPlay.push_back(cancion);
                }
            }
        }
        archivo.close();
    }catch(exception e)
    {
        cout << "Ocurrio un error al leer el archivo!";
    }

    int index = 0;
    for(Cancion cancion: cancionesPlay)
    {
        if(cancion.getCodigo() == codCanciones[index])
        {
            cancionesDet.push_back(cancion);
            index++;
        }
    }

    for(int i = 0; i < cancionesDet.size(); i++)
    {
        cout << "Nombre: " << cancionesDet[i].getNombre() << "\t" << "Genero: " << cancionesDet[i].getGenero() << endl;
    }

    int respuesta;
    cout << "Para generar una playlist nueva presione 1" << endl;
    cout << "Digite la opcion que desea > \t"; cin >> respuesta; cin.ignore();

    if(respuesta == 1)
    {
        generarPlaylist(codUsuario, cancionesDet, cancionesPlay);
    }
}

void mostrarPlaylist(int cod, vector<Playlist> *playlists)
{
    std::system("cls");
    int numero = 1;
    vector<Playlist> playlistsUsu;
    vector<int> codigos;

    for(Playlist play:playlists[0])
    {
        if(play.getUsuario() == cod)
        {
            playlistsUsu.push_back(play);
        }
    }
    
    for(int i = 0; i < playlistsUsu.size(); i++)
	{
        cout << "Nro. Playlist: " << numero << "\t" << "Nombre: " << playlistsUsu[i].getNombre() << endl;
		codigos.push_back(numero);
		numero++;
	}

    int respuesta;
    cout << "Ingrese el numero de playlist que quiere ingresar" << endl;
    cout << "Si desea volver atras escriba 0 > "; cin >> respuesta; cin.ignore();

    if(respuesta != 0)
    {
        detallePlaylist(cod, playlistsUsu[respuesta-1]);
    }
}

void crearPlaylist(int cod, vector<Playlist> *playlists)
{
    std::system("cls");
    string nombrePlaylist;
    cout << "Ingrese el nombre de la playlist > " << endl;
    getline(cin, nombrePlaylist);

    Playlist nuevaPlaylist = Playlist(playlists->size() + 1,nombrePlaylist,cod);

    string nuevoRegistro = to_string(nuevaPlaylist.getCodigo()) + ";" + nuevaPlaylist.getNombre() + ";" + to_string(nuevaPlaylist.getUsuario()) + ";";
    try
    {
        fstream archivo;
        archivo.open(R"(..\db\Playlist.csv)", ios :: app);
        if(archivo.is_open())
        {
            archivo << nuevoRegistro << endl;
            archivo.close();
        }

    }catch(exception e)
    {
        cout << "Ocurrio un error al grabar el archivo!!!";
    }
    
    cout << "Se registro la nueva playlist exitosamente! " << endl;
    cout << std::system("pause");
}

void menuPlaylist(int cod)
{
    std::system("cls");
    int opcion;
    vector<Playlist> vectorPlaylist;
    Playlist playlist;
    cout << "Playlist" << endl;
	cout <<	"Crear una playlist \t [1]" << endl;
	cout << "Mostrar tus playlist \t [2]" << endl;
	cout << "Atras \t \t \t [3]" << endl;				
	cout << "Ingrese la opcion que desea > "; cin >> opcion; cin.ignore();

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
                    playlist.setCodigo(stoi(temporal[0]));
                    playlist.setNombre(temporal[1]);
                    playlist.setUsuario(stoi(temporal[2]));
                    vectorPlaylist.push_back(playlist);
                }
            }
        }
        archivo.close();
    }catch(exception e)
    {
        cout << "Ocurrio un error al leer el archivo!!!";
    }

    switch (opcion)
    {
    case 1:
        crearPlaylist(cod,&vectorPlaylist);
        break;
    case 2:
        mostrarPlaylist(cod,&vectorPlaylist);
        menuPlaylist(cod);
        break;
    case 3:
        std::system("cls");
        break;
    default:
        cout << "Ingrese una opcion correcta!!" << endl;
        std::system("pause");
        menuPlaylist(cod);
        break;
    }
}

void buscarCancion(int cod)
{
    std::system("cls");
    string cancionBuscar;
    cout << "##### Buscar Cancion #####" << endl;
    cout << "Ingrese el nombre de la cancion a buscar > " << endl;
    getline(cin, cancionBuscar);

    Nodo* raiz = NULL;

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

                    raiz = insertarNodo(raiz,cancion);
                }
            }
        }
        archivo.close();
    }catch(exception e)
    {
        cout << "Ocurrio un error al leer el archivo!";
    }

    Cancion *cancionEncontrada = buscarArbol(raiz, cancionBuscar);

    if(cancionEncontrada != NULL)
    {
        std::system("cls");
        cout << "Cancion encontrada " << endl;
        cout << "Nombre > \t" << cancionEncontrada->getNombre() << "\t sGenero > \t" << cancionEncontrada->getGenero() << endl;
        std::system("pause");
    }else
    {
        std:system("cls");
        cout << "Cancion no encontrada" << endl;
        std::system("pause");
    }
}

void menuPrincipal(int cod)
{
    std::system("cls");
    int opcion;
    cout << "##### MENU PRINCIPAL #####" << endl;
    cout << "Mostrar Playlist \t [1]" << endl;
    cout << "Buscar Cancion \t \t [2]" << endl;
    cout << "Salir \t \t \t [3]" << endl;
    cout << "Ingrese la opcion que desea > \t"; cin >> opcion; cin.ignore();

    switch (opcion)
    {
    case 1:
        menuPlaylist(cod);
        menuPrincipal(cod);
        break;
    case 2:
        buscarCancion(cod);
        menuPrincipal(cod);
        break;
    case 3:
        std::system("cls");
        exit(0);
        break;
    default:
        cout << "Ingrese una opcion correcta!!" << endl;
        std::system("pause");
        menuPrincipal(cod);
        break;
    }

}

void inicioSesion()
{
    std::system("cls");
    int opcion;
    int ch;
    string nomUsuario;
    string contrasena;
    Usuario usuario;
    vector<Usuario> usuariosTot;
    bool validacion = false;
    cout << "##### INICIO DE SESION #####" << endl;
    cout << "Ingrese su Usuario > "; getline(cin, nomUsuario);
    cout << "Ingrese su Contrasena > "; ch = getch();

    /* Contraseña */
    while (ch != 13) /*13 ASCCI ENTER*/
    {
        if(ch != 8) /*8 BACKSPACE*/
        {
            contrasena.push_back(ch);
            cout << "*";
        }else
        {
            if(contrasena.length() > 0)
            {
                cout << "\b \b";
                contrasena = contrasena.substr(0, contrasena.length() - 1);
            }
        }
        ch = getch();
    }

    /* Leer Usuarios.csv */
    try
    {
        string linea;
        size_t posicionFinal;
        fstream archivo;

        archivo.open(R"(..\db\Usuarios.csv)", ios :: in);
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
                    usuario.setCodigo(stoi(temporal[0]));
                    usuario.setNombreUsuario(temporal[1]);
                    usuario.setContrasena(temporal[2]);
                    usuariosTot.push_back(usuario);
                }
            }
        }
        archivo.close();
    }catch(exception e)
    {
        cout << "Ocurrio un error al leer el archivo!!!";
    }

    for(Usuario u:usuariosTot)
    {
        if(u.getNombreUsuario() == nomUsuario && u.getContrasena() == contrasena)
        {
            validacion = true;
            usuario = u;
            break;
        }
    }

    if(validacion)
        menuPrincipal(usuario.getCodigo());
    else
    {
        std::system("cls");
        cout << "Datos incorrectos, vuelva a intentarlo " << endl;
        std::system("pause");
        inicioSesion();
    }
}

void pantallaInicial()
{
    std::system("cls");
    int opcion;
    cout << "##### BIENVENIDO #####" << endl;
    cout << "Iniciar sesion \t \t [1]" << endl;
    cout << "Presione 1 para continuar > \t"; cin >> opcion; cin.ignore();

    switch (opcion)
    {
    case 1:
        inicioSesion();
        break;
    default:
        std::system("cls");
        cout << "Ingrese una opcion valida " << endl;
        std::system("pause");
        pantallaInicial();
        break;
    }
}

int main()
{
    pantallaInicial();
    return 0;
}