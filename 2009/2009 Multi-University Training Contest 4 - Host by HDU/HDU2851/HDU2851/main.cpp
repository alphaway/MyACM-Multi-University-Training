//
//  main.cpp
//  HDU2851
//
//  Created by beMaster on 16/3/11.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
const int INF = 1<<30;
const int N = 2000 + 10;
struct Node{
    int l,r,w;
}a[N];
struct Node2{
    int v,dis;
    bool operator<(const Node2&rhs)const{
        return dis > rhs.dis;
    }
};
struct Edge{
    int to,next;
}g[N*N];
int head[N],e;
int d[N],val[N];
bool vis[N];
void addEdge(int u, int v){
    g[e].to =v;
    g[e].next = head[u];
    head[u] = e++;
}
void solve(int n){
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;++i)d[i] = INF;
    d[1] = val[1];
    priority_queue<Node2> q;
    Node2 cur,tmp;
    cur.v = 1,cur.dis = val[1];
    q.push(cur);
    while (!q.empty()) {
        cur = q.top(); q.pop();
        if(vis[cur.v])continue;
        vis[cur.v] = true;
        for(int i=head[cur.v];i!=-1;i=g[i].next){
            int v = g[i].to;
            if(d[v] > val[v] + d[cur.v]){
                tmp.dis = d[v] = val[v] + d[cur.v];
                tmp.v = v;
                q.push(tmp);
            }
        }
    }
}
int main(int argc, const char * argv[]) {
    
    int t,n,m;
    scanf("%d",&t);
    while(t--){
        memset(head,-1,sizeof(head));
        e = 0;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i){
            scanf("%d%d%d",&a[i].l,&a[i].r,&val[i]);
        }
        for(int i=1;i<=n;++i){
            for(int j=i+1;j<=n;++j)
                if(a[i].r>=a[j].l){
                    addEdge(i, j);
                }
        }
        solve(n);
        int des;
        for(int i=1;i<=m;++i){
            scanf("%d",&des);
            printf("%d\n",d[des]==INF?-1:d[des]);
        }
    }
    return 0;
}
