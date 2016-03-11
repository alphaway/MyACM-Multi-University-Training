//
//  main.cpp
//  HDU2850
//
//  Created by beMaster on 16/3/11.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;
const int N = 100000 + 10;
struct Server{
    int total;
    int id;
    bool operator <(const Server &rhs)const{
        return total > rhs.total;
    }
}a[N];
struct Job{
    int T;
    int id;
    int which;
}b[N];
bool CmpT(Job &lhs, Job &rhs){
    return lhs.T > rhs.T;
}

bool CmpId(Job &lhs, Job &rhs){
    return lhs.id < rhs.id;
}
priority_queue<Server> Q;
/*
简直日了狗， 少输出了一个n，一直wa，然后在找哪里错了。
 
 贪心的做法，下面这个数据会错
 1
 6 2
 100000 100000 98000 98000 4000
 */
int tt[100+10];
int main(int argc, const char * argv[]) {
    int t,n,m;
    scanf("%d",&t);
    while (t--) {
        scanf("%d%d",&n,&m);
        while (!Q.empty()) {
            Q.pop();
        }
        for(int i=0;i<m;++i){
            Server tmp;
            tmp.id = i;
            tmp.total = 0;
            Q.push(tmp);
        }
        for(int i=0;i<n;++i){
            scanf("%d",&b[i].T);
            b[i].id = i;
        }
        sort(b,b+n,CmpT);
        
        memset(tt, 0, sizeof(tt));
        for(int i=0;i<n;++i){
            Server tmp = Q.top(); Q.pop();
            b[i].which = tmp.id;
            tt[tmp.id] += b[i].T;
            tmp.total += b[i].T;
            Q.push(tmp);
        }
     

        
        sort(b,b+n,CmpId);
        printf("%d\n",n);
        for(int i=0;i<n;++i)
                printf("%d%c",b[i].which,i==n-1?'\n':' ');
        
}
    return 0;
}
