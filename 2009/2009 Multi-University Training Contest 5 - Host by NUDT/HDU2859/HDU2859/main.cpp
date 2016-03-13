//
//  main.cpp
//  HDU2859
//
//  Created by beMaster on 16/3/13.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
using namespace std;
const int N = 1000 + 10;
/*
 找出最大的一个子矩阵，该子矩阵关于左下角到右上角的对角线对称。
 */
char ma[N][N];
int dp[N][N];
int main(int argc, const char * argv[]) {
    int n;
    while(scanf("%d",&n),n){
        for(int i=1;i<=n;++i)
            scanf("%s",ma[i]+1);
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j){
                int ii = i - 1, jj = j+1;
                while (ii>=1 && jj<=n) {
                    if(ma[ii][j] == ma[i][jj])
                        dp[i][j]++;
                    else
                        break;
                    ii--;
                    jj++;
                }
            }
        int ans = 1;
        int cnt;
        for(int k=1;k<=n;++k){
            int i = 1, j = k;
            cnt = 0;
            while(j-1>=1){
                i++;
                j--;
                if(dp[i][j]>cnt){
                    cnt++;
                    ans = max(ans,cnt+1);
                }
                else{
                    cnt = dp[i][j];
                }
            }
        }
        for(int k=1;k<=n;++k){
            int i = k, j = n;
            cnt = 0;
            while(i+1<=n){
                i++;
                j--;
                if(dp[i][j]>cnt){
                    cnt++;
                    ans = max(ans,cnt+1);
                }
                else{
                    cnt = dp[i][j];
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
