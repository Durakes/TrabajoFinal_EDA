#include <iostream>
#include "Cancion.h"
using namespace std;

typedef struct nodo
{
    Cancion cancion; 
    struct nodo *izquierdo, *derecha; 
    short altura;
}Nodo;

Nodo * nuevoNodo(Cancion x)
{
    Nodo* nuevo = new Nodo;
    if(nuevo)
    {
        nuevo->cancion = x; 
        nuevo->izquierdo = NULL; 
        nuevo->derecha = NULL; 
        nuevo->altura = 0; 
    }else
        std::cout<<"Error al separar la memoria del nuevo nodo\n";
    return nuevo; 
}

/*Retorna el mayor valor entre dos valores 
a,b -> altura de dos nodos en el árbol*/
short mayor(short a, short b)
{
    return(a>b) ? a:b; 
}

short alturaDelNodo(Nodo * nodo)
{
    if(nodo == NULL)
        return -1; 
    else
        return nodo->altura; 
}

/*Calcula y retorna el factor de equilibrio
en un arbol balanceado debe ser -1, 1 , 0*/
short factorDeEquilibrio(Nodo *nodo)
{
    if(nodo)
        return (alturaDelNodo(nodo->izquierdo)-alturaDelNodo(nodo->derecha));
    else 
        return 0;
}

/**Rotacion a la izquierda*/ 
Nodo * rotacionIzquierda(Nodo *r)
{
    Nodo *y , *f;
    y = r->derecha; 
    f = y->izquierdo;
    
    y->izquierdo = r; 
    r->derecha = f; 
    
    r->altura = mayor(alturaDelNodo(r->izquierdo), alturaDelNodo(r->derecha)) +1;
    y->altura = mayor(alturaDelNodo(y->izquierdo), alturaDelNodo(y->derecha)) +1;
    return y;
}

/**Rotacion a la derecha*/ 
Nodo * rotacionDerecha(Nodo *r)
{
    Nodo *y , *f;
    y = r->izquierdo; 
    f = y->derecha;
    
    y->derecha = r; 
    r->izquierdo = f; 
    
    r->altura = mayor(alturaDelNodo(r->izquierdo), alturaDelNodo(r->derecha)) +1;
    y->altura = mayor(alturaDelNodo(y->izquierdo), alturaDelNodo(y->derecha)) +1;
    return y;
}

/**Rotacion doble*/ 
Nodo * rotacionDerechaIzquierda(Nodo *r)
{        
    r->derecha = rotacionDerecha(r->derecha);     
    return rotacionIzquierda(r);
}

/**Rotacion doble*/ 
Nodo * rotacionIzquierdaDerecha(Nodo *r)
{        
    r->izquierdo = rotacionIzquierda(r->izquierdo);     
    return rotacionDerecha(r);
}

Nodo* insertarNodo(Nodo* nodo, Cancion valor)
{
    if(nodo == NULL)
    {
        return(nuevoNodo(valor));
    }
    
    if(valor.getNombre().compare(nodo->cancion.getNombre()) < 0)
    {
        nodo->izquierdo = insertarNodo(nodo->izquierdo,valor);
    }
    else if(valor.getNombre().compare(nodo->cancion.getNombre()) > 0)
    {
        nodo->derecha = insertarNodo(nodo->derecha,valor);
    }
    else
        return nodo;

    nodo->altura = 1 + mayor(alturaDelNodo(nodo->derecha),alturaDelNodo(nodo->izquierdo));

    int balance = factorDeEquilibrio(nodo);

    //Rotación solo derecha
    if (balance > 1 && valor.getNombre() < nodo->izquierdo->cancion.getNombre())
        return rotacionDerecha(nodo);

    // Rotación solo izquiera
    if (balance < -1 && valor.getNombre() > nodo->derecha->cancion.getNombre())
        return rotacionIzquierda(nodo);

    // LRotación izquierda-derecha
    if (balance > 1 && valor.getNombre() > nodo->izquierdo->cancion.getNombre())
    {
        nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
        return rotacionDerecha(nodo);
    }

    // Rotación derecha-izquierda
    if (balance < -1 && valor.getNombre() < nodo->derecha->cancion.getNombre())
    {
        nodo->derecha = rotacionDerecha(nodo->derecha);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

void preOrder(Nodo *raiz)
{
    if(raiz != NULL)
    {
        std::cout << raiz->cancion.getNombre()<< " " << endl;
        preOrder(raiz->izquierdo);
        preOrder(raiz->derecha);
    }
}

Cancion* buscarArbol(Nodo* raiz, string valor)
{
    if(raiz == NULL)
        return NULL;
    else if(raiz->cancion.getNombre().compare(valor) == 0)
        return &raiz->cancion;
    else if(raiz->cancion.getNombre().compare(valor) > 0)
    {
        return buscarArbol(raiz->izquierdo, valor);
    }else
    {
        return buscarArbol(raiz->derecha, valor);
    }
}
