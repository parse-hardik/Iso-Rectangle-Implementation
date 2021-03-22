#include <bits/stdc++.h>
using namespace std;
#define inf 1e9
#include "Utils.hpp"

LRPS STRIPES(vector<Edge> V,Interval x_ext){
    sort(V.begin(),V.end(),edgecomp);
    vector<Interval> L, R,empvec;
    vector<int> P;
    vector<Stripe> S;
    vector<StripeTree> ST;

    if(V.size()==1){ 
        cout<<"in base case"<<" "<<V[0].coord<<"\n";                                       //V contains only one edge v. 
        Edge v= V[0];

        if(v.side == 'L')                                   // if its the left edge
            L.push_back(v.inter);
        else if(v.side=='R')                                               // if its the right edge
            R.push_back(v.inter);
        
        P.push_back(-inf);
        P.push_back(v.inter.bottom);
        P.push_back(v.inter.top);
        P.push_back(inf);
        
        for(int i=0;i<P.size()-1;i++)                       //make empty stripes
        {    
            S.push_back({x_ext,{P[i],P[i+1]},empvec});
            ST.push_back({x_ext,{P[i],P[i+1]} ,NULL });
        }

        if(v.side == 'L')                                   // if its the left edge
        {    
            S[1].x_union.push_back({v.coord,x_ext.top});    // fill the stripe to from the edge to the right extreme
            ST[1].tree = new Ctree(v.coord , 'L' , NULL, NULL);
        }
        else if(v.side == 'R')                                               // if its the right edge
        {    
            S[1].x_union.push_back({x_ext.bottom, v.coord});//fill the stripe from the edge to the left extreme
            ST[1].tree = new Ctree(v.coord , 'R' , NULL, NULL);
        }
        cout<<"returning from base case\n";
        return {L,R,P,S,ST};   

    }
    cout<<"in stirpes\n";
    for(auto p: V)
        cout<<p.coord<<" "<<p.side<<" "<<p.inter.bottom<<" "<<p.inter.top<<"\n";
    //int xm= (V[0].coord + V[V.size()-1].coord)/2;
    int xm = V[V.size()/2 - 1].coord;
    vector<Edge> V1,V2;

    //Divide
    // for(int i=0;i<V.size();i++){
    //     if(V[i].coord <=xm)
    //         V1.push_back(V[i]);
    //     else
    //         V2.push_back(V[i]);
    // }
    for(int i=0;i<V.size()/2;i++){
            V1.push_back(V[i]);
    }
    for(int i=V.size()/2;i<V.size();i++){
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
    sort(P1.begin(),P1.end());
    sort(P2.begin(),P2.end());

    vector<Interval> LR ;
    // Removed this for finding intersection -----------------------------------------------
    // for(int i=0;i<L1.size();i++){                           //find L1 intersection R2
    //     for(int j=0;j<R2.size();j++){
    //         if(L1[i].bottom == R2[j].bottom && L1[i].top == R2[i].top)
    //             LR.push_back(L1[i]);
    //     }
    // }
    // added this instead-------------------------------------------------------------------------
    LR = findIntersection(L1,R2);

    //checking aggr intersection function gives same answer ----------------------
    // cout<<"printing L from n sq \n";
    // for(auto p :  LR)
    //     cout<<p.bottom<<" "<<p.top<<" \n";
    // cout<<"printg union from funyion in o(n+m)\n";
    // for(auto p: findIntersection(L1, R2))
    //     cout<<p.bottom<<" "<<p.top<<"\n";
    // cout<<"finished\n";
    //----------------------------------------------------------------------------

    // L= (L1  \ LR) U L2;
    vector<Interval> L1MinusLR ;
    //find L1 \ LR
    
    //removed this for difference ----------------------------------
    // for(int i=0;i<L1.size();i++){
    //     bool found=0;
    //     for(int j=0;j<LR.size();j++){
    //         if(L1[i].bottom == LR[j].bottom && L1[i].top ==LR[j].top){    
    //             found=1;
    //             break;
    //         }
    //     }
    //     if(!found)
    //         L1MinusLR.push_back(L1[i]);
    // }
    // ------------------and andded this  - ----------------------------
    L1MinusLR = findDifference(L1,LR);


    //removed this for union and---------------------------------------            
    // for(int i=0; i<L1MinusLR.size();i++)
    //     L.push_back(L1MinusLR[i]);

    // for(int i=0;i<L2.size();i++){
    //     bool found=false;
    //     for(int j=0;j<L.size();j++){
    //         if(L2[i].bottom == L[j].bottom && L2[i].top ==L[j].top){ 
    //             found=true;
    //             break;
    //         }
    //     }
    //     if(!found)
    //         L.push_back(L2[i]);
    // } 
    //--------------------------------Added -------------
    L =  findUnion(L1MinusLR,  L2);

    //chekcing if the union function is right ---------------------------------
    // cout<<"printing L from n sq \n";
    // for(auto p :  L)
    //     cout<<p.bottom<<" "<<p.top<<" \n";
    // cout<<"printg union from funyion in o(n+m)\n";
    // for(auto p: findUnion(L1MinusLR, L2))
    //     cout<<p.bottom<<" "<<p.top<<"\n";
    // cout<<"finished\n";
    // R= R1 U (R2  \ LR);
    // --------------------------------------------------------------------------


    vector<Interval> R2MinusLR ;
    //find R2 \ LR

    //removed this for differnce -------------------------------------------
    // for(int i=0;i<R2.size();i++){
    //     bool found=0;
    //     for(int j=0;j<LR.size();j++){
    //         if(R2[i].bottom == LR[j].bottom && R2[i].top ==LR[j].top){    
    //             found=1;
    //             break;
    //         }
    //     }
    //     if(!found)
    //         R2MinusLR.push_back(R2[i]);
    // }
    // and added this  ----------------------------------------------
    R2MinusLR= findDifference(R2,LR);


    // -----------------------removed this for union----------------------------------------------------------
    // for(int i=0; i<R2MinusLR.size();i++){
    //     R.push_back(R2MinusLR[i]);
    // }

    // for(int i=0;i<R1.size();i++){
    //     bool found=false;
    //     for(int j=0;j<R.size();j++){
    //         if(R1[i].bottom == R[j].bottom && R1[i].top ==R[j].top)
    //         { 
    //             found=true;
    //             break;
    //         }
    //     }
    //     if(!found)
    //         R.push_back(R1[i]);
    // } 
    //---------------------and added  this  ---------------------------------
    R= findUnion(R1, R2MinusLR);

  
    //P=P1 U P2
    //------------------------removed this for union------------------------- 
    // for(int i=0; i<P1.size();i++){
    //     P.push_back(P1[i]);
    // }

    // for(int i=0;i<P2.size();i++){
    //     if(find(P.begin(),P.end(),P2[i])==P.end())
    //         P.push_back(P2[i]);
    // }
    //-----------and added this -----------------------------------------------
    P = findUnionNormal(P1,P2);

    //chekcing if output same h ya nahi -------------------------------
    //  cout<<"printing L from n sq \n";
    // for(auto p :  P)
    //     cout<<p<<" ";
    // cout<<"\n";
    // cout<<"printg union from funyion in o(n+m)\n";
    // for(auto p: findUnionNormal(P1, P2))
    //     cout<<p<<" ";
    // cout<<"\n";
    // cout<<"finished\n";
    //--------------------------------------------------------------

    //Sleft : = copy (S1, P, [xext.bottom, x,,]); 
    //Sright: = copy (S2, P, [xm, xext.top]) 
    vector<Stripe> Sleft,Sright, SleftNew;
    vector<StripeTree> STleft,STright;

    Sleft = copyNew(LRPS1.S , P , {x_ext.bottom , xm});
    Sright = copyNew(LRPS2.S , P , { xm, x_ext.top});

    //SleftNew = copyNew(LRPS1.S , P , {x_ext.bottom , xm});

// cout<<"printging old copy funvction\n";
//     for(auto stripe : Sleft){
//         cout<<"Y: " << stripe.y_inter.bottom << " "<< stripe.y_inter.top << "\n";
//         for(auto color : stripe.x_union){
//             cout << color.bottom << " " << color.top << " \n";
//         }
//     }
// cout<<"printging new copy funvction\n";
//     for(auto stripe : SleftNew){
//         cout<<"Y: " << stripe.y_inter.bottom << " "<< stripe.y_inter.top << "\n";
//         for(auto color : stripe.x_union){
//             cout << color.bottom << " " << color.top << " \n";
//         }
//     }
        


    STleft = copyTNew(LRPS1.ST , P , {x_ext.bottom , xm});
    STright = copyTNew(LRPS2.ST , P , { xm, x_ext.top});



    //blacken (Sle it, R 2 \ LR ); 
    //blacken ( Sright, L I\LR); 
    Sleft = blackenNew(Sleft , R2MinusLR);
    Sright = blackenNew(Sright , L1MinusLR);


    STleft = blackenTNew(STleft , R2MinusLR);
    STright = blackenTNew(STright , L1MinusLR);

    S= concat(Sleft,Sright, P,x_ext);

    ST= concatT(STleft,STright, P,x_ext);
    //cout<<"end of stripes\n";
    return {L,R,P,S,ST};
}

int main(){
    int n;
    cin >> n;
    vector<Edge> V;
    vector<Edge> H;
    int maxx=INT_MIN,minx=INT_MAX;
    for(int i=0;i<n;i++){
        int x,y,a,b;
        char c;
        cin >> x >> y >> a >>b;
        //if(c=='T' || c=='B' )
            H.push_back({{x,a},y,'B'});
            H.push_back({{x,a},b,'T'});
        //else{
            maxx = max(maxx,a);
            minx = min(minx,x);
            V.push_back({{y,b}, x, 'L'});
            V.push_back({{y,b}, a, 'R'});
        //}
    }
    LRPS stripes  = STRIPES(V,{minx,maxx});
    //cout<<"is done\n";
    // for(auto stripe : stripes.S){
    //     cout<<"Y: " << stripe.y_inter.bottom << " "<< stripe.y_inter.top << "\n";
    //     for(auto color : stripe.x_union){
    //         cout << color.bottom << " " << color.top << " \n";
    //     }
    // }
    for(auto stripe : stripes.ST)
    {  
        cout<<stripe.y_inter.bottom<<" "<<stripe.y_inter.top<<" \n";
        inorderPrint(stripe.tree);
        cout<<"\n";
    }

    for(auto linesegment :  contour(H,stripes.ST))
    {
        cout<<linesegment.inter.bottom <<" "<<linesegment.inter.top<<" "<<linesegment.coord<<"\n";
    }


    cout << "Area is " << measure(stripes.S) << endl;
     


}




//Test case 1
/*
4
1 1 4 4 
2 2 6 6
5 5 12 8
8 4 14 7
*/

//test case 2
/*
5
2 2 6 6
5 5 12 8
8 4 14 7
7 1 15 3
13 0 16 7
*/

//test case 3
/*
2 10 5 12
4 4 14 9
6 5 12 8
13 0 16 6
*/



