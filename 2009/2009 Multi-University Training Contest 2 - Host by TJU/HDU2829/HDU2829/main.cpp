//
//  main.cpp
//  HDU2829
//
//  Created by beMaster on 16/3/7.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int N = 1000 + 10;
int a[N];
int sum[N];
int dp[N][N];
int q[N],head,tail;
int n,m;
int getx(int k){
    return sum[k-1];
}
int gety(int k, int j){
    return dp[k][j-1];
}

/*
 dp[i][j] 第j次炸了i这个地方左边的铁路时，得到的最小值 j < i
 sum[i] 表示前i个数的和
 dp[i][j] = 
 min{ dp[k][j-1] - (sum[n-1] - sum[i-1]) * (sum[i-1] - sum[k-1])}
 = 
 dp[k][j-1] - sum[n-1]*sum[i-1] + sum[n-1] * sum[k-1] + sum[i-1]*sum[i-1]
 -sum[i-1]*sum[k-1]
 =
 dp[k][j-1]  + (sum[n-1] -sum[i-1]) * sum[k-1]
 G = dp[k][j-1] + (sum[n-1] -sum[i-1])  *sum[k-1]
dp[k][j-1] = -(sum[n-1] -sum[i-1])*sum[k-1] + G
 
 */
//g[k2,k1] > g[k3,k2] ,  那么k2是可舍弃的
int Cross(int x1, int y1, int x2, int y2, int x3, int y3){
    return (x2-x1) * (y3-y1) - (y2-y1)*(x3-x1);
}
int main(int argc, const char * argv[]) {
    
   
    while(scanf("%d%d",&n,&m),n+m){
        
        for(int i=0;i<n;++i)cin>>a[i];
            sum[0] = a[0];
        for(int i=1;i<n;++i) sum[i] = sum[i-1] + a[i];
        int total = 0;
        for(int i=0;i<n;++i)
            for(int j=i+1;j<n;++j)
                total += a[i] * a[j];
        if(m==0){
            cout<<total<<endl;
            continue;
        }
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;++i)
            dp[i][1] = total - sum[i-1] * (sum[n-1] - sum[i-1]);
        
        for(int j=2;j<=m;++j){
            
            head = tail = 0;
            q[tail++] = j - 1;
            //第j次选择爆炸的地点肯定是j开始，这样前面的j-1次爆炸才有地方选择
            for(int i=j;i<n;++i){
                int k = -(sum[n-1] - sum[i-1]);
                while(head+1<tail && (gety(q[head+1],j)-gety(q[head],j)) <= k*(getx(q[head+1])-getx(q[head])))
                    head++;
                //dp[k][j-1] - (sum[n-1] - sum[i-1]) * (sum[i-1] - sum[k-1])
                dp[i][j] = dp[q[head]][j-1] - (sum[n-1]-sum[i-1])*(sum[i-1]-sum[q[head]-1]);
                //dp[i][j] = dp[q[head]][j-1] + k * sum[q[head]];
                //dp[i][j] -= sum[n-1] - sum[i-1] + sum[i-1] * sum[i-1];
                
                
                while(head+1<tail && Cross(getx(q[tail-2]), gety(q[tail-2], j),getx(q[tail-1]),gety(q[tail-1], j),getx(i),gety(i, j))<=0)
                    tail--;
                q[tail++] = i;
            }
            /*
             0 1 2 3
             1 2 4 5
             */
        }
        int ans = 1<<30;
        for(int i=m;i<n;++i)
            ans = min(ans,dp[i][m]);
        cout<<ans<<endl;
    }
    return 0;
}
