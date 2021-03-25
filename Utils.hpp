#include "structures.hpp"
vector<int> vec;
bool compareInterval(Interval i1, Interval i2){
    return (i1.bottom < i2.bottom) || (i1.bottom == i2.bottom && i1.top < i2.top) || (i1.bottom == i2.bottom && i1.top == i2.top && i1.id<i2.id);
}

bool edgecomp(Edge e1, Edge e2){
    return (e1.coord < e2.coord)  || (e1.coord == e2.coord && e1.side =='L' && e2.side=='R') ;
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

vector<Stripe> copyNew(vector<Stripe> S, vector<int> P, Interval x_int){
    sort(P.begin(), P.end());
    vector<Stripe> Snew;
    vector<Interval> empvec;
    for (int i = 0; i < P.size() - 1; i++)
    {
        Snew.push_back({x_int, {P[i], P[i + 1]}, empvec});
    }
    for (int i = 0 , j= 0; i < Snew.size(); i++){
        // for (int j = 0; j < S.size(); j++){
        //     if (S[j].y_inter.bottom <= Snew[i].y_inter.bottom && S[j].y_inter.top >= Snew[i].y_inter.top){
        //         Snew[i].x_union = S[j].x_union;
        //         break;
        //     }
        // }
        Snew[i].x_union = S[j].x_union;
        if( S[j].y_inter.top == Snew[i].y_inter.top)
        {

            j++;
        }
    }
    return Snew;
}

vector<StripeTree> copyT(vector<StripeTree> ST, vector<int> P, Interval x_int){
    sort(P.begin(), P.end());
    vector<StripeTree> STnew;
    for (int i = 0; i < P.size() - 1; i++)
    {
        STnew.push_back({x_int, {P[i], P[i + 1]}, NULL});
    }
    for (int i = 0; i < STnew.size(); i++){
        for (int j = 0; j < ST.size(); j++){
            if (ST[j].y_inter.bottom <= STnew[i].y_inter.bottom && ST[j].y_inter.top >= STnew[i].y_inter.top){
                STnew[i].tree = ST[j].tree;
                break;
            }
        }
    }
    return STnew;
}
vector<StripeTree> copyTNew(vector<StripeTree> ST, vector<int> P, Interval x_int){
    sort(P.begin(), P.end());
    vector<StripeTree> STnew;
    for (int i = 0; i < P.size() - 1; i++)
    {
        STnew.push_back({x_int, {P[i], P[i + 1]}, NULL});
    }
    for (int i = 0 ,j =0; i < STnew.size(); i++){
        STnew[i].tree = ST[j].tree;
        if( ST[j].y_inter.top == STnew[i].y_inter.top)
        {
            j++;
        }
    }
    return STnew;
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
vector<Stripe> blackenNew(vector<Stripe> S, vector<Interval> J){
    sort(J.begin(),J.end() , compareInterval);
    int j = 0;
    for (int i = 0; i < S.size(); i++){
        //cout << "In Stripe\n";
        for (; j < J.size(); j++){
            if(S[i].y_inter.top <= J[j].bottom )
                break;
            if (S[i].y_inter.bottom >= J[j].bottom && S[i].y_inter.top <= J[j].top){
                S[i].x_union.clear();
                S[i].x_union.push_back(S[i].x_inter);
                //cout<<S[i].y_inter.bottom<<" "<<S[i].y_inter.top<<" "<<J[j].bottom<<" "<<J[j].top<<"\n";
                break;
            }
        }
    }
    return S;
}

vector<StripeTree> blackenTNew(vector<StripeTree> ST, vector<Interval> J){

     sort(J.begin(),J.end() , compareInterval);
     int j = 0;
    for (int i = 0; i < ST.size(); i++){
        for (; j < J.size(); j++){
            if (ST[i].y_inter.top <= J[j].bottom )
                break;
            if (ST[i].y_inter.bottom >= J[j].bottom && ST[i].y_inter.top <= J[j].top){
                ST[i].tree=NULL;
                break;
            }
        }
    }
    return ST;
}

vector<StripeTree> blackenT(vector<StripeTree> ST, vector<Interval> J){
    for (int i = 0; i < ST.size(); i++){
        for (int j = 0; j < J.size(); j++){
            if (ST[i].y_inter.bottom >= J[j].bottom && ST[i].y_inter.top <= J[j].top){
                ST[i].tree=NULL;
            }
        }
    }
    return ST;
}

vector<Stripe> concat(vector<Stripe> S1, vector<Stripe> S2, vector<int> P, Interval x_int){
    vector<Stripe> S;
    vector<Interval> empvec;
    sort(P.begin(), P.end());
    for (int i = 0; i < P.size() - 1; i++)
        S.push_back({x_int, {P[i], P[i + 1]}, empvec});

    for (int i = 0; i < S.size(); i++){
        // for (int j = 0; j < S1.size(); j++){
        //     if (S1[j].y_inter.bottom == S[i].y_inter.bottom && S1[j].y_inter.top == S[i].y_inter.top)
                S[i].x_union = S1[i].x_union;
        //}
    }
    for (int i = 0; i < S.size(); i++){
        // for (int j = 0; j < S2.size(); j++){
        //     if (S2[j].y_inter.bottom == S[i].y_inter.bottom && S2[j].y_inter.top == S[i].y_inter.top)
                S[i].x_union.insert(S[i].x_union.end(), S2[i].x_union.begin(), S2[i].x_union.end());
        //}
    }
    return S;
}
vector<StripeTree> concatT(vector<StripeTree> S1, vector<StripeTree> S2, vector<int> P, Interval x_int){
    vector<StripeTree> S;
    sort(P.begin(), P.end());
    for (int i = 0; i < P.size() - 1; i++)
        S.push_back({x_int, {P[i], P[i + 1]}, NULL});

    for (int i = 0; i < S.size(); i++){
        if(S1[i].tree != NULL && S2[i].tree != NULL )
        {
            S[i].tree = new Ctree( S1[i].x_inter.top , 'U', S1[i].tree , S2[i].tree);
        }
        if(S1[i].tree != NULL && S2[i].tree == NULL )
        {
            S[i].tree = S1[i].tree;
        }
        if(S1[i].tree == NULL && S2[i].tree != NULL )
        {
            S[i].tree = S2[i].tree;
        }
        if(S1[i].tree == NULL && S2[i].tree == NULL )
        {
            S[i].tree = NULL;
        }
    }
    return S;
}

void inorderPrint(Ctree *root)
{
    if (!root)
        return;
    if (!root->left && !root->right)
    {
        vec.push_back(root->x);
        cout << root->x << " "<<root->side<<" ";
        return;
    }
    if (root->left)
       inorderPrint(root->left);
    if (root->right)
       inorderPrint(root->right);
}
int measure(vector<Stripe> Stripes){
    long long int area = 0;
    for( auto stripe: Stripes){
        for(auto in: stripe.x_union){
            area +=  (in.top - in.bottom) * (stripe.y_inter.top - stripe.y_inter.bottom);
        }
    }
    return area;
}
void findrange(Ctree *root, vector<pair<int,char>> &points , vector<pair<int,char>> &allpoints, int k1,int k2)
{
    if (!root)
        return;
    if (!root->left && !root->right)
    {
        //cout << root->x << " "<<root->side<<" ";
        allpoints.push_back({root->x,root->side});
        if(root->x >= k1 && root->x <=k2)
            points.push_back({root->x,root->side});
        return;
    }
    if (root->left)
       findrange(root->left,points,allpoints,k1,k2);
    if (root->right)
       findrange(root->right,points,allpoints,k1,k2);
}

vector<LineSegment> contour_pieces(Edge h , vector<StripeTree> S)
{
    vector<LineSegment> subpieces;
    StripeTree selectedStripe;
    if(h.side=='B')
    {
        for(auto stripe :  S)
        {
            if(stripe.y_inter.top == h.coord)
                selectedStripe = stripe;
        }
    }
    else if(h.side=='T')
    {
        for(auto stripe :  S)
        {
            if(stripe.y_inter.bottom == h.coord)
                selectedStripe = stripe;
        }
    }
    vector<pair<int,char>> points,allpoints;
    points.push_back({h.inter.bottom,'R'});
    findrange(selectedStripe.tree,points,allpoints,h.inter.bottom,h.inter.top );
    points.push_back({h.inter.top,'L'});
    //
    // FindIntervals(selectedStripe.tree , h.inter.bottom , h.inter.top ,points,allpoints);
    //

    for(int i=0;i<points.size()-1;i++)
    {
        if(points[i].second == 'R' && points[i+1].second =='L')
            subpieces.push_back({{points[i].first,points[i+1].first}, h.coord });
    }
    //cout<<allpoints.size()<<" size\n";
    //cout<<h.inter.bottom<<" "<<h.inter.top<<" thi sis range\n";
    for(int i=1;i<allpoints.size();i++)
    {
        //cout<<allpoints[i-1].first<<" "<<allpoints[i].first<<" \n";
        if(h.inter.bottom >= allpoints[i-1].first && h.inter.top <= allpoints[i].first)
        {    subpieces.clear();
        //cout<<"cleared\n";
        }
    }
    //cout<<"end function\n";
    return subpieces;
}
vector<LineSegment> contour(vector<Edge> H , vector<StripeTree> S)
{
    vector<LineSegment> contourpieces;
    for(auto edge :  H)
    {
        //cout<<edge.inter.bottom<<" "<<edge.inter.top<<" "<<edge.coord<<"\n";
        vector<LineSegment> subpieces = contour_pieces(edge , S);

        for(auto piece : subpieces)
            contourpieces.push_back(piece);
    }
    return contourpieces;
}

vector<Interval> findUnion(vector<Interval>  arr1 , vector<Interval> arr2)
{
    vector<Interval> v;
    int i=0 ,j =0 ;
    while(i<arr1.size() && j <arr2.size())
    {
        if (arr1[i].bottom < arr2[j].bottom || (arr1[i].bottom == arr2[j].bottom && arr1[i].top < arr2[j].top) || (arr1[i].bottom == arr2[j].bottom && arr1[i].top == arr2[j].top && arr1[i].id < arr2[j].id))
            v.push_back(arr1[i++]);

        else if (arr1[i].bottom > arr2[j].bottom || (arr1[i].bottom == arr2[j].bottom && arr1[i].top > arr2[j].top) || (arr1[i].bottom == arr2[j].bottom && arr1[i].top == arr2[j].top && arr1[i].id > arr2[j].id))
            v.push_back(arr2[j++]);

        else {
            v.push_back(arr2[j++]);
            i++;
        }
    }
    while (i < arr1.size())
        v.push_back(arr1[i++]);

    while (j < arr2.size())
        v.push_back(arr2[j++]);
    return v;
}
vector<Interval> findDifference(vector<Interval>  arr1 , vector<Interval> arr2)
{
    vector<Interval> v;
    int i=0 ,j =0 ;
    while(i<arr1.size() && j <arr2.size())
    {
        if (arr1[i].bottom < arr2[j].bottom || (arr1[i].bottom == arr2[j].bottom && arr1[i].top < arr2[j].top) || (arr1[i].bottom == arr2[j].bottom && arr1[i].top == arr2[j].top && arr1[i].id < arr2[j].id))
            v.push_back(arr1[i++]);

        else if (arr1[i].bottom > arr2[j].bottom || (arr1[i].bottom == arr2[j].bottom && arr1[i].top > arr2[j].top) || (arr1[i].bottom == arr2[j].bottom && arr1[i].top == arr2[j].top && arr1[i].id > arr2[j].id))
            v.push_back(arr2[j++]);

        else {
            j++;
            i++;
        }
    }
    while (i < arr1.size())
        v.push_back(arr1[i++]);

    while (j < arr2.size())
        v.push_back(arr2[j++]);
    return v;
}

vector<Interval> findIntersection(vector<Interval>  arr1 , vector<Interval> arr2)
{
    vector<Interval> v;
    int i=0 ,j =0 ;
    while(i<arr1.size() && j <arr2.size())
    {
        if (arr1[i].bottom < arr2[j].bottom || (arr1[i].bottom == arr2[j].bottom && arr1[i].top < arr2[j].top) || (arr1[i].bottom == arr2[j].bottom && arr1[i].top == arr2[j].top && arr1[i].id < arr2[j].id))
            i++;

        else if (arr1[i].bottom > arr2[j].bottom || (arr1[i].bottom == arr2[j].bottom && arr1[i].top > arr2[j].top) || (arr1[i].bottom == arr2[j].bottom && arr1[i].top == arr2[j].top && arr1[i].id > arr2[j].id))
            j++;
        else {
            j++;
            v.push_back(arr1[i++]);
        }
    }

    return v;
}

vector<int> findUnionNormal(vector<int>  arr1 , vector<int> arr2)
{
    vector<int> v;
    int i=0 ,j =0 ;
    while(i<arr1.size() && j <arr2.size())
    {
        if (arr1[i] < arr2[j])
            v.push_back(arr1[i++]);

        else if (arr2[j] < arr1[i])
            v.push_back(arr2[j++]);

        else {
            v.push_back(arr2[j++]);
            i++;
        }
    }
    while (i < arr1.size())
        v.push_back(arr1[i++]);

    while (j < arr2.size())
        v.push_back(arr2[j++]);
    return v;
}
