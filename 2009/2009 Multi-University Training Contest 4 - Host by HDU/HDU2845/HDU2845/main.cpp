//
//  main.cpp
//  HDU2845
//
//  Created by beMaster on 16/3/10.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 200000 + 10;
LL rowval[N],dp[N];
int a[N];
int main(int argc, const char * argv[]) {
    
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=1;i<=n;++i){
            for(int j=1;j<=m;++j){
                scanf("%d",&a[j]);
                if(j==1)
                    rowval[j] = a[j];
                else
                    rowval[j] = max(rowval[j-2] + a[j], rowval[j-1]);
            }
            
            if(i==1)
                dp[i] = rowval[m];
            else
                dp[i] = max(dp[i-2] + rowval[m], dp[i-1]);
        }
        cout<<dp[n]<<endl;
    }
    return 0;
}
