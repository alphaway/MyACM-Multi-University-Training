//
//  main.cpp
//  HDU2825
//
//  Created by beMaster on 16/3/4.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;
const int MOD = 20090717;
const int MAX = 26;
const int N = 222 + 10;
char str[111];
struct Node{
    int next[MAX];
    int fail;
    int wordId;
    void init(){
        fail = 0;
        wordId = 0;
        for(int i=0;i<MAX;++i)
            next[i] = -1;
    }
}Trie[N];
int size;
void insert(int root, char *str, int id){
    int idx, cur = root;
    for(int i=0;str[i];++i){
        idx = str[i] - 'a';
        if(Trie[cur].next[idx]==-1){
            Trie[size].init();
            Trie[cur].next[idx] = size++;
        }
        cur = Trie[cur].next[idx];
    }
    Trie[cur].wordId = (1<<id);
}
/*
 bfs构建trie,trie图的特点是不仅有fail指针，没有后续结点的next域也不为空，
 所以具有确定性
 失配指针的作用是当该结点的儿子不是所要匹配的结点，那么就跳过当前串的最长后缀
 */
void make_fail(int root){
    queue<int> q;
    //顶点为第一层，所以这里是构建第二层的fail指针，因为第二层比较特殊
    for(int i=0;i<MAX;++i){
        if(Trie[root].next[i] ==-1)
            Trie[root].next[i] = root;
        else{
            Trie[Trie[root].next[i]].fail = root;
            q.push(Trie[root].next[i]);//如果有后续结点，则继续构建后续结点
        }
    }
    while(!q.empty()){
        int cur = q.front(); q.pop();
        for(int i=0;i<MAX;++i){
            int son = Trie[cur].next[i];
            int cur_fail = Trie[cur].fail;
            if(son==-1){
                Trie[cur].next[i] = Trie[cur_fail].next[i];
            }
            else{
                Trie[son].fail = Trie[cur_fail].next[i];
                Trie[son].wordId |= Trie[Trie[son].fail].wordId;
                q.push(son);
            }
        }
    }
}

/*
 dp[i][j][s]表示密码的长度为i时，若干个个word的状态压缩是s，在状态j的方法数
 
 */
int dp[25+10][100+10][2048+10];
int main(int argc, const char * argv[]) {
    freopen("/Users/bemaster/Documents/Acm/多校/HDU2825/HDU2825/in.txt", "r", stdin);
    int n,m,k;//m个单词， 长度为n的密码至少包含k个单词
    while(scanf("%d%d%d",&n,&m,&k),n+m+k){
        size = 1;
        Trie[0].init();
        Trie[0].fail = 0;
        for(int i=0;i<m;++i){
            scanf("%s",str);
            insert(0, str, i);
        }
        make_fail(0);

        int S = (1<<m) - 1;//这里应该是m，而不是k，因为超过k的状态也是要算的
        for(int i=0;i<=n;++i)
            for(int j=0;j<size;++j)
                for(int s=0;s<=S;++s)
                    dp[i][j][s] = 0;
        dp[0][0][0] = 1;
        for(int i=0;i<n;++i){
            for(int j=0;j<size;++j){
                for(int s=0;s<=S;++s){
                    if(dp[i][j][s]==0)continue;
                        for(int idx=0;idx<MAX;++idx){
                            int son = Trie[j].next[idx];
                            int tmp = s | Trie[son].wordId;
                            dp[i+1][son][tmp] += dp[i][j][s];
                            dp[i+1][son][tmp] %= MOD;
                        }
                }
            }
        }
        int ans = 0;
        for(int s=0;s<=S;++s){
            int cnt = 0;
            int i = s;
            while(i)
            {
                if(i&1)cnt++;
                i>>=1;
            }
            if(cnt>=k){
                for(int j=0;j<size;++j)
                    ans = (ans +dp[n][j][s])%MOD;
            }
                
        }
        printf("%d\n",ans);
    }
    return 0;
}
