#include <bits/stdc++.h>
using namespace std;
#define inf 1e9
#include "Utils.hpp"
#include<fstream>
using namespace std::chrono;



LRPS STRIPES(vector<Edge> V,Interval x_ext){
    
    sort(V.begin(),V.end(),edgecomp);
    vector<Interval> L, R,empvec;
    vector<int> P;
    vector<Stripe> S;
    vector<StripeTree> ST;

                                       //V contains only one edge v.
    if(V.size()==1){                                        //V contains only one edge v.
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
        return {L,R,P,S,ST};

    }
    int xm = V[V.size()/2 - 1].coord;
    //cout<<"dividing at xm"<<xm<<"\n";
    vector<Edge> V1,V2;

    //Divide
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
    // cout<<"left\n";
    // for(auto stripe : LRPS1.S){
    //     cout<<"Y: " << stripe.y_inter.bottom << " "<< stripe.y_inter.top << "\n";
    //     for(auto color : stripe.x_union){
    //         cout << color.bottom << " " << color.top << " ";
    //     }
    // }
    // cout<<"right\n";
    // for(auto stripe : LRPS2.S){
    //     cout<<"Y: " << stripe.y_inter.bottom << " "<< stripe.y_inter.top << "\n";
    //     for(auto color : stripe.x_union){
    //         cout << color.bottom << " " << color.top << " ";
    //     }
    // }

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

    return {L,R,P,S,ST};
}

int main(){
    ofstream mfile("Measure.txt");
    int n;
    cin >> n;
    vector<Edge> V;
    vector<Edge> H;
    int maxx=INT_MIN,minx=INT_MAX;
    for(int i=0;i<n;i++){
        int x,y,a,b;
        char c;
        cin >> x >> y >> a >>b;
        mfile << x << "," << y << "," << (a-x) << "," << (b-y);
        mfile << "\n";
        //if(c=='T' || c=='B' )
            H.push_back({{x,a,i},y,'B'});
            H.push_back({{x,a,i},b,'T'});
        //else{
            maxx = max(maxx,a);
            minx = min(minx,x);
            V.push_back({{y,b,i}, x, 'L'});
            V.push_back({{y,b,i}, a, 'R'});
        //}
    }
    mfile.close();

    //Timer timer("Stripes");
    auto start1 = high_resolution_clock::now(); 
    LRPS stripes  = STRIPES(V,{minx,maxx});
    auto stop1 = high_resolution_clock::now(); 
    auto duration1 = duration_cast<microseconds>(stop1 - start1); 



    cout<<"\nVertical line segments :\nFor the y interval ( y1 , y2 ) Draw vertical lines at the following x coordinates \n";
    ofstream cfile("ContourV.txt");
    for(auto stripe : stripes.ST)
    {
        cout<<"( "<<stripe.y_inter.bottom<<", "<<stripe.y_inter.top<<" ) : ";
        inorderPrint(stripe.tree);
        for(int i=0;i<vec.size();i++)
        {
            cfile << vec[i] << "," << stripe.y_inter.bottom << "," << stripe.y_inter.top;
            cfile << "\n";
        }
        vec.clear();
        cout<<"\n";
    }
    cfile.close();




    ofstream cfilev("ContourH.txt");
    cout<<"\nHorizontal Line Segments : \n";
    cout<<"x1 \tx2 \ty\n";


    auto start2 = high_resolution_clock::now(); 
    vector<LineSegment> contours = contour(H,stripes.ST);
    auto stop2 = high_resolution_clock::now(); 
    auto duration2 = duration_cast<microseconds>(stop2 - start2); 
    
    
    for(auto linesegment :  contours)
    {
        cout<<linesegment.inter.bottom <<" \t"<<linesegment.inter.top<<" \t"<<linesegment.coord<<"\n";
        cfilev << linesegment.coord << "," << linesegment.inter.bottom << "," << linesegment.inter.top;
        cfilev << "\n";
    }
    cfilev.close();
    // cout << "\nTime taken by Contour function: "
    //      << duration2.count() << " microseconds" << endl; 

    
    auto start3 = high_resolution_clock::now(); 
    int area= measure(stripes.S);
    auto stop3 = high_resolution_clock::now(); 
    auto duration3 = duration_cast<microseconds>(stop3 - start3); 
    
    cout << "Area is : " << area <<" units."<< endl;
    // cout << "\nTime taken by Measure function: "
    //      << duration3.count() << " microseconds" << endl; 
    
    cout << "\nTime taken by the entire algorithm to find measure and contour: "
         << duration1.count() + duration2.count()+  duration3.count() << " microseconds" << endl; 

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
4
2 10 5 12
4 4 14 9
6 5 12 8
13 0 16 6
*/

/*
test case 4
7
0 0 4 4
0 4 4 6
2 3 8 7
1 1 5 5 
5 1 7 3
9 1 10 4
8 6 9 7
*/

/*
8
0 0 4 4
0 4 4 6
2 3 8 7
1 1 5 5
5 1 7 3
9 1 10 4
8 6 9 7
0 0 13 9

Ans = 117
*/
/*
Test 5
10
3 4 6 7
1 3 2 4
3 2 10 4
2 6 6 10
2 7 3 15
2 5 10 7
8 5 9 7
7 5 9 6
3 4 5 7
1 1 3 3
*/




















































/*
95
17 19 37 65 
76 95 96 100 
12 94 98 99 
26 35 42 97 
36 50 62 96 
52 61 67 86 
10 53 86 89 
46 58 67 75
15 38 41 60 
23 55 77 91 
55 63 74 77 
4 10 76 82 
7 17 64 98 
25 59 74 97 
6 8 26 46 
19 29 31 95 
7 40 60 79 
3 13 19 43 
8 39 72 87
9 33 51 57 
21 26 43 92 
16 28 40 52 
25 33 62 63 
32 44 66 68 
39 44 73 89 
3 13 22 26 
24 39 61 69 
7 53 68 69 
47 50 64 82 
29 38 73 95 
14 71 73 95 
3 25 38 73 
16 40 80 93 
43 56 62 97 
8 17 29 39 
5 43 72 92 
20 52 81 96 
5 53 70 98 
44 50 81 90 
17 26 39 76 
27 51 80 93 
30 74 90 92 
5 44 62 100 
3 41 43 51 
5 12 19 98 
13 69 82 87 
31 44 57 66 
66 72 85 96 
71 75 96 97 
4 32 53 80 
32 60 71 81 
11 56 78 95 
15 34 68 76 
31 33 50 73 
51 75 82 86 
34 45 50 94 
14 15 81 92 
10 35 53 98 
29 30 89 92 
40 57 80 85 
1 14 15 99 
66 80 87 89 
22 24 92 93 
13 74 83 86 
10 50 74 90 
24 78 83 90 
18 28 57 100 
22 23 70 91 
12 46 51 85 
40 66 70 74 
30 83 86 90 
50 51 57 83 
2 42 74 87 
24 38 39 76 
36 60 81 85 
23 62 79 84 
20 36 68 88 
6 24 37 99 
1 9 12 99 
3 7 22 91 
9 36 79 87 
12 33 50 98 
6 19 76 97 
8 27 28 71 
38 42 55 77 
77 83 93 94 
20 22 24 80 
14 79 84 99 
75 86 92 98 
2 20 33 63 
21 22 37 69 
6 12 27 60 
6 45 72 87 
3 19 58 64 
49 68 77 98
*/


/*
5
1 1 5 4
4 3 7 6
2 3 3 10
1 6 5 7
0 8 8 9
*/
/*
10
32 44 66 68 
39 44 73 89  
24 39 61 69  
47 50 64 82 
29 38 73 95 
14 71 73 95 
16 40 80 93 
7 53 68 69
3 25 38 73
3 13 22 26
*/  





