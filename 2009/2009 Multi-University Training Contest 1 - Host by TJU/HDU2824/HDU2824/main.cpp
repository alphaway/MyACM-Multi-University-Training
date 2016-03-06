//
//  main.cpp
//  HDU2824
//
//  Created by beMaster on 16/3/4.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
typedef long long LL;
const int N = 3000000 + 10;
LL phi[N];
void phiTable(int n, LL *phi)
{
    int i, j;
    for (i = 2; i <= n; ++i) phi[i] = 0;
    phi[0] = 0;
    phi[1] = 1;
    for (i = 2; i <= n; ++i)
    {
        if (!phi[i])//素数肯定没有被筛过
            for (j = i; j <= n; j += i)
            {
                if (!phi[j]) phi[j] = j;
                phi[j] = phi[j] / i * (i - 1);//因为i是素数，即i是j的素数因子
            }
    }
}
int main(int argc, const char * argv[]) {
    phiTable(3000000, phi);
    for(int i=1;i<=3000000;++i)
        phi[i] += phi[i-1];
    int l,r;
    while(scanf("%d%d",&l,&r)!=EOF){
        cout<<(phi[r] - phi[l-1])<<endl;
    }
    return 0;
}
