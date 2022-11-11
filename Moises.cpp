#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <cstring>
#include <string.h>
#include <array>

using namespace std;
using std::cout;



struct nodoArbol {
    int mus, altura;
    nodoArbol * izq, * der, * padre;
    
};
typedef struct nodoArbol NodoArbol;


NodoArbol* arbol_crea(int m, nodoArbol* padre)
{
    NodoArbol* p = (NodoArbol*)malloc(sizeof(NodoArbol)); 
    p->mus = m; 
    p->izq = NULL; 
    p->der = NULL;
    p->padre = padre;
    p->altura = 0;  
    return p; 
}

void insertarNodo(NodoArbol *&a, int n,NodoArbol*padre) {
    if (a == NULL) { 
        NodoArbol *n_nodo = arbol_crea(n,padre);
        a = n_nodo;
    }
    else { 
        int valorRaiz = a->mus; 
        if ( n < valorRaiz) {
            insertarNodo(a->izq, n,a);
        }
        else {
            insertarNodo(a->der, n,a);
        }
    }
}

bool busqueda(NodoArbol* a, int n) {
    if (a == NULL) {
        return false;
    }
    else if (a->mus == n){
        return true;
    }
    else if (n <a->mus) {
        return busqueda(a->izq, n);
    }
    else {
        return busqueda(a->der, n);
    }
}

void imprime_alfa(NodoArbol* a) {
    if (a == NULL) {
        return;
    }
    else {
        imprime_alfa(a->izq);
        cout << " | " << a->mus << " | ";
        imprime_alfa(a->der);
    }
}

int n_datos(NodoArbol* a) {
    int cont = 0;
    if (a != NULL) {
        cont++;
        cont+=n_datos(a->izq);
        cont+=n_datos(a->der);
        return cont;
    }
    else
        return cont;
}

int n_izq(NodoArbol* a) {
    int cont = 0;
    if (a != NULL) {
        cont-=n_datos(a->izq);
        cont--;
        return cont;
    }
}

int n_der(NodoArbol* a) {
    int cont = 0;
    if (a != NULL){
        cont++;
        cont+=n_datos(a->der);
        return cont;
    }
}

NodoArbol* minimo(NodoArbol* a) {
    if (a == NULL) {
        return NULL;
    }
    if (a->izq) { 
        return minimo(a->izq); 
    }
    else { 
        return a; 
    }
}

void destruirNodo(NodoArbol* nodo) {
    nodo->izq = NULL;
    nodo->der = NULL;
    delete nodo;
}

void reemplazar(NodoArbol* a, NodoArbol* nuevoNodo) {
    if (a->padre) {
        if (a->mus == a->padre->izq->mus) {
            a->padre->izq = nuevoNodo;
        }
        else if (a->mus == a->padre->der->mus) {
            a->padre->der = nuevoNodo;
        }
    }
    if (nuevoNodo) {
        nuevoNodo->padre = a->padre;
    }
}

void eliminarNodo(NodoArbol* nodoEliminar) {
    if (nodoEliminar->izq && nodoEliminar->der) {
        NodoArbol* menor = minimo(nodoEliminar->der); 
        nodoEliminar->mus = menor->mus;
        eliminarNodo(menor);
    }
    else if (nodoEliminar->izq) {
        reemplazar(nodoEliminar, nodoEliminar->izq);
        destruirNodo(nodoEliminar);
    }
    else if (nodoEliminar->der) {
        reemplazar(nodoEliminar, nodoEliminar->der);
        destruirNodo(nodoEliminar);
    }
    else { 
        reemplazar(nodoEliminar, NULL);
        destruirNodo(nodoEliminar);
    }
}

void eliminar(NodoArbol* a, int n) {
    if (a == NULL) {
        return;
    }
    else if (n < a->mus) { 
        eliminar(a->izq, n); 
    }
    else if (n > a->mus) { 
        eliminar(a->der, n);
    }
    else {
        eliminarNodo(a);
    }
}

void mostrarArbol(NodoArbol* arbol, int cont) {
    if (arbol == NULL) {
        return;
    }
    else {
        mostrarArbol(arbol->der, cont + 1);
        for (int i = 0; i < cont; i++) {
            cout <<"    ";
        }
        cout << arbol->mus << endl;
        mostrarArbol(arbol->izq, cont + 1);
    }
}

/*
int status_avl(NodoArbol *a){
    if(n_datos(a->izq) + n_datos(a->der) == 0)
        //cout<<"Esta balanceado"<<endl;
        return 0;
    else if (n_datos(a->izq) + n_datos(a->der) < 0){
        //cout<<"Esta desbalanceado hacia la derecha"<<endl;
        return -1;
    }
    else{
        //cout<<"Esta desbalanceado hacia la izquierda"<<endl;
        return 1;
    }
}*/

int maximo_entre_2(int a, int b){
    return (a>b) ? a: b;
}
int altura_arbol(NodoArbol * a)
{
    if( a == NULL)
        return -1;
    else{
        a->altura = 1+maximo_entre_2(altura_arbol(a->izq),altura_arbol(a->der));
        return  a->altura;
    }
}

int status_avl(nodoArbol *n){
    if(n!=NULL)
        return (altura_arbol(n->izq)-altura_arbol(n->der));
    else 
        return 0;
}

//rotacion hacua la izquierda
nodoArbol * rotacionIzquierda(nodoArbol *r){
    nodoArbol *y , *f;
    y = r-> der; 
    f = y->izq;
    
    y->izq = r; 
    r->der = f; 
    
    r->altura = maximo_entre_2(altura_arbol(r->izq), altura_arbol(r->der)) +1;
    y->altura = maximo_entre_2(altura_arbol(y->izq), altura_arbol(y->der)) +1;
    return y;
}

//rotacion hacia la derecha
nodoArbol * rotacionDerecha(nodoArbol *r){
    nodoArbol *y , *f;
    y = r->izq; 
    f = y->der;
     
    y->der = r; 
    r->izq = f; 
     
    r->altura = maximo_entre_2(altura_arbol(r->izq), altura_arbol(r->der)) +1;
    y->altura = maximo_entre_2(altura_arbol(y->izq), altura_arbol(y->der)) +1;
    return y;
}

//un tipo de rotacion doble
nodoArbol * rotacionDerechaIzquierda(nodoArbol *r){        
    r->der = rotacionDerecha(r->der);     
    return rotacionIzquierda(r);
}

//un tipo de rotacion doble
nodoArbol * rotacionIzquierdaDerecha(nodoArbol *r){        
    r->izq = rotacionIzquierda(r->izq);     
    return rotacionDerecha(r);
}

void balanceo(NodoArbol *a){

    int a_izq,a_der;
    NodoArbol * arbol = NULL;

    a_izq = altura_arbol(a->izq);
    a_der = altura_arbol(a->der);

    if(a_izq == a_der){
        return;
    }
    else if (a_izq < a_der)
    {
        if(status_avl(a->der) == 0)
            return;
        else if (status_avl(a->der) < 0)
        {
            mostrarArbol(a->der, 0);
        }
        else if (status_avl(a->der) > 0)
        {
            //mostrarArbol(a->der, 0);
        }
    }
    else if (a_izq > a_der){
        if(status_avl(a->izq) == 0 || status_avl(a->izq) == -1 || status_avl(a->izq) == 1)
            return;
        else if (status_avl(a->izq) < 0)
        {
            mostrarArbol(a->izq, 0);
            a = rotacionDerecha(a);
            mostrarArbol(a, 0);
        }
        else if (status_avl(a->izq) > 0)
        {
            //mostrarArbol(a->izq, 0);
        }
    }
    

}

void menu() {
    int dato, opcion,contador= 0;
    NodoArbol * arbol = NULL;

    do {
        cout << "\t.:MENU:." << endl;
        cout << "1.Insertar una nueva cancion a la playlist" << endl;
        cout << "2.Buscar un elemento en la playlist" << endl;
        cout << "3.Lista de canciones" << endl;
        cout << "4.Eliminar una cancion de la playlist" << endl;
        cout << "5.Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Digite un numero: ";
            cin >> dato;
            insertarNodo(arbol, dato,NULL);
            cout << "\n";
            system("pause");
            break;
        case 2:
            cout <<"\n" <<"Introduce el dato que estas buscando ";
            cin >> dato;
            if (busqueda(arbol, dato) == true) {
                cout << "\n" << "El elemento " << dato << " si se encuentra en la playlist" << endl;
            }
            else {
                cout << "\n" << "El elemento " << dato << " no se encuentra en la playlist" << endl;
            }
            system("pause");
            break;
        case 3:
            cout << "\nPlaylist en orden alfabetico: " << endl;
            imprime_alfa(arbol);
            cout << "\n\n";
            mostrarArbol(arbol,contador);
            cout << "\n\n";
            balanceo(arbol);
            cout << "\n\n";
            system("pause");
            break;
        case 4:
            cout << "\nDigite el numero que desea eliminar:";
            cin >> dato;
            if (busqueda(arbol, dato) == true) {
                eliminar(arbol, dato);
            }
            else {
                cout << "\n" << "El elemento " << dato << " no se encuentra en la playlist" << endl;
            }
            cout << "\n";
            system("pause");
            break;
        }
        //system("cls");
    } while (opcion != 5);
}



int main()
{
    /*Musica p[6]={{"Vive la vida"},{"Lucas"},{"Paola"},{"Ana"},{"Omar"},{"Zoe"}};
    Musica *q;
    char bus[80]="Zoila";
    NodoArbol *a=arbol_crea(&p[0],arbol_crea(&p[1],arbol_crea(&p[3],NULL,NULL),NULL),arbol_crea(&p[2],arbol_crea(&p[4],NULL,NULL),arbol_crea(&p[5],NULL,NULL)));
    q=busca(a,bus);
    
    arbol_imprime(a);
    cout<<endl;
    imprime_alfa(a);
    cout<<endl;

    if(q==NULL){
        
        printf("\n%s no existe en la busqueda",bus);
    }
    else{
    
        printf("\n%s si existe en la busqueda",bus);
    }*/
    
    menu();

    return 0;
}

