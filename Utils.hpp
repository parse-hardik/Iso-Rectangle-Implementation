#include "structures.hpp"

bool compareInterval(Interval i1, Interval i2){
    return (i1.bottom < i2.bottom) || (i1.bottom == i2.bottom && i1.top < i2.top);
}

bool edgecomp(Edge e1, Edge e2){
    return (e1.coord < e2.coord);
}

vector<Stripe> copy(vector<Stripe> S, vector<int> P, Interval x_int){
    sort(P.begin(), P.end());
    vector<Stripe> Snew;
    vector<Interval> empvec;
    for (int i = 0; i < P.size() - 1; i++)
    {
        Snew.push_back({x_int, {P[i], P[i + 1]}, empvec});
    }
    for (int i = 0; i < Snew.size(); i++){
        for (int j = 0; j < S.size(); j++){
            if (S[j].y_inter.bottom <= Snew[i].y_inter.bottom && S[j].y_inter.top >= Snew[i].y_inter.top){
                Snew[i].x_union = S[j].x_union;
                break;
            }
        }
    }
    return Snew;
}

vector<Stripe> blacken(vector<Stripe> S, vector<Interval> J){
    for (int i = 0; i < S.size(); i++){
        for (int j = 0; j < J.size(); j++){
            if (S[i].y_inter.bottom >= J[j].bottom && S[i].y_inter.top <= J[j].top){
                S[i].x_union.clear();
                S[i].x_union.push_back(S[i].x_inter);
            }
        }
    }
    return S;
}

vector<Stripe> concat(vector<Stripe> S1, vector<Stripe> S2, vector<int> P, Interval x_int){
    vector<Stripe> S;
    vector<Interval> empvec;
    sort(P.begin(), P.end());
    for (int i = 0; i < P.size() - 1; i++)
        S.push_back({x_int, {P[i], P[i + 1]}, empvec});

    for (int i = 0; i < S.size(); i++){
        for (int j = 0; j < S1.size(); j++){
            if (S1[j].y_inter.bottom == S[i].y_inter.bottom && S1[j].y_inter.top == S[i].y_inter.top)
                S[i].x_union = S1[j].x_union; 
        }
    }
    for (int i = 0; i < S.size(); i++){
        for (int j = 0; j < S2.size(); j++){
            if (S2[j].y_inter.bottom == S[i].y_inter.bottom && S2[j].y_inter.top == S[i].y_inter.top)
                S[i].x_union.insert(S[i].x_union.end(), S2[j].x_union.begin(), S2[j].x_union.end());
        }
    }
    return S;
}