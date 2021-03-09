#include <bits/stdc++.h>
using namespace std;
#define inf 1e9
#include "Utils.hpp"

LRPS STRIPES(vector<Edge> V,Interval x_ext){
    vector<Interval> L, R,empvec;
    vector<int> P;
    vector<Stripe> S;

    if(V.size()==1){                                        //V contains only one edge v. 
        Edge v= V[0];

        if(v.side == 'L')                                   // if its the left edge
            L.push_back(v.inter);
        else                                                // if its the right edge
            R.push_back(v.inter);
        
        P.push_back(-inf);
        P.push_back(v.inter.bottom);
        P.push_back(v.inter.top);
        P.push_back(inf);
        
        for(int i=0;i<P.size()-1;i++)                       //make empty stripes
            S.push_back({x_ext,{P[i],P[i+1]},empvec});

        if(v.side == 'L')                                   // if its the left edge
            S[1].x_union.push_back({v.coord,x_ext.top});    // fill the stripe to from the edge to the right extreme
        else                                                // if its the right edge
            S[1].x_union.push_back({x_ext.bottom, v.coord});//fill the stripe from the edge to the left extreme

        return {L,R,P,S};        
    }
    
    sort(V.begin(),V.end(),edgecomp);
    int xm= (V[0].coord + V[V.size()-1].coord)/2;
    vector<Edge> V1,V2;

    //Divide
    for(int i=0;i<V.size();i++){
        if(V[i].coord <=xm)
            V1.push_back(V[i]);
        else
            V2.push_back(V[i]);
    }

    //Conquer
    LRPS LRPS1= STRIPES(V1, {x_ext.bottom ,xm});
    vector<Interval> L1 =LRPS1.L , R1 = LRPS1.R; 
    vector<int> P1= LRPS1.P;

    LRPS LRPS2= STRIPES(V2, {xm, x_ext.top});
    vector<Interval> L2 =LRPS2.L , R2 = LRPS2.R;
    vector<int> P2= LRPS2.P;

    //merge
    sort(L1.begin(),L1.end(),compareInterval);              // sort L1
    sort(L2.begin(),L2.end(),compareInterval);              //sort l2
    sort(R1.begin(),R1.end(),compareInterval);              //sort R1
    sort(R2.begin(),R2.end(),compareInterval);              //sort R2

    vector<Interval> LR ;
    
    for(int i=0;i<L1.size();i++){                           //find L1 intersection R2
        for(int j=0;j<R2.size();j++){
            if(L1[i].bottom == R2[j].bottom && L1[i].top == R2[i].top)
                LR.push_back(L1[i]);
        }
    }
    // L= (L1  \ LR) U L2;
    vector<Interval> L1MinusLR ;
    //find L1 \ LR
    
    for(int i=0;i<L1.size();i++){
        bool found=0;
        for(int j=0;j<LR.size();j++){
            if(L1[i].bottom == LR[j].bottom && L1[i].top ==LR[j].top){    
                found=1;
                break;
            }
        }
        if(!found)
            L1MinusLR.push_back(L1[i]);
    }
                
    for(int i=0; i<L1MinusLR.size();i++)
        L.push_back(L1MinusLR[i]);

    for(int i=0;i<L2.size();i++){
        bool found=false;
        for(int j=0;j<L.size();j++){
            if(L2[i].bottom == L[j].bottom && L2[i].top ==L[j].top){ 
                found=true;
                break;
            }
        }
        if(!found)
            L.push_back(L2[i]);
    }  
    // R= R1 U (R2  \ LR);
    vector<Interval> R2MinusLR ;
    //find R2 \ LR
    for(int i=0;i<R2.size();i++){
        bool found=0;
        for(int j=0;j<LR.size();j++){
            if(R2[i].bottom == LR[j].bottom && R2[i].top ==LR[j].top){    
                found=1;
                break;
            }
        }
        if(!found)
            R2MinusLR.push_back(R2[i]);
    }

    for(int i=0; i<R2MinusLR.size();i++){
        R.push_back(R2MinusLR[i]);
    }

    for(int i=0;i<R1.size();i++){
        bool found=false;
        for(int j=0;j<R.size();j++){
            if(R1[i].bottom == R[j].bottom && R1[i].top ==R[j].top)
            { 
                found=true;
                break;
            }
        }
        if(!found)
            R.push_back(R1[i]);
    }  
  
    //P=P1 U P2
    for(int i=0; i<P1.size();i++){
        P.push_back(P1[i]);
    }

    for(int i=0;i<P2.size();i++){
        if(find(P.begin(),P.end(),P2[i])==P.end())
            P.push_back(P2[i]);
    }

    //Sleft : = copy (S1, P, [xext.bottom, x,,]); 
    //Sright: = copy (S2, P, [xm, xext.top]) 
    vector<Stripe> Sleft,Sright;

    Sleft = copy(LRPS1.S , P , {x_ext.bottom , xm});
    Sright = copy(LRPS2.S , P , { xm, x_ext.top});

    //blacken (Sle it, R 2 \ LR ); 
    //blacken ( Sright, L I\LR); 
    Sleft = blacken(Sleft , R2MinusLR);
    Sright = blacken(Sright , L1MinusLR);

    S= concat(Sleft,Sright, P,x_ext);
    return {L,R,P,S};
}

int main(){
    int n;
    cin >> n;
    vector<Edge> V;
    int maxx=INT_MIN,minx=INT_MAX;
    for(int i=0;i<n;i++){
        int b,t,x;
        char c;
        cin>>b>>t>>x>>c;
        maxx = max(maxx,x);
        minx = min(minx,x);
        V.push_back({{b,t}, x, c});
    }
    LRPS stripes  = STRIPES(V,{minx,maxx});
    cout<<"is done\n";
    for(auto stripe : stripes.S){
        cout<<"Y: "<<stripe.y_inter.bottom<<" "<<stripe.y_inter.top<<" "<<"X: "<<stripe.x_inter.bottom<<" "<<stripe.x_inter.top<<"\n";
        for(auto color : stripe.x_union){
            cout<<color.bottom<<' '<<color.top<<" \n";
        }
    }
    
}


