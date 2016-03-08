//
//  main.cpp
//  HDU2826
//
//  Created by beMaster on 16/3/7.
//  Copyright &#169; 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
/*
 判断两个任意的多边形是否相似
 */
typedef struct Point{
    int x,y;
    Point(int x = 0, int y = 0):x(x),y(y){}
}Vector;
Vector operator-(Vector a, Vector b){
    return Vector(a.x-b.x,a.y-b.y);
}
int Cross(Vector a, Vector b){
    return a.x * b.y - a.y * b.x;
}
int dis(Vector a){
    return a.x * a.x + a.y * a.y;
}
double Dot(Vector a, Vector b){
    return a.x * b.x + a.y * b.y;
}
double Length(Vector a){
    return sqrt(Dot(a, a));
}
double Angle(Vector a, Vector b){
    return Dot(a, b) / Length(a) / Length(b);
}
const int N = 300 + 10;
Point a[N],b[N];
int main(int argc, const char * argv[]) {
    
    int n;
    while(scanf("%d",&n)!=EOF){
        for(int i=0;i<n;++i) scanf("%d%d",&a[i].x,&a[i].y);
        for(int i=0;i<n;++i) scanf("%d%d",&b[i].x,&b[i].y);
        if(n==1||n==2){
            puts("Yes");
            continue;
        }
        bool f1 = false;
        //枚举哪个点作为第二个多边形的起点
        for(int k=0;k<n;++k){
            
            bool f2 = true;
            
            for(int i=0,j=k;i<n;++i,++j){
                int i1 = (i+1)%n, i2 = (i+2)%n;
                int j1 = (j+1)%n, j2 = (j+2)%n;
                //两个多边形相邻两边的比值相同，相邻两边的夹角相等
                bool flag1 = dis(a[i] - a[i1]) * dis(b[j1]-b[j2])
                == dis(b[j]-b[j1]) * dis(a[i1]-a[i2]);
                bool flag2 = Angle(a[i1]-a[i], a[i2]-a[i]) == Angle(b[j1]-b[j], b[j2]-b[j]);
                if(flag1 && flag2) continue;
                f2 = false;
                break;
            }
            if(f2){
                f1 = f2;
                break;
            }
        }
        if(f1)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}