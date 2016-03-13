//
//  main.cpp
//  HDU2861
//
//  Created by beMaster on 16/3/13.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
using namespace std;
typedef unsigned long long  LL;
LL a[200+10][200+10][20+10];
LL b[200+10][200+10][20+10];
/*

 */
void init(){
    a[1][0][1] = 1;
    b[1][1][1] = 1;
    for(int i=2;i<=200;++i){
        for(int j=0;j<=i;++j){
            for(int k=1;k<=20;++k){
                a[i][j][k] = a[i-1][j][k] + b[i-1][j][k-1];
                if(j)
                    b[i][j][k] = a[i-1][j-1][k-1] + b[i-1][j-1][k];
            }
        }
    }
}
int main() {
    init();
    int n,m,k;
    while(scanf("%d%d%d",&n,&m,&k)!=EOF){
        cout<<a[n][m][k] + b[n][m][k]<<endl;
    }
    return 0;
}
