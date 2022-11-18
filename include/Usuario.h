#ifndef __USUARIO_H__
#define __USUARIO_H__
#include <iostream>
#include <cstring>
using namespace std;
class Usuario
{
    protected:
        int codigo;
        string nombreUsuario;
        string contrasena;
        
    public:
        Usuario(){}
        Usuario(int codigo,string nombreUsuario, string contrasena)
        {
            this->codigo = codigo;
            this->nombreUsuario = nombreUsuario;
            this->contrasena = contrasena;
        }

        int getCodigo()    {return codigo;}
        void setCodigo(int codigo)   {this->codigo = codigo;}

        string getNombreUsuario()    {return nombreUsuario;}
        void setNombreUsuario(string nombreUsuario) {this->nombreUsuario = nombreUsuario;}

        string getContrasena()    {return contrasena;}
        void setContrasena(string contrasena) {this->contrasena = contrasena;}

};
#endif
