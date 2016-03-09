//
//  main.cpp
//  HDU2838
//
//  Created by beMaster on 16/3/9.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long  LL;
struct Node{
    int id,val;
    bool operator<(const Node&rhs)const{
        return val > rhs.val;
    }
};
const int N = 100000 + 10;
int n;
Node a[N];
LL sum[N];
LL cnt[N];
int lowbit(int x){
    return x & -x;
}
void modify(int pos, int val, LL *tree){
    while(pos<=n){
        tree[pos] += val;
        pos += lowbit(pos);
    }
}
LL getsum(int pos, LL*tree){
    LL ret = 0;
    while(pos>0){
        ret += tree[pos];
        pos -= lowbit(pos);
    }
    return ret;
}
int main(int argc, const char * argv[]) {

    LL ans;
    while(scanf("%d",&n)!=EOF){
        memset(sum, 0, sizeof(sum));
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=n;++i){
            a[i].id = i;
            scanf("%d",&a[i].val);
            modify(i, a[i].val,sum);
            modify(i, 1, cnt);
        }
        sort(a+1,a+n+1);
        ans = 0;
        for(int i=1;i<=n;++i){
            LL tmp = getsum(n,sum) - getsum(a[i].id,sum);
            modify(a[i].id, -a[i].val,sum);
            LL c = getsum(n, cnt) - getsum(a[i].id, cnt);
            modify(a[i].id, -1, cnt);
            //printf("%d %d %d\n",a[i].id,tmp,c);
            ans += tmp + a[i].val * c;
        }
        cout<<ans<<endl;
    }
    return 0;
}
