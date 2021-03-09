#include <bits/stdc++.h>

struct Point{
    int x,y;
};

struct Interval{
    int bottom, top;
};

struct LineSegment{
    Interval inter;
    int coord;
};

struct Rectangle{
    Interval x_inter, y_inter;
};

struct Edge{
    Interval inter;
    int coord;
    char side;//L,R,T,B
};

struct Stripe{
    Interval x_inter, y_inter;
    vector<Interval> x_union;
};

struct LRPS{
    vector<Interval> L, R;
    vector<int> P;
    vector<Stripe> S;
};