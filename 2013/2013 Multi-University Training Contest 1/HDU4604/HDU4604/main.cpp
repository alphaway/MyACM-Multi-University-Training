#include <stdio.h>
#include <algorithm>
#include <map>
#include <string.h>
using namespace std;
const int N = 100000 + 10;
int a[N],b[N];
int cnt[2][N];
int len[2][N];
int dp[2][N];
int st[2][N];
map<int,int> haxi;
//st非严格递增， 找到第一个大于key自己的数
int bs(int *st, int top, int key){
    int l = 0, r = top;
    while(l<r){
        int mid = (l+r)>>1;
        if(st[mid] > key){
            r = mid;
        }
        else{
            l = mid + 1;
        }
    }
    return l;
}
//st非严格递减，找到第一个小于key的数
int bs2(int *st, int top, int key){
    int l = 0, r = top;
    while(l<r){
        int mid = (l+r)>>1;
        if(st[mid]<key){
            r = mid;
        }
        else{
            l = mid + 1;
        }
    }
    return l;
}
int solve(int n){
    //st[0]
    memset(cnt,0,sizeof(cnt));
    int top1 = 0, top2 = 0;
    st[0][0] = st[1][0] = haxi[a[n-1]];
    dp[0][n-1] = dp[1][n-1] = 1;
    cnt[0][haxi[a[n-1]]]++;
    len[0][n-1] = 1;
    cnt[1][haxi[a[n-1]]]++;
    len[1][n-1] = 1;
    for(int i=n-2;i>=0;--i){
        int aa = haxi[a[i]];
        if(aa >= st[0][top1]){
            st[0][++top1] = aa;
            dp[0][i] = top1 + 1;
        }
        else{
            int pos = bs(st[0],top1,aa);
            cnt[0][st[0][pos]]--;
            st[0][pos] = aa;
            dp[0][i] = pos + 1;
        }
        cnt[0][aa]++;
        len[0][i] = cnt[0][aa];
        if(aa<=st[1][top2]){
            st[1][++top2] = aa;
            dp[1][i] = top2 + 1;
        }
        else{
            int pos = bs2(st[1],top2,aa);
            cnt[1][st[1][pos]]--;
            st[1][pos] = aa;
            dp[1][i] = pos + 1;
        }
        cnt[1][aa]++;
        len[1][i] = cnt[1][aa];
    }
    
    int ans = 0;
    for(int i=0;i<n;++i){
        //printf("%d %d %d %d\n",dp[0][i],dp[1][i], len[0][i], len[1][i]);
        ans = max(ans, dp[0][i]+dp[1][i] - min(len[0][i],len[1][i]));
    }
    
    return ans;
           
}
/*
 问题是怎么求子序列开头相同的数有几个
 
 */
int main(){
    int t,n;
    scanf("%d",&t);
    while(t--){
        haxi.clear();
        scanf("%d",&n);
        for(int i=0;i<n;++i){
            scanf("%d",&a[i]);
            b[i] = a[i];
        }
        sort(b,b+n);
        int m = unique(b,b+n) - b;
        for(int i=0;i<m;++i)
            haxi[b[i]] = i + 1;
        
        int ans = solve(n);
        printf("%d\n",ans);
    }
}
           