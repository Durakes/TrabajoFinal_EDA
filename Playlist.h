#ifndef __PLAYLIST_H__
#define __PLAYLIST_H__
#include<string>
#include<iostream>
using namespace std;

class Playlist
{
    private:
        int codigo;
        string nombrePlaylist;
        int codUsuario;
    public:
        Playlist(int codigo, string nombre, int codUsuario)
        {
            this->codigo = codigo;
            this->nombrePlaylist = nombre;
            this->codUsuario = codUsuario;
        }
        
        Playlist(){}

        int getCodigo() {return codigo;}
        void setCodigo(int codigo) {this->codigo = codigo;}

        string getNombre()  {return nombrePlaylist;}
        void setNombre(string nombre) {this->nombrePlaylist = nombre;}

        int getUsuario(){return codUsuario;}
        void setUsuario(int codigoUsuario) {codUsuario = codigoUsuario;}

        /*void agregarCancion(int cod){VectorCodigo.push_back(cod);}*/
};
#endif