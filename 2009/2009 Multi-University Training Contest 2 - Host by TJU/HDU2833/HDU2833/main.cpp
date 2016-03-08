//
//  main.cpp
//  HDU2833
//
//  Created by beMaster on 16/3/8.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <queue>
#include <string.h>
using namespace std;
const int INF = 1<<30;
const int N = 500 + 10;
struct Node{
    int cur,dist;
    bool operator<(const Node&rhs)const{
        return dist >rhs.dist;
    }
};
int d1[N],d2[N];
bool vis[N];
int ma[N][N];
int dp[N][N];
void bfs(int st, int n,int *d){
    for(int i=1;i<=n;++i){
        vis[i] = 0;
        d[i] = INF;
    }
    d[st] = 0;
    priority_queue<Node> q;
    Node cur,tmp;
    cur.cur = st;
    cur.dist = 0;
    q.push(cur);
    while (!q.empty()) {
        cur = q.top();
        q.pop();
        if(vis[cur.cur]) continue;
        vis[cur.cur] = true;
        for(int i=1;i<=n;++i){
            if(ma[cur.cur][i]==0) continue;
            if(d[i] > d[cur.cur] + ma[cur.cur][i]){
                tmp.dist = d[i] = d[cur.cur] +ma[cur.cur][i];
                tmp.cur = i;
                q.push(tmp);
            }
        }
    }
}
int solve(int a, int b, int n){
    if(dp[a][b]!=-1)
        return dp[a][b];
    int v = 0;
    
    for(int i=1;i<=n;++i)
        if( d1[i] + ma[i][a] == d1[a])
            v = max(v, solve(i,b,n));
    for(int i=1;i<=n;++i)
        if(d2[i] + ma[i][b] == d2[b])
            v = max(v, solve(a,i,n));
    if(a==b)
        v++;
    dp[a][b] = v;
    
    return v;
}
int main(int argc, const char * argv[]) {
    int n,m;
    int a,b,c,d;
    while(scanf("%d%d",&n,&m),n+m){
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                ma[i][j] = INF;
        for(int i=1;i<=m;++i){
            int from,to,dis;
            scanf("%d%d%d",&from,&to,&dis);
            if(dis < ma[from][to])
                ma[from][to] = ma[to][from] = dis;
        }
        scanf("%d%d%d%d",&a,&b,&c,&d);
        bfs(a,n,d1);
        bfs(c,n,d2);
        /*
         dp[i][j]  表示第一个人从i走到a的路径与第二个人从j走到b的最短路径的最多交点有几个
         
         所以答案就是dp[b][d]
         */
        dp[a][c] = (a == c);
        memset(dp,-1,sizeof(dp));
        printf("%d\n",solve(b,d,n));
    }
    return 0;
}
