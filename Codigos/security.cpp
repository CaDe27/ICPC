//podemos checar si un ID en especifico esta con una bfs desde s en O(m)
// hay muchos intervalos que pueden checarse asi, pues nunca pueden estar separados
// por ejemplo si k = 10, y las puertas tienen intervalos [1,3] [2, 14] el intervalo [5-10] 
// siempre va junto y podemos checarlo con un solo representante

//hay a lo mas 2m-1 + 2m intervalos disjuntos que pueden no ir juntos
// dados por las puertas
// asi que 
// tardamos mlog m en ordenar estos intervalos
// y 4m*(m) = 4m^2 en checar cada uno
// asi que tenemos m^2 en general y funciona



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

typedef pair<int,ll> pill;
typedef vector<pill> vill;
typedef pair<int,int> pii;
typedef vector<pii> vii;

#define loop(i,a,b) for(int i = a; i < b; ++i)
#define invl(i,a,b) for(int i = a; i > b; --i)

const int maxN = 1005, maxM = 5005;
int n, m, k;
int s, t;

struct puerta{
    int b, c, d;
    puerta(){ b = c = d = 0;}
    puerta(int b1, int c1, int d1){ b = b1; c = c1; d = d1;}
};
vector<puerta> adj[maxN];

vector<int> limites;

//te dice si hay un camino de s a t por el que puede pasar h
bool bfs(int h){
    queue<int> cola;
    bool visited[maxN];
    fill(visited, visited+maxN, 0);

    cola.push(s);
    visited[s] = true;
    bool llegue = false;

    while(!llegue && !cola.empty()){
        
        int v = cola.front();
        cola.pop();

        if(v == t) llegue = true;
        
        for(puerta p : adj[v]){
            
            if(!visited[p.b] && p.c<=h && h<= p.d){
                visited[p.b] = true;
                cola.push(p.b);
            }
                
        }

    }
    
    return llegue;
}


int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m>>k;
    cin>>s>>t;
    int a, b, c, d;
    loop(i, 0, m){
        cin>>a>>b>>c>>d;
        adj[a].push_back(puerta(b, c, d));
        limites.push_back(c);
        limites.push_back(d);
    }
    limites.push_back(1);
    limites.push_back(k);

    sort(limites.begin(), limites.end());
    
    int resp = 0;
    
    int ant, desp;
    loop(i, 0, 2*m+2 - 1){
        ant = limites[i];
        desp = limites[i+1];
        
        //checo ant y el intervalo [ant+1, desp)
        if(ant < desp && bfs(ant)) ++resp;
        if(ant + 1 < desp && bfs(ant+1)) resp += desp-1 - ant;
    }
    //checo el ultimo que falto
    if(bfs(k)) ++resp;
    
    cout<<resp<<"\n";
    

}
