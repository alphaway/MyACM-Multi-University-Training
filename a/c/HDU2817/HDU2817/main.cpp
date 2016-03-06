//
//  main.cpp
//  HDU2817
//
//  Created by beMaster on 16/3/3.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string.h>
using namespace std;
typedef long long LL;
const int MOD = 200907;
LL quick_pow(LL a, LL k){
    LL ret = 1;
    while (k) {
        if(k&1)
            ret = ret * a % MOD;
        a = a * a % MOD;
        k>>=1;
    }
    return ret;
}
int main(int argc, const char * argv[]) {
    int t;
    scanf("%d",&t);
    while(t--){
        LL a,b,c,k;
        cin>>a>>b>>c>>k;
        LL d = b - a;
        if(b + d == c){//等差,an = a1 + (n-1)*d;
            cout<< (a % MOD + (k-1) % MOD * d % MOD) % MOD << endl;
        }
        else{//等比, an = (
            LL q = b / a;
            cout << (a % MOD * quick_pow(q, k-1))%MOD <<endl;
        }
    }
    return 0;
}
