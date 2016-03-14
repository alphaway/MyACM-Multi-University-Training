//
//  main.cpp
//  HDU2855
//
//  Created by beMaster on 16/3/14.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
struct Matrix{
    int d[2][2];
}ans,ori;
int n,m;
/*
 矩阵乘法
 */
Matrix mutil(Matrix &lhs, Matrix &rhs){
    Matrix ret;
    memset(ret.d,0,sizeof(ret.d));
    for(int k=0;k<2;++k)
        for(int i=0;i<2;++i)
            for(int j=0;j<2;++j){
                ret.d[i][j] += lhs.d[i][k] * rhs.d[k][j];
                if(ret.d[i][j]>=m)
                    ret.d[i][j] %= m;
            }
    return ret;
}
/*
 矩阵快速幂
 */
void solve(){
    int k = n;
    while(k){
        if(k&1)
            ans = mutil(ans, ori);
        k>>=1;
        ori = mutil(ori, ori);
    }
}
/*
 (1+x)^n = c(n,0)*0 + c(n,1)*x^1 + c(n,2)*x^2...
 */
int main(int argc, const char * argv[]) {
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        ans.d[0][0] = ans.d[1][1] = 1;
        ans.d[0][1] = ans.d[1][0] = 0;
        ori.d[0][0] = 2;
        ori.d[0][1] = ori.d[1][0] = ori.d[1][1] = 1;
        solve();
        printf("%d\n",ans.d[0][1]);
    }
    return 0;
}
