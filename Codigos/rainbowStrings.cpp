/*
    Rainbow Strings
    puedo localizar si dos aristas del mismo color estan
    juntas con una dfs

    digo infectado para cuando ya no son rainbow

    hay dos maneras

    si en un nodo, sus dos hijos tienen el mismo color
    si un nodo tiene el mismo color que de mi a mi padre

    si los dos hijos tienen el mismo color:
        todos sus hijos estaran "infectados"
    
    si mi hijo tiene el mismo que mi padre
        toda su rama y todo el resto del arbol que conecta
        conmigo por arriba, estan "infectados"

    primero una dfs para ver que nodos tienen un hijo no directo
    que tiene el mismo color que su papa
    para indicar que hacia arriba todo esta infectado
    se guarda que rama es la que lo contiene porque por ahi si puede haber
    nodos buenos

    si hay un nodo que tenga dos hijos no directos asi en diferentes ramas
    todo el arbol esta infectado

    despues de esta dfs, se hace otra para infectar como tal
    tu te infectas si tienes un hijo especial (el no directo que el y su papa 
    tienen el mismo color a sus respectivos papas) o si ya tu rama estaba infectada 

    la rama de un hijo esta infectada si hay dos hijos del mismo color
    si la rama ya estaba infectada, si tienes un hijo especial y no es ese hijo
    o si tienes el mismocolor que de mi a mi papa
    


*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


typedef pair<int,int> pii;

const int maxN = 50005;
int n;

vector<pii> adj[maxN];

bool todoInfectado;
int hijoEspecial[maxN];
bool infectado[maxN];
int colores[maxN];

void dfs1(int nd, int papa, int colorPapa){
    bool especial = false;
    for(pii nodo : adj[nd]){
        if(nodo.first == papa) continue;
        if(nodo.second == colorPapa)
            especial =true;
        dfs1(nodo.first, nd, nodo.second);
    }

    if(hijoEspecial[nd] != 0)
        especial = true;
    
    if(papa != 0 && especial){
        if(hijoEspecial[papa] != 0)
            todoInfectado = true;
        else
            hijoEspecial[papa] = nd;
    }
    
}

void dfs(int nd, int papa, int colorPapa, bool ramaInfectada){
    
    //yo eestoy infectado si toda la rama esta infectada o tengo hijo especial
    infectado[nd] = ramaInfectada || hijoEspecial[nd]!=0;
    
    for(pii nodo : adj[nd]){
        if(nodo.first == papa) continue;
         ++colores[nodo.second];
    }

    for(pii nodo : adj[nd]){
        if(nodo.first == papa) continue;
        if(colores[nodo.second] > 1){
            infectado[nodo.first] = true;
        }
    }

    for(pii nodo : adj[nd]){
        if(nodo.first == papa) continue;
        --colores[nodo.second];
    }

    for(pii nodo : adj[nd]){
        if(nodo.first == papa) continue;
        //visito a mi hijo
        //toda su rama esta infectada si tengo hijo especial y no eres tu, hay otro hijo de tu color, o tienes el mismo color que mi papa
        if( ramaInfectada || (hijoEspecial[nd]!=0 && hijoEspecial[nd] != nodo.first) || infectado[nodo.first] || colorPapa == nodo.second){
            dfs(nodo.first, nd, nodo.second, true);
        }else
            dfs(nodo.first, nd, nodo.second, false);
    }

    
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n;
    int a, b, c;
    for(int i = 0; i < n-1; ++i){
        cin>>a>>b>>c;
        adj[a].push_back(pii(b, c));
        adj[b].push_back(pii(a, c));
    }
    dfs1(1, 0, 0);
    if(todoInfectado){
        fill(infectado, infectado+maxN, 1);
    }else
    {
        dfs(1, 0, 0, false);
    }
    
    int rainbow = 0;
    for(int i = 1; i <= n; ++i){
        if(!infectado[i]) 
            ++rainbow;
    }
    cout<<rainbow<<"\n";
    for(int i = 1; i <= n; ++i){
        if(!infectado[i]) 
            cout<<i<<"\n";
    }
}
