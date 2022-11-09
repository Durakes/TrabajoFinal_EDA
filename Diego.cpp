#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <conio.h>

using namespace std;

struct Cancion{
    int valor;
    Cancion *siguiente;
};

void menu();
void mostrarRegistro(Cancion *&);
void registroActividad(Cancion *&, int);
Cancion *registro = NULL;

int main()
{
    menu();
    getch();
    return 0;
}

void menu(){
    int opcion, valor;
    do{
        cout<<"\t MENU \n";
        cout<<"1. Ingresar registros\n";
        cout<<"2. Mostrar registros\n";
        cout<<"3. Salir\n";
        cout<<"Opcion: ";
        cin>>opcion;
        
        switch(opcion){
            
            case 1: cout<<"Digite un numero";
                    cin>>valor;
                    registroActividad(registro, valor);
                    break;
            
            case 2: mostrarRegistro(registro);
                    break;
        }
        system("cls");
    }while(opcion != 3);
}

void registroActividad( Cancion *&registro, int n){
    Cancion *nuevo_nodo = new Cancion();
    nuevo_nodo->valor = n;
    
    Cancion * aux1 = registro;
    Cancion * aux2;
    
    while((aux1 != NULL) && (aux1->valor < n)){
        aux2 = aux1;
        aux1 = aux1 -> siguiente;
    }
    
    if ( registro == aux1){
        registro = nuevo_nodo;
    }
    else{
        aux2->siguiente = nuevo_nodo;
    }
    
    nuevo_nodo->siguiente = aux1;
}

void mostrarRegistro( Cancion *&registro){
    
    Cancion *actual = new Cancion();
    actual = registro;
    
    while(actual != NULL){
        cout<<actual->valor<<" -> " ;
        actual = actual->siguiente;
    }
}
