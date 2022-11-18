#ifndef __GENERO_H__
#define __GENERO_H__
#include <iostream>
using namespace std;

class Genero
{
    private:
        int idGenero;
        string nombreGenero;
    public:
        Genero(int id, string nombre)
        {
            this->idGenero = id;
            this->nombreGenero = nombre;
        }
        Genero(){}

        int getCodigoGenero() {return idGenero;}
        void setCodigoGenero(int codigo)    {this->idGenero = codigo;}

        string getNombreGenero() {return nombreGenero;}
        void setNombreGenero(string nombre) {this->nombreGenero = nombre;}

};
#endif
