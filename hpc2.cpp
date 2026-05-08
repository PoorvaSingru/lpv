#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>
using namespace std;

// -------- Bubble Sort --------
void bubble_seq(vector<int>& a){
    for(int i=0;i<a.size();i++)
        for(int j=0;j<a.size()-i-1;j++)
            if(a[j]>a[j+1]) swap(a[j],a[j+1]);
}

void bubble_par(vector<int>& a){
    for(int i=0;i<a.size();i++){
        #pragma omp parallel for
        for(int j=0;j<a.size()-i-1;j++)
            if(a[j]>a[j+1]) swap(a[j],a[j+1]);
    }
}

// -------- Merge Sort (UPDATED - no push_back) --------
void merge(vector<int>& a,int l,int m,int r){
    vector<int> t(r-l+1);   // fixed size temp array
    int i=l, j=m+1, k=0;
    // compare both halves
    while(i<=m && j<=r){
        if(a[i] < a[j]) t[k++] = a[i++];
        else t[k++] = a[j++];
    }
    // copy remaining elements
    while(i<=m) t[k++] = a[i++];
    while(j<=r) t[k++] = a[j++];

    // copy back to original array
    for(int x=0;x<k;x++) a[l+x] = t[x];
}
// Sequential merge sort
void merge_seq(vector<int>& a,int l,int r){
    if(l<r){
        int m=(l+r)/2;
        merge_seq(a,l,m);
        merge_seq(a,m+1,r);
        merge(a,l,m,r);
    }
}
// Parallel merge sort
void merge_par(vector<int>& a,int l,int r){
    if(l<r){
        int m=(l+r)/2;

        #pragma omp parallel sections
        {
            #pragma omp section
            merge_par(a,l,m);       // left half

            #pragma omp section
            merge_par(a,m+1,r);     // right half
        }

        merge(a,l,m,r);             // merge both
    }
}
// -------- Main --------
int main(){
    int n; cout<<"Enter size: "; cin>>n;

    vector<int>a(n),b,c,d;

    cout<<"Enter elements:\n";
    for(int i=0;i<n;i++) cin>>a[i];

    b=c=d=a;

    double t;

    t=omp_get_wtime(); bubble_seq(b);
    cout<<"Seq Bubble Time: "<<omp_get_wtime()-t<<"\n";

    t=omp_get_wtime(); bubble_par(c);
    cout<<"Par Bubble Time: "<<omp_get_wtime()-t<<"\n";

    t=omp_get_wtime(); merge_seq(d,0,n-1);
    cout<<"Seq Merge Time: "<<omp_get_wtime()-t<<"\n";

    d=a;
    t=omp_get_wtime(); merge_par(d,0,n-1);
    cout<<"Par Merge Time: "<<omp_get_wtime()-t<<"\n";
}