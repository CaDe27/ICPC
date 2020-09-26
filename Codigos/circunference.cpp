
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <stack>
#include <utility>
#include <queue>
#include <set>
#include <iomanip>

using namespace std;

typedef int64_t ll;
typedef vector<int> vi;
typedef pair<int,int> pii;


#define MOD(a,b) (a%b + b)%b
#define loop(i,a,b) for(int i = a; i < b; ++i)
#define invl(i,a,b) for(int i = a; i > b; --i)

const int maxN = 300005;
int n;
vi adj[maxN];
int papa[maxN];
bool visited[maxN], enDiametro[maxN];
int level[maxN], distExtremo[maxN];
int resp[maxN];
int diametro;

//devuelve el nodo mas lejano de v y su distancia a v
pii masLejano(int inicial){
    queue<pii> bfs;
    bfs.push(pii(inicial, 0));

    papa[inicial] = inicial;
    int nodoLejano = inicial;
    int dist = 0;

    fill(visited, visited + maxN, 0);
    pii nodo;
    while(!bfs.empty()){
       //visito y quito de la cola
       nodo = bfs.front();
       bfs.pop();
       
       visited[nodo.first] = true;

        //si es el mas lejano, actualiz
        if(nodo.second > dist){
           dist = nodo.second;
           nodoLejano = nodo.first;
        }

        //meto a todos sus hijos no visitados
        for(int son : adj[nodo.first]){
            if(visited[son]) continue;
            
            papa[son] = nodo.first;
            bfs.push(pii(son, nodo.second + 1));
        }

    }

    //localizo en el diametro
    return pii(nodoLejano, dist);

}

//si extremo1 y extremo2 son los nodos extremos del diametro, y diam es la longitud del diametro
// y ademas extremo1 es la raiz del diametro, todos son sus hijos y extremo2 es hoja
// determina todos los nodos que estna en el diametro y guarda en distExtremo su distancia minima a uno de los extremos
void localizaDiametro(int extremo1, int extremo2){
        int v = extremo2, distEx = 0;
        do{ 
            enDiametro[v] = true;
            distExtremo[v] = min(distEx, diametro-distEx);
            v = papa[v];
            ++distEx;
        }while(v != extremo1);
        
}

//realiza una dfs desde un nodo en el diametro
//si la altura en este subarbol es mayor o igual a la distancia al extremo la respuesta es diam +1, si no , diam
int raizSubArbol;
void dfsExtremo(int nd, int papa = 0){
    level[nd] = papa==0? 0: level[papa] + 1;
    resp[nd] = level[nd] == distExtremo[raizSubArbol]? diametro + 1 : diametro;
    for(int son: adj[nd]){
        if(enDiametro[son])  continue;
        if(son  == papa) continue;
        dfsExtremo(son, nd);
    }
}  

void dfsDiametro(int extremo1, int extremo2){
    do{
        raizSubArbol = extremo2;
        dfsExtremo(extremo2);
        extremo2 = papa[extremo2];
    }while(extremo2 != extremo1);

}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n;
    

    loop(i, 0,n-1){
        int a, b; 
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);    
    }

    pii extremo1, extremo2;
    extremo1 = masLejano(1);
    extremo2 = masLejano(extremo1.first);
    diametro = extremo2.second;
    localizaDiametro(extremo1.first, extremo2.first);

    dfsDiametro(extremo1.first, extremo2.first);

    loop(i, 1, n+1){
        cout<<resp[i]<<"\n";
    }

}