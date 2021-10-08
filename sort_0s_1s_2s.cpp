#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int duplicates(int a[],int n){
 int low=0;     //all the elemts below low will be 0s
 int mid=0;
 int high=n-1;     //all elemengts after high will be 2s
 while(high>=mid){
     switch (a[mid]){
         case 0:
         swap(a[low++], a[mid++]); //https://hackershrine.com/interview-experience/cadence/cadence-interview-experience-1/
            break; 
        case 1:
        mid++; 
            break; 
        case 2:
        swap(a[mid],a[high--]);
            break;
     }
    
 }

}
  
int main(){
    int a[]={1,1,0,1,2,2,0,0,2,1};
    int n=sizeof(a)/sizeof(a[0]);
    duplicates(a,n);
   for (int i = 0; i <n; i++) 
        cout << a[i] << " "; 
  
    return 0;
}                                              //www.youtube.com/watch?v=oaVa-9wmpns