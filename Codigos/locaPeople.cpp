#include <iostream>
#include <stack>

//la idea es que el area del rectangulo maximo 
// entre las filas a y b
// el rectangulo esta pegado a la fila b 
// o es la respuesta entre las filas a y b-1

//para calcular si esta pegado a la fila b
// usamos destruyendo edificios
// este nos permite calcular el area maxima entre las filas
// 0 e i, 1 e i, 2 e i ... hasta entre i e i
// con base en i 
using namespace std;

const int maxN = 1005;
int n, m;

typedef pair<int,int> pii;

stack<pii> alturas;
int extension[maxN];
int entreFilas[maxN][maxN];
int mat[maxN][maxN];

//mat[i][j] tiene la cantidad de unos que hay desde
//esa entrada al proximo cero hacia arriba
// o sea, "la altura del edificio"
void leeAlturas(){
    for(int i = 0; i < n;  ++i)
    for(int j = 0; j < m; ++j){
        int h; cin>>h;
        if(h == 1){
            if(i > 0)
                mat[i][j] = 1+mat[i-1][j];
            else
            {
                mat[i][j] = 1;
            }
        }
        else{
            mat[i][j] = 0;
        }
    }
}

//limpia la pila y el arregoe extension
void clear(){
    stack<pii> empty;
    swap(empty, alturas);
    fill(extension, extension + maxN, 0);    
}

//
void agrega(int h){
    int como = 0;
    while(!alturas.empty() && alturas.top().first >= h){
        como += alturas.top().second + 1;

        int tope = alturas.top().first;
        alturas.pop();
        
        //tu extension es todo lo que yo puedo comerme
        extension[tope] = max( extension[tope], como);

    }
    
    alturas.push(pii(h, como));
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m;
    
    leeAlturas();

    for(int i = 0; i < n ; ++i){
        
        clear();
        
        //destruyendo edificios para calcular maxima extension de cada altura
        for(int j = 0; j<m; ++j)
            agrega(mat[i][j]);
        agrega(0); 
        
        //extension maxima para cada altura es la maxima entre la tuya y la de las alturas mayores
        for(int j = i; j >=1; --j){
            extension[j] = max(extension[j], extension[j+1]);
        }

        //calculo entre filas
        // tu area maxima entre la fila j e i con edificios que empiezan en el piso i
        // es el maximo entre los que llegan hasta j-1  y los de la altura maxima
        entreFilas[i][i] = extension[1];
        for(int j = i-1; j>=0; --j){
            entreFilas[j][i] = max(entreFilas[j+1][i], (i-j+1)*extension[i-j+1]);
        }
        
        //ahora el maximo entre la fila j e i, o tiene piso en i, o ya esta guardado en el area maxima entre j e i-1
        for(int j = 0; j<i; ++j){
            entreFilas[j][i] = max(entreFilas[j][i], entreFilas[j][i-1]);
        }

    }

    int q; cin>>q;
    for(int i = 0; i < q; ++i){
        int a, b; cin>>a>>b;
        --a;--b;
        cout<<entreFilas[a][b]<<"\n";
    }




}