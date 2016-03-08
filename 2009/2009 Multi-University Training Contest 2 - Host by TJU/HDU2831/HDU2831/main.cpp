//
//  main.cpp
//  HDU2831
//
//  Created by beMaster on 16/3/8.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <stdio.h>
using namespace std;
/*
 贪心
 vi - k * speed >= di
 vi - di >= k * speed
 所以按照vi - di  排序
 */
const int N = 100 + 10;
struct Node{
    int vi,di;
    int id;
    bool operator<(const Node&rhs)const{
        return (vi-di) < (rhs.vi -rhs.di);
    }
}a[N];
int main(int argc, const char * argv[]) {

    int n,speed;
    while(scanf("%d%d",&n,&speed)!=EOF){
        for(int i=1;i<=n;++i){
            scanf("%d%d",&a[i].vi,&a[i].di);
            a[i].id = i;
        }
        sort(a+1,a+n+1);
        bool flag = true;
        for(int i=1;i<=n;++i){
            if(a[i].vi - i * speed < a[i].di)
                flag = false;
        }
        if(flag){
            for(int i=1;i<=n;++i)
                printf("%d%c",a[i].id,i==n?'\n':' ');
        }
        else
            puts("The zombies eat your brains!");
    }
    return 0;
}
