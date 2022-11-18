#ifndef __CANCION_H__
#define __CANCION_H__

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

class Cancion
{
    private:
        int codigo;
        string titulo;
        int codGenero;

    public:
        Cancion(){}
        Cancion(int codigo, string titulo, int genero)
        {
            this->codigo = codigo;
            this->titulo = titulo;
            this->codGenero = genero;
        }

        int getCodigo(){ return codigo; }
        void setCodigo(int codigo){ this->codigo = codigo; }
        
        string getNombre(){ return titulo; }
        void setNombre(string titulo){ this->titulo = titulo; }

        int getGenero() {return codGenero;}
        void setGenero(int genero)  {this->codGenero = genero;}

};
#endif
