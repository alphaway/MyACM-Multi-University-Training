//
//  main.cpp
//  HDU2821
//
//  Created by beMaster on 16/3/6.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 25 + 10;
char ma[N][N];
int a[N][N];
char path[N];
bool flag;
int xx,yy;
//上下左右
int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};
int n,m;
char getDir(int i){
    if(i==0)return 'U';
    if(i==1)return 'D';
    if(i==2)return 'L';
    return 'R';
}
bool judge(int x, int y, int i, int &tx, int &ty){//判断该方向上有没有方块
    x += dx[i];
    y += dy[i];
    //如果下一个位置不是空格，那么就不行
    if(x+dx[i]>=0 && x+dx[i]<n && y+dy[i]>=0 && y+dy[i]<m && a[x][y]!=0)
        return false;
    while(x+dx[i]>=0 && x+dx[i]<n && y+dy[i]>=0 && y+dy[i]<m){
        x += dx[i];
        y += dy[i];
        if(a[x][y]!=0){
            tx = x, ty = y;
            return true;
        }
    }
    return false;
}
bool dfs(int x, int y, int res,int step){
    if(res==0){
        printf("%d\n%d\n",xx,yy);
        for(int i=0;i<step;++i)
            printf("%c",path[i]);
        puts("");
        flag = true;
    }
    if(flag)return true;
    //选择一个方向
    for(int i=0;i<4;++i){
        int tx,ty;
        if(judge(x, y, i,tx,ty)){//如果该方向上有方块
            path[step] = getDir(i);
            int type = ma[tx][ty] == 1 ? 1 : 2;//该位置是有一个方块还是一堆方块
            if(type==1){
                a[tx][ty] = 0;
                if(!dfs(tx,ty,res-1,step+1)){
                    a[tx][ty] = 1;
                }
                else
                    return true;
            }
            else{
                int tmp = a[tx][ty];
                int ttx = tx + dx[i];
                int tty = ty + dy[i];
                bool flag = false;
                if(ttx>=0 && ttx<n && tty>=0 && tty <m){
                    flag =  true;
                    a[ttx][tty] += tmp - 1;
                }
                a[tx][ty] = 0;
                if(!dfs(tx,ty,res-1,step+1)){
                    a[tx][ty] = tmp;
                    if(flag)
                        a[ttx][tty] -= tmp - 1;
                }
                else
                    return true;
            }
        }
    }
    return false;
}
int main(int argc, const char * argv[]) {
    freopen("/Users/bemaster/Documents/Acm/MyACM-Multi-University-Training/2009/2009 Multi-University Training Contest 1 - Host by TJU/HDU2821/HDU2821/in.txt", "r", stdin);
    while(scanf("%d%d",&m,&n)!=EOF){
        for(int i=0;i<n;++i)
            scanf("%s",ma[i]);
        int res = 0;
        flag = false;
        for(int i=0;i<n;++i)
            for(int j=0;j<m;++j)
                if(ma[i][j]=='.')
                    a[i][j] = 0;
                else{
                     a[i][j] = ma[i][j] - 'a' + 1;
                    res += a[i][j];
                }
                   
                   
        for(int i=0;i<n;++i){
            for(int j=0;j<m;++j){
                if(a[i][j] == 0 ){
                    xx = i,yy = j;
                    if(dfs(i,j,res,0))
                        flag = true;
                }
                if(flag)break;
            }
            if(flag)break;
        }
    }
    return 0;
}
