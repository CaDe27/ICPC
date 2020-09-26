#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

//Fairy sequences 
//http://poj.org/problem?id=2478
// la idea es que F(n) = sumatoria desde i = 2 hasta de n de phi(n)
// donde phi es la funcion phi de euler (euler's totient function)

const int maxN = 1e6+5;
bitset<maxN> esPrimo;
vector<int> primos;

int sizePrimos;
long long int f[maxN];

void criba(){
    esPrimo.set();

    esPrimo[0] = esPrimo[1] = 0;
    f[1] = 1;

    for(int i = 2; i < maxN; ++i){
        if(esPrimo[i]){
            primos.push_back(i);
            f[i] = i-1;
            ++sizePrimos;
        }
        for(int j = 0; j < sizePrimos; ++j){
            if(i*primos[j] >= maxN) break;
            esPrimo[primos[j]*i] = 0;
            if(i%primos[j] == 0){
                f[i*primos[j]] = f[i]*primos[j];
                break;
            }else{
                f[i*primos[j]] = f[i]*(primos[j] - 1);
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    
    criba();
    for(int i =3; i < maxN; ++i)
        f[i] += f[i-1];

    int n;
    cin>>n;
    while( n!=0 ){
       cout<<f[n]<<"\n";
        cin>>n;
    }
    
	return 0;
}
