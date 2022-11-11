#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <conio.h>

using namespace std;


struct nodoCancion{
    int numeroReproducciones;
    string nombreCancion;
    string albumCancion;
    nodoCancion *izq;
    nodoCancion *der;
};

void menu();
nodoCancion *crearNodo(int,string,string);
void insertarNodo(nodoCancion *&, int,string,string);
nodoCancion *song = NULL;
void mostrarCancion(nodoCancion *, int);
void listaReproduccion(nodoCancion *);

int main()
{
    menu();
    getch();
    return 0;
}

void menu(){

    int opcion, valor, contador=0;
    string cancion, album;
    do{
        cout<<"\t MENU \n";
        cout<<"1. Ingresar registro de cancion\n";
        cout<<"2. Mostrar registro de actividad\n";
        cout<<"3. Salir\n";
        cout<<"Opcion: ";
        cin>>opcion;
        
        switch(opcion){
            
            case 1: cout<<"Digite el nombre de la cancion: ";
                    cin>>cancion;
                    cout<<"Digite el nombre del album de la cancion: ";
                    cin>>album;
                    cout<<"Digite el número de reproducciones de la cancion: ";
                    cin>>valor;
                    insertarNodo(song, valor, cancion, album);
                    cout<<"\n";
                    system("pause");
                    break;
            
            case 2: cout<<"\n Lista de reproduccion: \n\n";
                    listaReproduccion(song);
                    cout<<"\n\n";
                    system("pause");
                    break;
        }
        system("cls");
    }while(opcion != 3);
}


nodoCancion *crearNodo(int n, string cancion, string album){
    nodoCancion *nuevo_nodo = new nodoCancion();
    
    nuevo_nodo-> numeroReproducciones = n;
    nuevo_nodo-> nombreCancion = cancion;
    nuevo_nodo-> albumCancion = album;
    nuevo_nodo-> der = NULL;
    nuevo_nodo-> izq = NULL;
    
    return nuevo_nodo;
}

void insertarNodo(nodoCancion *&song, int n, string cancion, string album){
    if(song == NULL){
        nodoCancion *nueva_cancion = crearNodo(n, cancion, album);
        song = nueva_cancion;
    }
    
    else{
        int valorCancion = song->numeroReproducciones;
        if(n < valorCancion){
            insertarNodo(song -> izq,n,cancion,album);
        }
        else{
            insertarNodo(song -> der,n,cancion,album);
        }
    }
}

void listaReproduccion(nodoCancion *song){
    if(song == NULL){
        return;
    }
    else{
        listaReproduccion(song->der);
        cout<<"("<<song->nombreCancion<< "-" << song->albumCancion<<")";
        cout<<"\n";
        listaReproduccion(song->izq);
    }
}
