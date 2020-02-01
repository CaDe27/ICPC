//
// si tomo izq, cuento el caso del sig en el que mi oponente toma el sig que mas conviene y es valor + ese caso en el que sigo de nuevo
// maximizarte equivale a minimizar a tu enemigo
#include <iostream>
#include <algorithm>
#define loop(i, a, b) for(int i = a; i < b; ++i)
#define endl '\n'
#define optimize() ios_base::sync_with_stdio(0);
#define readMyCase() if(fopen("case.txt", "r")) freopen("case.txt", "r", stdin)
using namespace std;
const int maxN = 100;
int n;
int coins[maxN];
long dp[maxN][maxN];
void limpiaDP(){
    loop(i, 0, n)
        fill(dp[i], dp[i]+n, -1);
}

long DP(int izq, int der){
    if(izq > der)
        return 0;
    else if(dp[izq][der] == -1){
        //podemos hacer bien todas estas elecciones porque el arreglo es par y el siempre va a tener
        //turno despues de nosotros
        long tomoIzq = 0, tomoDer = 0;
        //si yo tomo la izq (el recibe izq+1, der)
        //el me va a dejar el caso que minimice mi ganancia
        if(DP(izq+2, der) < DP(izq+1, der-1))
            tomoIzq += coins[izq] + DP(izq+2, der);
        // si le conviene tomar el de la derecha
        else
            tomoIzq += coins[izq] + DP(izq+1, der-1);
        
        //si yo tomo la der (el recibe izq, der-1)
        if(DP(izq, der-2) < DP(izq+1, der-1))
            tomoDer += coins[der] + DP(izq, der-2);
        else 
            tomoDer += coins[der] + DP(izq+1, der-1);
        dp[izq][der] = max(tomoIzq, tomoDer);
    }
    return dp[izq][der];
}

int main(){
    optimize();
    readMyCase();
    int testCases; cin>>testCases;
    loop(t, 0, testCases){
        cin>>n;
        loop(i, 0, n)
            cin>>coins[i];
        limpiaDP();
        cout<<DP(0, n-1)<<endl;
    }
    
}