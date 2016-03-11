//
//  main.cpp
//  HDU2852
//
//  Created by beMaster on 16/3/11.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <set>
using namespace std;
const int N = 100000+10;
int tree[N];
int lowbit(int x){
    return x & -x;
}
int getsum(int pos){
    int ret = 0;
    while (pos>0) {
        ret += tree[pos];
        pos -= lowbit(pos);
    }
    return ret;
}
void modify(int pos, int val){
    while(pos < N){
        tree[pos] += val;
        pos += lowbit(pos);
    }
}
int main(int argc, const char * argv[]) {
    int m,type,e,a,k;
    while(scanf("%d",&m)!=EOF){
        memset(tree,0,sizeof(tree));
        for(int i=0;i<m;++i){
            scanf("%d",&type);
            if(type==0){
                scanf("%d",&e);
                modify(e, 1);
            }
            else if(type==1){
                scanf("%d",&e);
                int ret;
                if(e==1){
                    ret = getsum(e);
                }
                else{
                    ret = getsum(e) - getsum(e-1);
                }
                if(ret==0){
                    puts("No Elment!");
                }
                else{
                    modify(e, -1);
                }
            }
            else{
                bool flag = false;
                scanf("%d%d",&a,&k);
                int low = a, high = N - 1;
                while(low <= high){
                    int mid = (low + high)>>1;
                    int ret = getsum(mid) - getsum(a);
                    if(ret>=k){
                        high = mid - 1;
                        flag = true;
                    }
                    else if(ret < k){
                        low = mid + 1;
                    }
                    
                }
                if(flag)
                    printf("%d\n",low);
                else
                    puts("Not Find!");
                
            }
        }
    }
    return 0;
}
