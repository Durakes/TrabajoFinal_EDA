//#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
    int opcion;
    bool repetir = true;
    
    do {
        system("cls");
        
        cout << "\n\nMenu de navegacion" << endl;
        cout << "1. Usuarios" << endl;
        cout << "2. Canciones" << endl;
        cout << "3. Albums" << endl;
        cout << "0. SALIR" << endl;
        
        cout << "\nIngrese una opcion: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1:
                     
                system("pause>nul"); 
                break;
                
            case 2:
   
                system("pause>nul"); 
                break;
                
            case 3:
       
                system("pause>nul");             
                break;
            
            case 0:
            	repetir = false;
            	break;
        }        
    } while (repetir);
	 
    return 0;
}

using namespace std;

class Usuario{
    private:
        int cod_usuario;
        string nom_usuario;
    public: 
        Usuario(int,string);
        void leer();
};

Usuario::Usuario(int _cod_usuario,string _nom_usuario){
    cod_usuario = _cod_usuario;
    nom_usuario = _nom_usuario;
};

void Usuario::leer(){
    cout<<"Lista de usuarios: \n\n";
    cout<<cod_usuario<<": "<<nom_usuario<<endl;
}

class Artista{
    private:
        int cod_artista;
        string nom_artista;
    public:
        Artista(int,string);
};
Artista::Artista(int _cod_artista,std::string _nom_artista){
    cod_artista = _cod_artista;
    nom_artista = _nom_artista;
}

class Cancion{
    private:
        int cod_cancion;
        string nom_cancion;
    public:
        Cancion(int,string);
        void lista();
};

Cancion::Cancion(int __cod_cancion,std::string __nom_cancion){
    cod_cancion = __cod_cancion;
    nom_cancion = __nom_cancion;
}
    
void Cancion::lista(){
    cout<<"Lista de canciones: \n\n";
    cout<<cod_cancion<<": "<<nom_cancion<<endl;
}