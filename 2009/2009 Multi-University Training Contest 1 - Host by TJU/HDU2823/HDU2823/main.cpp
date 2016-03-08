//
//  main.cpp
//  HDU2823
//
//  Created by beMaster on 16/3/6.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
const int N = 1000 + 10;
const double eps = 1e-10;
typedef struct Point{
    double x,y;
    Point(double x=0,double y=0):x(x),y(y){}
}Vector;
int dcmp(double x){
    if(fabs(x) < eps) return 0;
    return x < 0 ? -1 : 1;
}
Vector operator-(const Vector &a, const Vector &b){
    return Vector(a.x - b.x, a.y - b.y);
}
bool operator<(const Point &a, const Point&b){
    return a.x < b.x || (a.x==b.x && a.y < b.y);
}
bool operator==(const Point &a, const Point &b){
    return dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)==0;
}
double Cross(const Vector &a, const Vector &b){
    return a.x * b.y - a.y * b.x;
}
double Dot(const Vector &a, const Vector &b){
    return a.x * b.x + a.y * b.y;
}
double Length(const Vector &a){
    return  sqrt(Dot(a,a)) ;
}
double DistanceToSegment(Point p, Point a, Point b){
    if(a==b) return Length(p - a);
    Vector v1 = b - a, v2 = p - a, v3 = p - b;
    if(dcmp(Dot(v1,v2)) < 0) return Length(v2);
    else if(dcmp(Dot(v1,v3)) > 0) return Length(v3);
    else return fabs(Cross(v1,v2)) / Length(v1);
}
bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2){
    double c1 = Cross(a2-a1,b1-a1), c2 = Cross(a2-a1, b2-a1);
    double c3 = Cross(b2-b1, a1-b1), c4 = Cross(b2-b1, a2-b1);
    return dcmp(c1) * dcmp(c2) <0 && dcmp(c3) * dcmp(c4) < 0;
}
bool OnSegment(Point p, Point a1, Point a2){
    return dcmp(Cross(a1-p,a2-p)) ==0 && dcmp(Dot(a1-p,a2-p))<0;
}
bool SegmentIntersection(Point a1, Point a2, Point b1, Point b2)
{
    return SegmentProperIntersection(a1, a2, b1, b2) || OnSegment(a1, b1, b2) || OnSegment(a2, b1, b2);
}
Point a[N],b[N];
Point cha[N],chb[N];
int ConvexHull(Point *p, int n, Point *ch){
    int m = 0;
    sort(p,p+n);
    for(int i=0;i<n;++i){
        while(m>1 && Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0)m--;
        ch[m++] = p[i];
    }
    int k = m;
    for(int i=n-2;i>=0;--i){
        while(m>k &&Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0)m--;
        ch[m++] = p[i];
    }
    if(m>1) m--;
    return m;
}
int isPointInPolygon(Point p, Point *a, int n){
    int cnt = 0;
    for(int i=0;i<n;++i){
        if(OnSegment(p, a[i], a[(i+1)%n])) return -1;
        int k = Cross(a[(i+1)%n]-a[i], p-a[i]);
        int d1 = a[i].y - p.y;
        int d2 = a[(i+1)].y - p.y;
        if(k>0 &&d1<=0 &&d2>0)//点在线段的左侧
            cnt++;
        if(k<0 &&d2<=0 &&d1>0)//点在线段的右侧
            cnt++;
        //k==0，点和线段共线的情况不考虑
    }
    if(cnt&1)return 1;
    return 0;
}
//判断凸包是否相离
bool judge(Point *cha, int n1, Point *chb, int m1){
    if(n1==1 && m1==1){
        if(cha[0]==chb[0])
            return false;
    }
    else if(n1==1 && m1==2){
        if(OnSegment(cha[0], chb[0], chb[1]))
            return false;
    }
    else if(n1==2 && m1==1){
        if(OnSegment(chb[0], cha[0], cha[1]))
            return false;
    }
    else if(n1==2 && m1==2){
        if(SegmentIntersection(cha[0], cha[1], chb[0], chb[1]))
            return false;
    }
    else if(n1==2){
        for(int i=0;i<n1;++i)
            if(isPointInPolygon(cha[i], chb, m1))
                return false;
    }
    else if(m1==2){
        for(int i=0;i<m1;++i)
            if(isPointInPolygon(chb[i], cha, n1))
                return false;
    }
    else{
        for(int i=0;i<n1;++i){
            for(int j=0;j<m1;++j){
                if(SegmentIntersection(cha[i], cha[(i+1)%n1], chb[j], chb[(j+1)%m1]))
                    return false;
            }
        }
        for(int i=0;i<n1;++i)
            if(isPointInPolygon(cha[i], chb, m1))
                return false;
        for(int i=0;i<m1;++i)
            if(isPointInPolygon(chb[i], cha, n1))
                return false;
        
    }    return true;
}
double SegmentToSegment(Point a1, Point a2, Point b1, Point b2){
    //线段间的最短距离分为四种情况
    double t1 = DistanceToSegment(b1, a1, a2);
    double t2 = DistanceToSegment(b2, a1, a2);
    double t3 = DistanceToSegment(a1, b1, b2);
    double t4 = DistanceToSegment(a2, b1, b2);
    return min(t1,min(t2,min(t3,t4)));
}
//旋转卡壳求凸包最近距离
double solve(Point *P, Point *Q, int n, int m){
    if(n==1 && m==1){
        return Length(P[0] - Q[0]);
    }
    else if(n==1 && m==2){
        return DistanceToSegment(P[0], Q[0], Q[1]);
    }
    else if(n==2 && m==1){
        return DistanceToSegment(Q[0], P[0], P[1]);
    }
    else if(n==2 && m==2){
        return SegmentToSegment(P[0], P[1], Q[0], Q[1]);
    }
    int yminP = 0, ymaxQ = 0;
    for(int i=0;i<n;++i) if(P[i].y < P[yminP].y) yminP = i;
    for(int i=0;i<m;++i) if(Q[i].y > Q[ymaxQ].y) ymaxQ = i;
    P[n] = P[0];
    Q[n] = Q[0];
    double INF = 1e100;
    double arg, ans = INF;
    
    
    for(int i=0;i<n;++i){
        //当叉积负正转正时，说明点ymaxQ就是对踵点
        while((arg=Cross(P[yminP] - P[yminP+1],Q[ymaxQ+1] - Q[ymaxQ])) < -eps)
            ymaxQ = (ymaxQ+1)%m;
        double ret;
        
        if(arg > eps)//卡住第二个凸包上的点。
        {
            ret = DistanceToSegment(Q[ymaxQ], P[yminP], P[yminP+1]);
            ans  = min(ans,ret);
        }
        else//arg==0，卡住第二个凸包的边
        {
            ret = SegmentToSegment(P[yminP],P[yminP+1],Q[ymaxQ],Q[ymaxQ+1]);
            ans = min(ans,ret);
            
        }
        yminP = (yminP+1)%n;
        
    }
    return ans;
}
int main(int argc, const char * argv[]) {
   
    int n,m;
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=0;i<n;++i) scanf("%lf%lf",&a[i].x,&a[i].y);
        for(int i=0;i<m;++i) scanf("%lf%lf",&b[i].x,&b[i].y);
        //先求凸包
        int n1 = ConvexHull(a, n, cha);
        int m1 = ConvexHull(b, m, chb);
        //判断凸包是不是相离，如果不是，输出0
        if(judge(cha, n1, chb, m1)){
            printf("%.4lf\n",min(solve(cha, chb, n1, m1),solve(chb,cha,m1,n1)));
        }
        else
            printf("%.4lf\n",0.0);
    }
    return 0;
}
