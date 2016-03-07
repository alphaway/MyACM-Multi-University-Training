//
//  main.cpp
//  HDU2830
//
//  Created by beMaster on 16/3/7.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 1000 + 10;
int a[N][N];
int dp[N];
int d[N];
int getAns(int *dp, int m){
    int ret = 0;
    for(int i=1;i<=m;++i)
        d[i] = dp[i];
    sort(d+1,d+m+1);
    d[0] = -1;
    for(int i=m;i>=1;--i){
        if(d[i-1] != d[i])
            ret = max(ret,d[i] * (m-i+1));
    }
    return ret;
}
int main(int argc, const char * argv[]) {
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;++i)
            for(int j=1;j<=m;++j)
                scanf("%1d",&a[i][j]);
        for(int i=1;i<=m;++i)
            dp[i] = a[1][i] == 1 ;
        int ans = getAns(dp, m);
        for(int i=2;i<=n;++i){
            for(int j=1;j<=m;++j){
                if(a[i][j]==1)
                    dp[j]++;
                else
                    dp[j] = 0;
            }
            ans = max(ans,getAns(dp, m));
        }
        printf("%d\n",ans);
    }
    return 0;
}
