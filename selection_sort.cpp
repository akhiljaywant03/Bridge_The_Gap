#include<iostream>
using namespace std;

int insertion(int a[],int n){
    int i,j,k;
    for(i=0;i<n;i++)
        for(j=i;j<n;j++)
            if(a[j+1]<a[j]){
                k=a[j];
                a[j]=a[j+1];
                a[j+1]=k;
            }
    for(i=0;i<n;i++)
        cout<<a[i]<<" ";
}
int main(){
    int a[]={-2,-7,2,5,9,-10};
    int n=sizeof(a)/sizeof(a[0]);
    insertion(a,n);
    return 0;
}