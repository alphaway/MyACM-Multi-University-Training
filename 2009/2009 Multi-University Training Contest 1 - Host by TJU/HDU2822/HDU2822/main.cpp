//
//  main.cpp
//  HDU2822
//
//  Created by beMaster on 16/3/4.
//  Copyright © 2016年 beMaster. All rights reserved.
//
/*
4 3
x.x
...
x..
x..
x.x
1 3
4 3
 */
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
const int N = 1000+10;
char ma[N][N];
int vis[N][N];
struct Node{
    int x,y;
    int step;
    bool operator<(const Node&rhs)const{
        return step > rhs.step;
    }
};
priority_queue<Node> Q;
int n,m;
int dx[4] = {-1,0,1,0};
int dy[4] = {0,-1,0,1};
void getPoint(Node a){
    queue<Node> q;
    q.push(a);
    Node tmp;
    tmp.step = a.step;
    vis[a.x][a.y] = 1;
    while(!q.empty()){
        a = q.front();
        q.pop();
        Q.push(a);
        for(int i=0;i<4;++i){
            tmp.x = a.x + dx[i];
            tmp.y = a.y + dy[i];
            if(tmp.x >=0 && tmp.x < n && tmp.y>=0 && tmp.y<m && ma[tmp.x][tmp.y]=='X' && vis[tmp.x][tmp.y]!=1){
                vis[tmp.x][tmp.y] = 1;
                q.push(tmp);
            }
        }
    }
}
void getPoint2(Node a){
    queue<Node> q;
    Node tmp;
    q.push(a);
    vis[a.x][a.y] = 2;
    while(!q.empty()){
        a = q.front();
        q.pop();
        for(int i=0;i<4;++i){
            tmp.x = a.x + dx[i];
            tmp.y = a.y + dy[i];
             if(tmp.x >=0 && tmp.x < n && tmp.y>=0 && tmp.y<m && ma[tmp.x][tmp.y]=='X' &&  vis[tmp.x][tmp.y]!=2){
                 vis[tmp.x][tmp.y] = 2;
                 q.push(tmp);
             }
        }
    }
}
int bfs(){
    Node cur,tmp;
    while(!Q.empty()){
        cur = Q.top();
        Q.pop();
               for(int i=0;i<4;++i) {
            tmp.x = cur.x + dx[i];
            tmp.y = cur.y + dy[i];
            if(tmp.x>=0 && tmp.x<n && tmp.y>=0 && tmp.y<m && vis[tmp.x][tmp.y]!=1){
                
                if(ma[tmp.x][tmp.y]=='X'){
                    tmp.step = cur.step;

                    if(vis[tmp.x][tmp.y]==2)
                        return tmp.step;
                    getPoint(tmp);
                }
                else{
                    tmp.step = cur.step+1;
                    Q.push(tmp);
                    

                    vis[tmp.x][tmp.y] = 1;
                }
            }
        }
    }
    return 0;
}
int main(int argc, const char * argv[]) {
    freopen("/Users/bemaster/Documents/Acm/多校/HDU2822/in.txt", "r", stdin);
    while(scanf("%d%d",&n,&m),n+m){
        memset(vis,0,sizeof(vis));
        for(int i=0;i<n;++i)
            scanf("%s",ma[i]);
        Node a,b;
        scanf("%d%d%d%d",&a.x,&a.y,&b.x,&b.y);
        a.x--,a.y--,b.x--,b.y--;
        while(!Q.empty()) Q.pop();
        
        a.step = 0;
        getPoint(a);
        getPoint2(b);
       
        printf("%d\n",bfs());
        
    }
    return 0;
}
