#include <bits/stdc++.h>

struct Point{
    int x,y;
};

struct Interval{
    int bottom, top;
   
    // Interval(int b, int t){
    //     bottom = b, top = t;
    // }
};

struct LineSegment{
    Interval inter;
    int coord;
    // LineSegment(Interval in, int co){
    //     inter = in, coord = co;
    // }
};

struct Rectangle{
    Interval x_inter, y_inter;
    // Rectangle(Interval x, Interval y){
    //     x_inter = x, y_inter = y;
    // }
};

struct Edge{
    Interval inter;
    int coord;
    char side;//L,R,T,B
    // Edge(Interval in, int co, char c){
    //     inter = in;
    //     coord = co;
    //     side = c;
    // }
};

struct Stripe{
    Interval x_inter, y_inter;
    vector<Interval> x_union;
    // Stripe(Interval x, Interval y,  vector<Interval> sx){
    //     x_inter = x, y_inter = y;
    //     x_union = sx;
    // }
};

struct LRPS{
    vector<Interval> L, R;
    vector<int> P;
    vector<Stripe> S;
    // LRPS(vector<Interval> el,  vector<Interval> ar, vector<int> pi , vector<Stripe> es){
    //     L=el;
    //     R=ar;
    //     P=pi;
    //     S=es;
    // }
};