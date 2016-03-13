//
//  main.cpp
//  HDU2857
//
//  Created by beMaster on 16/3/13.
//  Copyright © 2016年 beMaster. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
const double eps = 1e-5;

typedef struct Point{
    double x,y;
    Point(double x = 0, double y = 0):x(x),y(y){}
}Vector;
Vector operator-(Vector a, Vector b){
    return Vector(a.x-b.x,a.y-b.y);
}
Vector operator+(Vector a, Vector b){
    return Vector(a.x+b.x,a.y+b.y);
}
Vector operator*(Vector a, double p){
    return Vector(a.x*p, a.y*p);
}
int dcmp(double x){
    if(fabs(x)<eps)return 0;
    return x < eps ? -1 : 1;
}
Vector Rotate(const Vector &a, double rad){
    return Vector( a.x * cos(rad) - a.y * sin(rad), a.x * sin(rad) + a.y * cos(rad) );
}
double Cross(Vector a, Vector b){
    return a.x * b.y - a.y * b.x;
}
double Dot(Vector a, Vector b){
    return a.x * b.x + a.y * b.y;
}
double Length(Vector a){
    return sqrt(Dot(a, a));
}
Point GetLineProjection(Point p, Point a, Point b){
    Vector v = b - a;
    return a + v * (Dot(v, p-a) / Dot(v, v));
}
Point GetLineIntersection(Point p, Vector v, Point q, Vector w){
    Vector u = p - q;
    double t = Cross(w, u) / Cross(v, w);
    return p + v * t;
}

Point read_point(){
    Point ret;
    scanf("%lf%lf",&ret.x,&ret.y);
    return ret;
}
int main(int argc, const char * argv[]) {
    int t;
    Point p1,p2,ps,pe;
    scanf("%d",&t);
    while (t--) {
        p1 = read_point();
        p2 = read_point();
        ps = read_point();
        pe = read_point();
        
        Point projection = GetLineProjection(ps, p1, p2);
        Point pss = projection + (projection - ps);
        Point ans = GetLineIntersection(pe, pss-pe, p1, p2-p1);
        printf("%.3lf %.3lf\n",ans.x,ans.y);
        
        
    }
    return 0;
}
