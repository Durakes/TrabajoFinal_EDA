#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Grafo
{
    public:
    int numeroVertice;
    bool** adjMatriz;

    Grafo(const int numero)
    {
        this->numeroVertice = numero;
        adjMatriz = new bool*[numeroVertice];

        for (int i = 0; i < numero; i++)
        {
            adjMatriz[i] = new bool [numeroVertice];
            for (int j = 0; j < numero; j++)
                adjMatriz[i][j] = false;
        }
    }

    void agregarArista(int i, int j)
    {
        adjMatriz[i][j] = true;
        adjMatriz[j][i] = true; /* Si se desea representar un grafo dirigido se toma solo el orden ingresado por parametro */
    }

    void quitarArista(int i, int j)
    {
        adjMatriz[i][j] = false;
        adjMatriz[j][i] = false; /* Si se desea representar un grafo dirigido se toma solo el orden ingresado por parametro */
    }

    bool verificarArista(int i, int j)
    {
        if(adjMatriz[i][j] == true)
        {
            return true;
        }else
        {
            return false;
        }
    }

    void imprimir()
    {   
        cout << "    ";
        for (int i = 0; i < numeroVertice; i++)
        {
            cout << i << " ";
        }
        cout << "\n";
        
        for (int i = 0; i < numeroVertice; i++)
        {
            cout << i << " : ";
            for (int j = 0; j < numeroVertice; j++)
                cout << adjMatriz[i][j] << " ";
            cout << "\n";
        }
    }

    void dfs(int start, vector<bool>& visited, map<int,int> *generalmap)
    {
    
        // Print the current node
        cout << start << " ";
        // Set current node as visited
        visited[start] = true;
        // For every node of the graph
        for (int i = 0; i < numeroVertice; i++) 
        {
            // If some node is adjacent to the current node
            // and it has not already been visited
            if (adjMatriz[start][i] == 1 && (!visited[i]))
            {
                dfs(i, visited, generalmap);
            }
        }
    }

    void bfs(int start,map<int,int> *generalmap)
    {
    // Visited vector to so that
    // a vertex is not visited more than once
    // Initializing the vector to false as no
    // vertex is visited at the beginning
        vector<bool> visited(numeroVertice, false);
        vector<int> q;
        q.push_back(start);

        // Set source as visited
        visited[start] = true;

        int vis;
        while (!q.empty()) 
        {
            vis = q[0];

            // Print the current node
            cout << vis << " ";
            q.erase(q.begin());

            // For every adjacent vertex to the current vertex
            for (int i = 0; i < numeroVertice; i++)
            {
                if (adjMatriz[vis][i] == 1 && (!visited[i])) 
                {

                    // Push the adjacent node to the queue
                    q.push_back(i);

                    // Set
                    visited[i] = true;
                }
            }
        }
    }
};