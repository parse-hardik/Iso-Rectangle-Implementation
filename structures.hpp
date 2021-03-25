#include <bits/stdc++.h>

struct Point{
    int x,y;
};

struct Interval{
    int bottom, top,id;
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

struct Ctree {
      int x;
      char side ; //L,R,U
      Ctree *left;
      Ctree *right;
      Ctree() : x(0), side('U'), left(nullptr), right(nullptr) {}
      Ctree(int a) : x(a), side('U'), left(nullptr), right(nullptr) {}
      Ctree(int a, char c) : x(a), side(c), left(nullptr), right(nullptr) {}
      Ctree(int a, char c , Ctree *left, Ctree *right) : x(a),side(c), left(left), right(right) {}
  };

struct StripeTree{
    Interval x_inter, y_inter;
    Ctree* tree;    
};


struct LRPS{
    vector<Interval> L, R;
    vector<int> P;
    vector<Stripe> S;
    vector<StripeTree> ST;
};