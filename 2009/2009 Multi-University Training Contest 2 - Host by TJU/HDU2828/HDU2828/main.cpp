//
//  main.cpp
//  HDU2828
//
//  Created by beMaster on 16/3/8.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
const int N = 500 + 10;
int ma[N][N];
int cy[N];
bool vis[N];
bool dfs(int cur, int m){
    for(int i=1;i<=m;++i){
        if(vis[i] || ma[cur][i]==0) continue;
        vis[i] = true;
        /*
         因为一个开关最多控制两个灯
         所以当前开关没被使用，即cy[i]==-1 ,那么就控制cur
         如果被使用了，那么判断使用的状态符不符合当前灯即ma[cur][i]==ma[cy[i]][i] 
         如果不符合，让cy[i]这个灯去寻找增广路
         
         */
        if(cy[i]==-1 || ma[cur][i]==ma[cy[i]][i] || dfs(cy[i], m)){
            cy[i] = cur;
            return true;
        }
    }
    return false;
}
int max_match(int n, int m){
    int ret = 0;
    memset(cy,-1,sizeof(cy));
    for(int i=1;i<=n;++i){
        memset(vis,0,sizeof(vis));
        ret += dfs(i, m);
    }
    return ret==n;
}
int main(int argc, const char * argv[]) {
    int n,m,k;
    char state[4];
    int idx;
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(ma,0,sizeof(ma));
        for(int i=1;i<=n;++i){
            scanf("%d",&k);
            for(int j=0;j<k;++j){
                scanf("%d%s",&idx,state);
                
                ma[i][idx] = state[1] == 'F' ? 1 : 2;
            }
        }
        bool ans = max_match(n, m);
        if(ans){
            for(int i=1;i<=m;++i){
                if(cy[i]==-1)
                    printf("ON");
                else
                    printf("%s",ma[cy[i]][i]==1? "OFF":"ON");
                printf("%c",i==m?'\n':' ');
            }
        }
        else
            printf("-1\n");
    }
    return 0;
}
