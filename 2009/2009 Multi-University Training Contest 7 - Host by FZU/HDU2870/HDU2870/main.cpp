//
//  main.cpp
//  HDU2870
//
//  Created by beMaster on 16/3/14.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
const int N = 1000 + 10;
char ma[N][N];
int height[N];
int l[N],r[N];
char alphabet[] = {'a','b','c','w','x','y','z' };
bool canChange(char from, char to){
    if(from=='w' && (to=='a' || to=='b'))return true;
    if(from=='x' && (to=='b' || to=='c'))return true;
    if(from=='y' && (to=='a' || to=='c'))return true;
    if(from=='z' && (to=='a' || to=='c'))return true;
    return false;
}
int getMax(int m){
    int ret = 0;
    //l[i],r[i]表示以height[i]为高度子矩阵，往左和往右最远能延伸到的地方
    //那么答案就是最大(r[i]-l[i]+1)*height
    l[1] = 1;
    r[m] = m;
    for(int j=2;j<=m;++j){
        int idxL = j;
        while(height[j]!=0 && height[j] <= height[idxL-1]){
            idxL = l[idxL-1];
        }
        l[j] = idxL;
    }
    for(int j=m-1;j>=1;--j){
        int idxR = j;
        while (height[j]!=0 && height[j] <= height[idxR+1]) {
            idxR = r[idxR+1];
        }
        r[j] = idxR;
    }
    for(int j=1;j<=m;++j)
        ret = max(ret,(r[j]-l[j]+1)*height[j]);
    return ret;
}
int main(int argc, const char * argv[]) {
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF){
        int ans = 0;
        for(int i=1;i<=n;++i)scanf("%s",ma[i]+1);
        for(int k=0;k<7;++k){//枚举是哪种字符的子矩阵最大
            //height[j]表示以某一行为底的，第j列连续向上的某种字符的个数
            memset(height,0,sizeof(height));
            for(int i=1;i<=n;++i){
                //算出以第i行为底的height数组
                for(int j=1;j<=m;++j){
                    if(ma[i][j]==alphabet[k] || canChange(ma[i][j], alphabet[k]))
                        height[j]++;
                    else
                        height[j] = 0;
                    
                }
                //在height数组上计算最大的子矩阵
                ans = max(ans,getMax(m));
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
