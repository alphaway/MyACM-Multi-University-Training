//
//  main.cpp
//  HDU2842
//
//  Created by beMaster on 16/3/10.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
typedef long long LL;
LL tmplate[4][4] = {{1,2,0,1},{1,0,0,0},{0,1,0,0},{0,0,0,1}};
const int MOD = 200907;
struct Matrix{
    LL a[4][4];
    Matrix(){
        for(int i=0;i<4;i++)
            for(int j=0;j<4;++j)
                a[i][j] = tmplate[i][j];
    }
    void unit(){
        memset(a,0,sizeof(a));
        a[0][0] = a[1][1] = a[2][2] = a[3][3] = 1;
    }
    void zero(){
        memset(a,0,sizeof(a));
    }
    
};
Matrix operator*(Matrix a, Matrix b){
    Matrix ret;
    ret.zero();
    for(int k=0;k<4;++k)
        for(int i=0;i<4;++i)
            for(int j=0;j<4;++j){
                ret.a[i][j] += a.a[i][k]%MOD * b.a[k][j]%MOD;
                if(ret.a[i][j]>=MOD)
                    ret.a[i][j] %= MOD;
            }
    return ret;
}
Matrix quick(Matrix mat, int k){
    Matrix ret;
    ret.unit();
    while(k){
        if(k&1){
            ret = ret * mat;
        }
        k>>=1;
        mat = mat * mat;
    }
    return ret;
}
int main(int argc, const char * argv[]) {
    int n;
    while(scanf("%d",&n),n){
        if(n==1){
            printf("%d\n",1);
        }
        else if(n==2){
            printf("%d\n",2);
        }
        else if(n==3){
            printf("%d\n",5);
        }
        else{
            Matrix a;
            a = quick(a, n-3);
            int ans = a.a[0][0] * 5 + a.a[0][1] * 2 + a.a[0][2] * 1 + a.a[0][3]*1;
            cout<<ans%MOD<<endl;
        }
    }
    return 0;
}
