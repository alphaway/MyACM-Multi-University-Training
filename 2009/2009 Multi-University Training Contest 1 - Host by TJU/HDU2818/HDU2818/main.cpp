//
//  main.cpp
//  HDU2818
//
//  Created by beMaster on 16/3/3.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <algorithm>
using namespace std;
const int N = 30000 + 10;
struct Query{
    char type[2];
    int x,y;
}q[1000000+10];
int fa[N],total[N],above[N];

int find(int x){
    if(x==fa[x]) return x;
    int tmp = find(fa[x]);
    above[x] += above[fa[x]];
    return fa[x] = tmp;
}
int main(int argc, const char * argv[]) {
    freopen("/Users/bemaster/Documents/Acm/多校/HDU2818/HDU2818/in.txt", "r", stdin);
    int p,n;
    while(scanf("%d",&p)!=EOF){
        n = 0;
        for(int i=0;i<p;++i){
            scanf("%s",q[i].type);
            if(q[i].type[0]=='M'){
                scanf("%d%d",&q[i].x,&q[i].y);

                n = max(n,q[i].y);
            }
            else{
                scanf("%d",&q[i].x);
                n = max(n,q[i].x);
            }
        }
        for(int i=0;i<=n;++i){
            fa[i] = i;
            total[i] = 1;
            above[i] = 0;
        }
        for(int i=0;i<p;++i){
            if(q[i].type[0]=='M'){
                int f1 = find(q[i].x);
                int f2 = find(q[i].y);
                if(f1!=f2){
                    fa[f2] = f1;
                    above[f2] += total[f1];
                    total[f1] += total[f2];
                }
            }
            else{
               
                int f = find(q[i].x);
                printf("%d\n",total[f] - above[q[i].x] - 1);
                
            }
        }
    }
    return 0;
}
