//
//  main.cpp
//  HDU4602
//
//  Created by beMaster on 16/4/4.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <stdio.h>
using namespace std;
const int MOD = 1000000007;
typedef long long LL;

/*
 int path[1000];
 int cnt[100];
 void dfs(int n, int cur){
 if(n==0){
 for(int i=0;i<cur;++i){
 printf("%d ",path[i]);
 cnt[path[i]]++;
 }
 puts("");
 return;
 }
 for(int i=1;i<=n;++i){
 path[cur] = i;
 dfs(n-i,cur+1);
 }
 }
 */
LL quick(LL a, int k){
    LL ret = 1;
    while(k){
        if(k&1)
            ret = ret * a % MOD;
        a = a * a % MOD;
        k>>=1;
    }
    return ret;
}
int main(int argc, const char * argv[]) {
    int t,n,k;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&k);
        if(k>n)
            cout<<0<<endl;
        else if(k==n)
            cout<<1<<endl;
        else if(k==n-1)
            cout<<2<<endl;
        else{
            int kk = n - 1 - k;
            LL ans = quick(2,kk) * 2 + kk * quick(2,kk-1);
            ans %= MOD;
            cout<<ans<<endl;
        }
    }
    return 0;
}
