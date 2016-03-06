//
//  main.cpp
//  HDU2819
//
//  Created by beMaster on 16/3/4.
//  Copyright &#169; 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
const int N = 100 + 10;
int a[N][N];
int cy[N];
int cx[N];
bool vis[N];
int cnt;
int x[1111],y[1111];
bool find(int cur, int n){
    for(int i=0;i<n;++i){
        if(a[cur][i]==1 && !vis[i]){
            vis[i] = true;
            if(cy[i]==-1 || find(cy[i],n)){
                cy[i] = cur;
                cx[cur] = i;
                return true;
            }
        }
    }
    return false;
}
bool max_match(int n){
    memset(cy,-1,sizeof(cy));
    for(int i=0;i<n;++i){
        memset(vis,0,sizeof(vis));
        if(!find(i,n))
            return false;
    }
    return true;
}
void insert_sort(int n){
    //cy[i] 表示第i列为第cy[i]行占据
    for(int i=0;i<n;++i){
        int idx = i;
        for(int j=i+1;j<n;++j){
            if(cx[j] < cx[idx])
                idx = j;
        }
        if(i!=idx){
            x[cnt] = i+1;
            y[cnt] = idx+1;
            cnt++;
            swap(cx[i],cx[idx]);
        }
        
    }
}
int main(int argc, const char * argv[]) {
    int n;
    while(scanf("%d",&n)!=EOF){
        for(int i=0;i<n;++i){
            for(int j=0;j<n;++j)
                scanf("%d",&a[i][j]);
        }
        if(max_match(n)){
            cnt = 0;
            insert_sort(n);
            printf("%d\n",cnt);
            for(int i=0;i<cnt;++i)
                printf("R %d %d\n",x[i],y[i]);
        }
        else
            puts("-1");
        
    }
    return 0;
}