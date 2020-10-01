
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

//https://codeforces.com/gym/102501/problem/K
//
// tomo T como la raiz, 
// hago el grafo inverso
// para cada hijo de T, quiero ver si nohay otra manera de llegar mas que la directa

// para esto, hago una dfs
// cada dfs tiene una subRaiz activa, que es el hijo directo de T desde el que inicia la dfs
// entonces hay dos maneras de llegar de otra forma a un hijo A 
// si llego a A en la dfs y este no es la subRaiz activa, entonces lo quito como posible nodo
// si llego a A por medio de un nodo B, pero A es la subRaiz activa, en cuyo caso no puedo asegurar nada, pero
//         si en algun momento, se puede llegar a B desde otra subRaiz, entonces A deja de ser un nodo de los quebusco
//          entonces en mi dfs guardo si puedes llegar a tu subRaiz 

// entonces al momento de llegar en la dfs a un nodo ya visitado, lo quito como nodo de los que busco, y si este puede llegar
// a su subRaiz, y su subRaiz no es la quito, tambien quito a su subRaiz
// si no lo he visitado, hago la dfs normal, y pregunto si este hijo pudo llegar a la subRaiz activa, para ver si yo puedo llegar

// asi, si hay otra manera de llegar a A, eventualmente se va a quitar

using namespace std;

typedef int64_t ll;

typedef vector<int> vi;
typedef pair<int,ll> pill;
typedef vector<pill> vill;
typedef pair<int,int> pii;
typedef vector<pii> vii;

#define MINF -1000000000000
#define MOD 1000000007

#define modula(a,b) (a%b + b)%b
#define loop(i,a,b) for(int i = a; i < b; ++i)
#define invl(i,a,b) for(int i = a; i > b; --i)

const int maxN = 100005;
int n, m, t;


vi adj[maxN];
bool visited[maxN], llegoASubRaiz[maxN];
int subRaizActiva, subRaiz[maxN];
bool enS[maxN];

void dfs(int f, int nd){
    //me marco como visitado y detecto a mi subRaiz
    visited[nd] = true;
    subRaiz[nd] = subRaizActiva;

    for(int son : adj[nd]){
    
        if(visited[son]){
            //checo si eres la activa
            if(son == subRaizActiva){
                llegoASubRaiz[nd] = true;
            }
            else
            {
                // si no eres la activa, entonces te quito de S (si no es subRaiz no afecta)
                enS[son] = false;
                //si llegas a tu subraiz, entonces se puede llegar desde la activa y la quito de S
                if(llegoASubRaiz[son] && subRaiz[son] != subRaizActiva)
                    enS[subRaiz[son]] = false;
            }
        }
        else{
            dfs(nd, son);
            if(llegoASubRaiz[son]) llegoASubRaiz[nd] = true;
        }
        
    } 

}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin>>n>>m>>t;

    //creo el grafo inverso
    loop(i, 0, m){
        int a, b;
        cin>>a>>b;
        adj[b].push_back(a);
    }

    //los marco todos como en S y despues descarto los que no
    for(int son : adj[t]){
        enS[son] = true;
    }


    visited[t] = true;
    for(int son: adj[t]){
        if(visited[son]){
            //si ya te visite, no hay unico camino a ti, y te quito de S
            enS[son] = false;
            //si llegas a tu subRaiz, como en este caso son seria la activa, 
            //entonces su subRaiz tampoco esta en S
            if(llegoASubRaiz[son]) enS[subRaiz[son]] = false;
        }
        else{
            subRaizActiva = son;
            dfs(t, son);
        }
    }

    int totalS = 0;
    for(int son: adj[t])
        totalS += enS[son];

    cout<<totalS<<"\n"; 
    loop(i, 0, n){
        if(enS[i]) cout<<i<<"\n";
    }

    return 0;

}
