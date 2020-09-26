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

using namespace std;

typedef int64_t ll;

typedef pair<int,ll> pill;
typedef vector<pill> vill;

typedef pair<ll,int> pii;
typedef vector<pii> vii;
typedef vector<int> vi;


#define loop(i,a,b) for(int i = a; i < b; ++i)
#define mp make_pair
const int maxN = 300005;


vill adj[maxN];
bool visited[maxN], isBridge[maxN], special[maxN];
int level[maxN], backEdges[maxN], specialSons[maxN];
ll dp[maxN], c[maxN], w[maxN], resp[maxN];
int k;

void dfsBridges(int f, int nd){
    visited[nd] = true;
    level[nd] = level[f] + 1;
    specialSons[nd] = special[nd];

    for(pill s : adj[nd]){
        int son = s.first;

        if(son == f) continue;
	//si eres back edge
        if(visited[son])
            backEdges[nd] += level[son] > level[nd]? 1: -1;
        //si eres front edje
        else{
            dfsBridges(nd, son);
            specialSons[nd] += specialSons[son];
            backEdges[nd] += backEdges[son];
        }
    }
    isBridge[nd] = backEdges[nd]==0;
    //si eres la raiz

}

ll maxProfit(int son, ll weight){
    //Si estamos en una biconnected component, puedo dirigirla a mi hijo porque no tiene special sons
    // o si la dirigo a mi, pero todos los specials estan en su rama (entonces dirigirla a mi la mantiene saturada),
    // puedo sacar el maximo valor de mi hijo
    if (!isBridge[son] || specialSons[son] == 0 || specialSons[son] == k)
        return dp[son];
    else return max( (ll)0, dp[son] - weight);
}

void dfsDP(int f, int nd){
    dp[nd] = c[nd];
    for(pill s : adj[nd]){
        int son = s.first;
        ll weight = s.second;

        if(level[son] == 1+level[nd]){
           dfsDP(nd, son);
           dp[nd] += maxProfit(son, weight);
        }
    }
}

void dfsResp(int f, int nd, ll weight){
    if(f != 0){
        dp[f] -= maxProfit(nd, weight);
        isBridge[f] = isBridge[nd];
        specialSons[f] = k - specialSons[nd];
        specialSons[nd] = k;
        dp[nd] += maxProfit(f, weight);
    }
    resp[nd] = dp[nd];
    
    for(pill s : adj[nd]){
        int son = s.first;
        if(level[son] == 1+level[nd]) 
            dfsResp(nd, son, s.second);
    }

    if(f != 0){
        dp[nd] -= maxProfit(f, weight);
        specialSons[nd] = k - specialSons[f];
        specialSons[f] = k;
        isBridge[nd] = isBridge[f];
        dp[f] += maxProfit(nd, weight);
    }

}



int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    if(fopen("case.txt", "r")) freopen("case.txt", "r", stdin);
    int n, m;
    cin>>n>>m>>k;
    loop(i, 0, k){
        int x; cin>>x;
        special[x] = true;
    }

    loop(i, 1, n+1) cin>>c[i];
    loop(i, 0, m) cin>>w[i];
    loop(i, 0, m){
        int u, v; cin>>u>>v;
        adj[u].push_back( mp(v, w[i]) );
        adj[v].push_back( mp(u, w[i]) );
    }

    dfsBridges(0, 1);
    
    dfsDP(0, 1);
    dfsResp(0, 1, 0);

    cout<<resp[1];
    loop(i, 2, n+1){
        cout<<" "<<resp[i];
    }
    cout<<"\n";

}

