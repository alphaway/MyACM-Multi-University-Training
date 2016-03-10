//
//  main.cpp
//  HDU2846
//
//  Created by beMaster on 16/3/10.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;
const int N = 10000 + 10;
struct Node{
    int next[26];
    int fail;
    int flag;
    bool isword;
    int cnt;
    void init(){
        for(int i=0;i<26;++i) next[i] = -1;
        fail = 0;
        flag = -1;
        isword = false;
    }
}tree[3000000+10];
int size;
int cnt[3000000+10];
char str[10000+10][22];
char tmp[22];
int id[100000+10];


int insert(int cur, char *s){
    for(int i=0;s[i];++i){
        int idx = s[i] - 'a';
        if(tree[cur].next[idx]==-1){
            tree[++size].init();
            tree[cur].next[idx] = size;
        }
        cur = tree[cur].next[idx];
    }
    tree[cur].isword = true;
    cnt[cur] = 0;
    return cur;
}
void make_fail(int cur){
    queue<int> q;
    for(int i=0;i<26;++i)
        if(tree[cur].next[i]==-1)
            tree[cur].next[i] = 0;
        else{
            tree[tree[cur].next[i]].fail = 0;
            q.push(tree[cur].next[i]);
        }
    while(!q.empty()){
        cur = q.front();q.pop();
        for(int i=0;i<26;++i){
            if(tree[cur].next[i]==-1){
                tree[cur].next[i] = tree[tree[cur].fail].next[i];
            }
            else{
                tree[tree[cur].next[i]].fail = tree[tree[cur].fail].next[i];
                q.push(tree[cur].next[i]);
            }
        }
    }
}
void match(int cur, char *s, int which){
    for(int i=0;s[i];++i){
        int idx = s[i] - 'a';
        cur = tree[cur].next[idx];
        int tmp = cur;
        while(tree[tmp].fail!=0){
            tmp = tree[tmp].fail;
            if(tree[tmp].isword && tree[tmp].flag!=which){
                tree[tmp].flag = which;
                cnt[tmp]++;
            }
            
        }
        if(tree[cur].isword && tree[cur].flag!=which){
            tree[cur].flag = which;
            cnt[cur]++;
        }
    }
}
void findans(int cur, char *s){
    for(int i=0;s[i];++i){
        int idx = s[i] - 'a';
        cur = tree[cur].next[idx];
    }
    printf("%d\n",tree[cur].cnt);
}
int main(int argc, const char * argv[]) {

    int n,q;
    while(scanf("%d",&n)!=EOF){
        for(int i=0;i<n;++i) scanf("%s",str[i]);
        scanf("%d",&q);
        tree[size = 0].init();
        for(int i=0;i<q;++i){
            scanf("%s",tmp);
            id[i] = insert(0, tmp);
        }
        make_fail(0);
        for(int i=0;i<n;++i){
            match(0,str[i],i);
        }
        for(int i=0;i<q;++i){
            printf("%d\n",cnt[id[i]]);
        }
    }
    return 0;
}
