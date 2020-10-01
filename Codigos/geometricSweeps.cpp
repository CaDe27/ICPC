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
typedef vector<int> vi;
typedef vector<int, pii> viii;
 
#define loop(i,a,b) for(int i = a; i < b; ++i)
#define invl(i,a,b) for(int i = a; i > b; --i)
 
 
struct PT {
    double x,y;
    PT(){};
    PT(double x, double y) : x(x), y(y){}
    PT(const PT &p) : x(p.x), y(p.y) {}
    PT operator + (const PT &p) const {  return PT(x+p.x, y+p.y);  }
    PT operator - (const PT &p) const {  return PT(x-p.x, y-p.y);  }
    bool operator < (const PT &p) const { return x < p.x || (x == p.x && y < p.y);}
};
 
double cross(PT p, PT q)    {return p.x*q.y - p.y*q.x;}
 
vector < PT > ConvexHull(vector < PT > &P){ 
    sort(P.begin(), P.end());
    vector<PT>U,L;
    for(int i = 0; i < P.size(); i++){
        while(L.size() > 1 && cross(L[L.size()-1]-L[L.size()-2], P[i]-L[L.size()-2]) > 0)
            L.pop_back();
        L.push_back(P[i]);
    }
    if(L.size() > 1) L.pop_back();
    for(int i = P.size()-1; i >= 0; i--){
        while(U.size() > 1 && cross(U[U.size()-1]-U[U.size()-2], P[i]-U[U.size()-2]) > 0) 
            U.pop_back();
        U.push_back(P[i]);
    }
    if(U.size() > 1) U.pop_back();
    L.insert(L.end(), U.begin(), U.end());
    return L;
}

// dado un conjunto de puntos y un punto especifico A
//realiza un sweep line en sentido de las manecillas del reloj y centrado en A
// esto permite considerar todas las posibles rectas que dividen en dos al conjunto de puntos y que pasan por A
// la linea considerada pasa por encima de A y por debajo del punto por el que "trazamos la recta"
// y lo hacen en O(n log n)
// O(nlog n) para ordenar a los puntos y O(n) para recorrerlos con dos punteros 
// SE ASUME QUE NO HAY 3 PUNTOS COLINEALES
void clockSweep(vector<PT> &P , PT A){
    //tomamos el primer punto del vector y es ahi donde comenzamos la primera recta
    
    //informacion de los puntos debajo de la recta
    // A siempre esta por debajo
    // esto no afecta porque si quereos a A por arriba, es como considerar que A esta por abajo en relacion a la recta con otro punto
    double fAbajo = 0;

    //informacion de los puntos por encima de la recta
    // incluimos al primero del vector
    double fArriba = 0;


    //hacemos un recorrido O(n) para meter a todos los puntos en la informacion de uno de los dos lados
    // tenemos fijos A y B(el primero del vector)
    // C esta por encima de la recta si la componente en z del producto cruz de (B-A) y (C-A) es mayor a cero
    // me refiero simplemente a esta componente como producto cruz
    // y estas por debajo si el producto cruz es menor a cero

    //hago un recorrido para identificar el primer punto que esta por abajo de la recta que no es A
    // al recorrer a B, posiblemente tenga que recorrer este tambien


    //hago el sweep line
    // voy variando B, cada que cambio de B actualizo a C (esto se hace usando el producto cruz)
    // depende del problema lo que haga con f y como la guarde




}

//recorre todas las posibles rectas en un conjunto de puntos que dividen a estos en dos 
// oara esto usa un clock Sweep (funcion de arriba) sobre cada punto
// complejidad general n^2 logn
void todasPosiblesRectas(vector<PT> &P){

    //para cada punto hago un clock Sweep
    for(PT p : P){
        clockSweep(P, p);
    }

}

int main(){





}
 