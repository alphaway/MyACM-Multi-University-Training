//
//  main.cpp
//  HDU2847
//
//  Created by beMaster on 16/3/11.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long LL;
char str[22];
LL bToInt(char *str){
    int n = strlen(str);
    LL ret = 0,tmp = 1;
    for(int i=n-1;i>=0;--i){
        if(str[i]=='1')
            ret += tmp;
        tmp *= 2;
    }
    return ret;
}
int intToB(LL n, char *str){
    int i = 0;
    while(n){
        if(n&1)
            str[i] = '1';
        else
            str[i] = '0';
        i++;
        n>>=1;
    }
    str[i] = 0;
    reverse(str, str+i);
    return i;
}
bool dfs(char *lhs, int i, int n, char *rhs, int j,int m){
    
    if(n - i == m - j){
        while (lhs[i]) {
            if(lhs[i]!=rhs[j])
                return false;
            i++;
            j++;
        }
        return true;
    }
    if(lhs[i]==rhs[j]){
        return dfs(lhs,i+1,n,rhs,j+1,m);
    }
    else{
        return dfs(lhs,i,n,rhs,j+1,m);
    }
}
bool check(LL cur, LL target){
    char lhs[22],rhs[22];
    int n = intToB(cur, lhs);
    int m =intToB(target, rhs);
    //在lhs中添加0或者1，问能不能变成rhs
    return dfs(lhs, 0, n, rhs, 0, m);
}
int main(int argc, const char * argv[]) {
    LL n,k;
    while(scanf("%s",str)!=EOF){
        cin>>k;
        n = bToInt(str);
        if(n%k==0){
            puts(str);
        }
        else{
            int i =1;
            while(i*k < n) i++;
            LL target = i * k;
            while(true){
                if(check(n,target)){
                    char ans[22];
                    intToB(target, ans);
                    puts(ans);
                    break;
                }
                target += k;
            }
        }
    }
    return 0;
}
