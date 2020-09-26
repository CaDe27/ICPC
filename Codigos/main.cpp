#include <iostream>

using namespace std;

int main(){
    cout<<1000<<" "<<5000<<" "<<1000000000<<endl;
    cout<<1<<" "<<1000<<endl;
    for(int i = 1; i <= 500; ++i){
        for(int j = i+1; j<=i+10; ++j){
            cout<<i<<" "<<j<<" "<<1<<" "<<1000000000<<endl;
        }
    }
}