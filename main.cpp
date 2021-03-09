#include <bits/stdc++.h>
using namespace std;
#define inf 1e9
#include "structures.hpp"

bool compareInterval(Interval i1, Interval i2) 
{ 
    return (i1.bottom < i2.bottom) || (i1.bottom == i2.bottom  &&  i1.top < i2.top  ) ; 
} 
bool edgecomp(Edge e1, Edge e2) 
{ 
    return (e1.coord < e2.coord) ; 
} 
vector<Stripe> copy( vector<Stripe> S, vector<int> P, Interval x_int)
{
    sort(P.begin(),P.end());
    cout<<"in cpy \n";
    for(int x : P)
        cout<<x<<" ";
    cout<<"\n";
    vector<Stripe> Snew ;
    vector<Interval> empvec;
    for(int i=0;i<P.size()-1;i++)
    {
        Snew.push_back({x_int , {P[i],P[i+1]}, empvec});
    }
    //cout<<"new Stripe evctor made\n";
    for(int i=0;i<Snew.size();i++)
    {
        for(int j=0;j<S.size();j++)
        {
            if(S[j].y_inter.bottom<= Snew[i].y_inter.bottom && S[j].y_inter.top>= Snew[i].y_inter.top )
            {
                Snew[i].x_union = S[j].x_union;
                break;
            }
        }
    }
    //cout<<"out of cpoy function\n";
    return Snew;
}
vector<Stripe> blacken( vector<Stripe> S , vector<Interval> J)
{
    //cout<<"in blacken\n";
    for(int i=0;i<S.size();i++)
    {
        for(int j=0;j<J.size();j++)
        {
            if(S[i].y_inter.bottom>= J[j].bottom  && S[i].y_inter.top <= J[j].top )
            {   
                //cout<<"yes blackening\n";
                S[i].x_union.clear();
                S[i].x_union.push_back(S[i].x_inter);
                // for(auto color : S[i].x_union)
                // {
                //     cout<<color.bottom <<" "<<color.top<<" \n";
                // }
            }
        }
    }
    return S;
}
vector<Stripe> concat(vector<Stripe> S1, vector<Stripe> S2, vector<int> P, Interval x_int)
{
    cout<<"in concat\n";
    cout<<"S1\n";
    for(auto stripe : S1)
    {
        cout<<"Y: "<<stripe.y_inter.bottom<<" "<<stripe.y_inter.top<<" "<<"X: "<<stripe.x_inter.bottom<<" "<<stripe.x_inter.top<<"\n";
        for(auto color : stripe.x_union)
        {
            cout<<color.bottom<<' '<<color.top<<" \n";
        }
    }
    cout<<"S2\n";
    for(auto stripe : S2)
    {
        cout<<"Y: "<<stripe.y_inter.bottom<<" "<<stripe.y_inter.top<<" "<<"X: "<<stripe.x_inter.bottom<<" "<<stripe.x_inter.top<<"\n";
        for(auto color : stripe.x_union)
        {
            cout<<color.bottom<<' '<<color.top<<" \n";
        }
    }
    
    vector<Stripe> S ;
    vector<Interval> empvec;
    sort(P.begin(),P.end());
    for(int i=0;i<P.size()-1;i++)
    {
        S.push_back({x_int , {P[i],P[i+1]} , empvec});
    }
    for(int i=0;i<S.size();i++)
    {
        for(int j=0;j<S1.size();j++)
        {
            if(S1[j].y_inter.bottom==S[i].y_inter.bottom && S1[j].y_inter.top==S[i].y_inter.top)
            {
                S[i].x_union = S1[j].x_union;//S.xunion=S1.xnuion
            }
        }
    }
    for(int i=0;i<S.size();i++)
    {
        for(int j=0;j<S2.size();j++)
        {
            if(S2[j].y_inter.bottom==S[i].y_inter.bottom && S2[j].y_inter.top==S[i].y_inter.top)
            {
                S[i].x_union.insert(S[i].x_union.end(), S2[j].x_union.begin(), S2[j].x_union.end());// S.xunion = S.xunion + S2.xunion
            }
        }
    }
    for(auto stripe : S)
    {
        cout<<"Y: "<<stripe.y_inter.bottom<<" "<<stripe.y_inter.top<<" "<<"X: "<<stripe.x_inter.bottom<<" "<<stripe.x_inter.top<<"\n";
        for(auto color : stripe.x_union)
        {
            cout<<color.bottom<<' '<<color.top<<" \n";
        }
    }

    return S;
}
LRPS STRIPES(vector<Edge> V,Interval x_ext)
{
    cout<<" call stripes\n";
    for(auto E: V)
    {
        cout<<E.inter.bottom<<" "<<E.inter.top<<" "<<E.side<<"\n";
    }
    vector<Interval> L, R,empvec;
    vector<int> P;
    vector<Stripe> S;

    if(V.size()==1)//V contains only one edge v. 
    {
        cout<<"has one edge\n";
        Edge v= V[0];
        if(v.side == 'L')// if its the left edge
        {
            cout<<"is left edge\n";
            L.push_back(v.inter);
        }
        else// if its the right edge
        {
            R.push_back(v.inter);
        }
        P.push_back(-inf);P.push_back(v.inter.bottom);P.push_back(v.inter.top);P.push_back(inf);
        //make empty stripes
        for(int i=0;i<P.size()-1;i++)
        {
            S.push_back({x_ext,{P[i],P[i+1]},empvec});
        }
        if(v.side == 'L')// if its the left edge
        {
            S[1].x_union.push_back({v.coord,x_ext.top});// fill the stripe to from the edge to the right extreme
        }
        else// if its the right edge
        {
            S[1].x_union.push_back({x_ext.bottom, v.coord});//fill the stripe from the edge to the left extreme
        } 
        cout<<"returning\n";
        for(auto stripe : S)
        {
            cout<<"Y: "<<stripe.y_inter.bottom<<" "<<stripe.y_inter.top<<" "<<"X: "<<stripe.x_inter.bottom<<" "<<stripe.x_inter.top<<"\n";
            for(auto color : stripe.x_union)
            {
                cout<<color.bottom<<' '<<color.top<<" \n";
            }
        }
        return {L,R,P,S};        
    }
    //divide 
    cout<<"has more than 1 edge";
    sort(V.begin(),V.end(),edgecomp);
    int xm= (V[0].coord + V[V.size()-1].coord)/2;

    
    vector<Edge> V1,V2;
    // for(int i=0;i<V.size()/2;i++)
    // {
    //     V1.push_back(V[i]);
    //     xm=V[i].coord;   
    // }
    // for(int i=V.size()/2;i<V.size();i++)
    // {
    //         V2.push_back(V[i]);
    // }
    for(int i=0;i<V.size();i++)
    {
        if(V[i].coord <=xm)
            V1.push_back(V[i]);
        else
            V2.push_back(V[i]);
    }
    cout<<xm<<" dividing \n";
    //conquer
    LRPS LRPS1= STRIPES(V1, {x_ext.bottom ,xm});
    cout<<"going to find right side\n";
    vector<Interval> L1 =LRPS1.L , R1 = LRPS1.R; 
    vector<int> P1= LRPS1.P;
    LRPS LRPS2= STRIPES(V2, {xm, x_ext.top});
    vector<Interval> L2 =LRPS2.L , R2 = LRPS2.R;
    vector<int> P2= LRPS2.P;

    cout<<"before everything in sleft\n";
    for(auto stripe : LRPS1.S)
    {
        cout<<"Y: "<<stripe.y_inter.bottom<<" "<<stripe.y_inter.top<<" "<<"X: "<<stripe.x_inter.bottom<<" "<<stripe.x_inter.top<<"\n";
        for(auto color : stripe.x_union)
        {
            cout<<color.bottom<<' '<<color.top<<" \n";
        }
    }
    cout<<"before everything in sright\n";
    for(auto stripe : LRPS2.S)
    {
        cout<<"Y: "<<stripe.y_inter.bottom<<" "<<stripe.y_inter.top<<" "<<"X: "<<stripe.x_inter.bottom<<" "<<stripe.x_inter.top<<"\n";
        for(auto color : stripe.x_union)
        {
            cout<<color.bottom<<' '<<color.top<<" \n";
        }
    }

    //merge
    sort(L1.begin(),L1.end(),compareInterval); // sort L1
    sort(L2.begin(),L2.end(),compareInterval);//sort l2
    sort(R1.begin(),R1.end(),compareInterval);//sort R1
    sort(R2.begin(),R2.end(),compareInterval);//sort R2

    cout<<"finished sorting\n";
    vector<Interval> LR ;
    //find L1 intersection R2
        for(int i=0;i<L1.size();i++)
        {
            for(int j=0;j<R2.size();j++)
            {
                if(L1[i].bottom == R2[j].bottom && L1[i].top == R2[i].top)
                    LR.push_back(L1[i]);
            }
        }
        //auto LRenditerator = set_intersection(L1.begin(),L1.end(), R2.begin(),R2.end(), LR.begin(),compareInterval); 

        cout<<" step 1\n";
    // L= (L1  \ LR) U L2;
                vector<Interval> L1MinusLR ;
                //find L1 \ LR
                
                //auto L1MinusLRenditerator = set_difference(L1.begin(),L1.end(), LR.begin(),LR.end(), L1MinusLR.begin(),compareInterval);
                for(int i=0;i<L1.size();i++)
                {
                    bool found=0;
                    for(int j=0;j<LR.size();j++)
                    {
                        if(L1[i].bottom == LR[j].bottom && L1[i].top ==LR[j].top)
                        {    
                            found=1;
                            break;
                        }
                    }
                    if(!found)
                        L1MinusLR.push_back(L1[i]);
                }
                
                //auto Lenditerator = set_union(L1MinusLR.begin(),L1MinusLR.end(), L2.begin(),L2.end(), L.begin(),compareInterval); 
                for(int i=0; i<L1MinusLR.size();i++)
                {
                    L.push_back(L1MinusLR[i]);
                }
                for(int i=0;i<L2.size();i++)
                {
                    bool found=false;
                    for(int j=0;j<L.size();j++)
                    {
                        if(L2[i].bottom == L[j].bottom && L2[i].top ==L[j].top)
                        { 
                            found=true;
                            break;
                        }
                    }
                    if(!found)
                        L.push_back(L2[i]);
                }  
                cout<<"step 2\n";
     // R= R1 U (R2  \ LR);
                vector<Interval> R2MinusLR ;
                //find R2 \ LR
                //auto R2MinusLRenditerator = set_difference(R2.begin(),R2.end(), LR.begin(),LR.end(), R2MinusLR.begin(),compareInterval); 
                for(int i=0;i<R2.size();i++)
                {
                    bool found=0;
                    for(int j=0;j<LR.size();j++)
                    {
                        if(R2[i].bottom == LR[j].bottom && R2[i].top ==LR[j].top)
                        {    
                            found=1;
                            break;
                        }
                    }
                    if(!found)
                        R2MinusLR.push_back(R2[i]);
                }
                
                //auto Renditerator = set_union(R2MinusLR.begin(),R2MinusLR.end(), R1.begin(),R1.end(), R.begin(),compareInterval); 
                for(int i=0; i<R2MinusLR.size();i++)
                {
                    R.push_back(R2MinusLR[i]);
                }
                for(int i=0;i<R1.size();i++)
                {
                    bool found=false;
                    for(int j=0;j<R.size();j++)
                    {
                        if(R1[i].bottom == R[j].bottom && R1[i].top ==R[j].top)
                        { 
                            found=true;
                            break;
                        }
                    }
                    if(!found)
                        R.push_back(R1[i]);
                }  
                cout<<"step 3\n";
  
    //P=P1 U P2
        //auto Penditerator = set_union(P1.begin(),P1.end(), P2.begin(),P2.end(), P.begin()); 
        for(int i=0; i<P1.size();i++)
        {
            P.push_back(P1[i]);
        }
        for(int i=0;i<P2.size();i++)
        {
            if(find(P.begin(),P.end(),P2[i])==P.end())
                P.push_back(P2[i]);
        }
        cout<<"step 4\n";

    //Sleft : = copy (S1, P, [xext.bottom, x,,]); 
    //Sright: = copy (S2, P, [xm, xext.top]) 
    vector<Stripe> Sleft,Sright;
    Sleft = copy(LRPS1.S , P , {x_ext.bottom , xm});
    cout<<"going to next copy\n";
    Sright = copy(LRPS2.S , P , { xm, x_ext.top});

    cout<<"before blacken in sleft\n";
    for(auto stripe : Sleft)
    {
        cout<<"Y: "<<stripe.y_inter.bottom<<" "<<stripe.y_inter.top<<" "<<"X: "<<stripe.x_inter.bottom<<" "<<stripe.x_inter.top<<"\n";
        for(auto color : stripe.x_union)
        {
            cout<<color.bottom<<' '<<color.top<<" \n";
        }
    }
    cout<<"before blacken in sright\n";
    for(auto stripe : Sright)
    {
        cout<<"Y: "<<stripe.y_inter.bottom<<" "<<stripe.y_inter.top<<" "<<"X: "<<stripe.x_inter.bottom<<" "<<stripe.x_inter.top<<"\n";
        for(auto color : stripe.x_union)
        {
            cout<<color.bottom<<' '<<color.top<<" \n";
        }
    }
    //blacken (Sle it, R 2 \ LR ); 
    //blacken ( Sright, L I\LR); 
    Sleft = blacken(Sleft , R2MinusLR);
    Sright = blacken(Sright , L1MinusLR);

    cout<<"before concat in sleft\n";
    for(auto stripe : Sleft)
    {
        cout<<"Y: "<<stripe.y_inter.bottom<<" "<<stripe.y_inter.top<<" "<<"X: "<<stripe.x_inter.bottom<<" "<<stripe.x_inter.top<<"\n";
        for(auto color : stripe.x_union)
        {
            cout<<color.bottom<<' '<<color.top<<" \n";
        }
    }
    cout<<"before concat in sright\n";
    for(auto stripe : Sright)
    {
        cout<<"Y: "<<stripe.y_inter.bottom<<" "<<stripe.y_inter.top<<" "<<"X: "<<stripe.x_inter.bottom<<" "<<stripe.x_inter.top<<"\n";
        for(auto color : stripe.x_union)
        {
            cout<<color.bottom<<' '<<color.top<<" \n";
        }
    }

    S= concat(Sleft,Sright, P,x_ext);
    cout<<"returning from main\n";
    return {L,R,P,S};
}
int main(){
    int n;
    cin >> n;
    vector<Edge> V;
    int maxx=INT_MIN,minx=INT_MAX;
    for(int i=0;i<n;i++)
    {
        int b,t,x;
        char c;
        cin>>b>>t>>x>>c;
        maxx = max(maxx,x);
        minx = min(minx,x);
        V.push_back({{b,t}, x, c});
    }
    cout<<"finished taking input\n";
    LRPS stripes  = STRIPES(V,{minx,maxx});
    cout<<"is done\n";
    for(auto stripe : stripes.S)
    {
        cout<<"Y: "<<stripe.y_inter.bottom<<" "<<stripe.y_inter.top<<" "<<"X: "<<stripe.x_inter.bottom<<" "<<stripe.x_inter.top<<"\n";
        for(auto color : stripe.x_union)
        {
            cout<<color.bottom<<' '<<color.top<<" \n";
        }
    }
    
}


