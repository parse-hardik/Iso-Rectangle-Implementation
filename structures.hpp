#include <bits/stdc++.h>
#include <unordered_set>

class Point{
    int x,y;
}

class Interval{
    int bottom, top;
    Interval(int b, int t){
        bottom = b, top = t;
    }
}

class Line{
    Interval in;
    int coord;
    Line(Interval inter, int co){
        in = inter, coord = co;
    }
}

class Rectangle{
    Interval x_int, y_int;
    Recatngle(Interval x, Interval y){
        x_int = x, y_int = y;
    }
}

class Edge{
    Interval inter;
    int coord;
    char edgetype;//L,R,T,B
    Edge(Interval in, int co, char edge){
        inter = in;
        coord = co;
        edgetype = edge;
    }
} 

class Stripe{
    Interval x_inter, y_inter;
    unordered_set<Interval> x_union;
    Stripe(Interval x, Interval y,  unordered_set<Interval> sx){
        x_inter = x, y_inter = y;
        x_union = sx;
    }
}