#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    vector<int> arr1(n);
    for(int i=0;i<n;i++)
        cin>>arr1[i];
    int m;
    cin>>m;
    vector<int> arr2(m);
    for(int i=0;i<m;i++)
        cin>>arr2[i];
    for(int x:  arr1)
        cout<<x<<" ";
    cout<<" \n";

    for(int x:  arr2)
        cout<<x<<" ";
    cout<<" \n";

    int i=0 ,j =0 ;
    while(i<n && j <m)
    {
        if (arr1[i] < arr2[j]) 
            i++;
  
        else if (arr2[j] < arr1[i]) 
            j++; 
  
        else { 
            cout<< arr1[i++]<<" ";
            j++;
        } 
    }
    // while (i < n) 
    //     cout << arr1[i++] << " "; 
  
    // while (j < m) 
    //     cout << arr2[j++] << " "; 
     
}


// 1 1 2 3  4 5
// 4 6 7