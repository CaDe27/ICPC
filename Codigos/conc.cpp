
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

#define loop(i,a,b) for(int i = a; i < b; ++i)
#define invl(i,a,b) for(int i = a; i > b; --i)

ll gauss(ll a, ll b){
    if( (b-a)%2 == 0)
        return a*(b-a+1) + ((b-a)/2)*(b-a+1);
    else
        return a*(b-a+1) + ((b-a+1)/2)*(b-a); 
}

//overflow
//ll gauss(ll a){
//    return a*(a+1)/2;
//}

ll f(ll a){
    ll suma = 0;
    int i = 1;
    long double sq = sqrt(a);
    ll sup, inf;
    for(; (a/i) > sq; ++i ){
        sup = a/i;
        inf = a/(i+1) + 1;
        suma += i*(gauss(inf, sup));
    }

    for(i = a/i; i>=1; --i){
        suma += i*(a/i);
    }

    return suma;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //if(fopen("case.txt", "r")) freopen("case.txt", "r", stdin);
    ll a,b;
    cin>>a>>b;
    cout<<f(b)-f(a-1)<<"\n";
}

