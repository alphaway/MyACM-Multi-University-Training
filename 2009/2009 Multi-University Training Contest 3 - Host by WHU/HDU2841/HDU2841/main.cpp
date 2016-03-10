#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
typedef long long LL;
const int N = 100000 + 1000;
bool isp[N];
int pri[N],total;
int pp[N][32],cnt[N];
void init(){
    total = 0;
    pri[total++] = 2;
    for(int i=3;i<N;++i) isp[i] = i&1;
    for(int i=3;i<N;i+=2)
        if(isp[i]){
            pri[total++] = i;
            for(int j=3*i;j<N;j+=2*i)
                isp[j] = false;
        }
}
void divide(int n){
    int tmp = n;
    for(int i=0;pri[i]<=tmp;++i){
        if(tmp%pri[i]==0){
            pp[n][cnt[n]++] = pri[i];
            while(tmp%pri[i]==0){
                tmp /= pri[i];
            }
        }
    }
    if(tmp>1)
        pp[n][cnt[n]++] = tmp;
}
void init2(){
    for(int i=2;i<=100000;++i){
        divide(i);
    }
}
void init22(){
    for(int i=0;pri[i]<=100000;++i){
        for(int j=1;j*pri[i]<=100000;++j)
            pp[j*pri[i]][cnt[j*pri[i]]++] = pri[i];
    }
}
int solve(int n, int m){
    int ret = 0;
    int bits,tmp;
    for(int s=1;s<(1<<cnt[n]);++s){
        tmp = 1;
        bits = 0;
        for(int i=0;i<cnt[n];++i){
            if(s&(1<<i)){
                bits++;
                tmp *= pp[n][i];
            }
        }
        if(bits&1)
            ret += m / tmp;
        else
            ret -= m / tmp;
    }
    return ret;
}
int main(){
    int t,n,m;
    scanf("%d",&t);
    init();
    //printf("%d %d\n",total,pri[total-1]);
    init2();
    LL ans;
    while(t--){
        scanf("%d%d",&n,&m);
        ans = m;
        for(int i=2;i<=n;++i)
            ans += m - solve(i, m);
        cout<<ans<<endl;
    }
    return 0;
}
