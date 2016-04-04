//
//  main.cpp
//  HDU4607
//
//  Created by beMaster on 16/4/4.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
const int N = 100000 + 10;
vector<int> g[N];
int p1,p2;
int d;
void dfs(int u, int fa, int dep, int &p){
    if(dep > d){
        p = u;
        d = dep;
    }
    for(int i=0;i<g[u].size();++i){
        int v = g[u][i];
        if(v==fa) continue;
        dfs(v, u, dep+1, p);
    }
}
int main(int argc, const char * argv[]) {
    
    int t,n,m,k;
    int u,v;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)
            g[i].clear();
        
        for(int i=0;i<n-1;++i){
            scanf("%d%d",&u,&v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        d = 0;
        dfs(1, -1, 0, p1);
        d = 0;
        dfs(p1, -1, 0, p2);
        d++;//最长链上点的个数
        while(m--){
            scanf("%d",&k);
            if(k<=d){
                printf("%d\n",k-1);
            }
            else{
                printf("%d\n",(k-d)*2+d-1);
            }
        }
    }
    
    return 0;
}
