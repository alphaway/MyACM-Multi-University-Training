//
//  main.cpp
//  HDU2848
//
//  Created by beMaster on 16/3/12.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
typedef long long LL;
LL base[22];
void getBase(){
    base[0] = 1;
    for(int i=1;i<22;++i) base[i] = base[i-1] * 10;
}
bool dfs(LL n, int k);
bool divide(LL n, int dep, int k, LL cur){
    if(dep==k){
        return !dfs(n+cur, k);
    }
    else{
        for(int i=1;i<=19;++i){
            LL a = n % base[i];
            LL b = n / base[i];
            if(b==0){
                break;
            }
            else if(divide(b, dep+1, k, cur+a)){
                return true;
            }
                
        }
         return false;
    }
   
}
bool dfs(LL n, int k){
    if(n < base[k-1])//n的位数比小于k，false
        return false;
    else{
        return divide(n, 1, k, 0);
    }
}
int main(int argc, const char * argv[]) {
    getBase();
    LL n; int k;
    while(cin>>n>>k){
        if(dfs(n,k))
            printf("1\n");
        else
            printf("0\n");
    }
    return 0;
}
