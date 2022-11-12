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
        /*string autor;
        int codAutor;*/
        int codGenero;

    public:
        Cancion(){}
        /*Cancion(int codigo, string titulo, string autor, int codAutor, int genero)
        {
            this->codigo = codigo;
            this->titulo = titulo;
            this->autor = autor;
            this->codAutor = codAutor;
            this->codGenero = genero;
        }*/
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
        
        /*string getAutor(){ return autor; }
        void setAutor(string autor){ this->autor = autor; }
        
        int getCodigoAutor() {return codAutor;}
        void setCodigoAutor(int codAut) { this->codAutor = codAut;}*/

        int getGenero() {return codGenero;}
        void setGenero(int genero)  {this->codGenero = genero;}

        /*string getDatosCompletos()
        {
            string tiempo = to_string(floor(Duracion * 0.016)) + ":";

            if(Duracion % 60 < 10)
            {
                tiempo += "0" + to_string(Duracion % 60);
            }else
            {
                tiempo += to_string(Duracion % 60);
            }

            return (titulo + " - " + autor + " " + tiempo);
        }*/

        /*int obtenerCodigo()
        {
            int filas = 1;
            ifstream archivo("../docs/Canciones.csv");
            string linea;
            while (getline(archivo, linea))
            filas++;
            archivo.close();
            return filas;
        }*/

};
#endif
