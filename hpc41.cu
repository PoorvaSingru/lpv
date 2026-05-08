#include <stdio.h>

__global__ void add(int *a,int *b,int *c){
    int i=threadIdx.x;
    c[i]=a[i]+b[i];
}

int main(){
    int a[5]={1,2,3,4,5}, b[5]={5,4,3,2,1}, c[5];
    int *d_a,*d_b,*d_c;

    cudaMalloc(&d_a,20); cudaMalloc(&d_b,20); cudaMalloc(&d_c,20);
    cudaMemcpy(d_a,a,20,cudaMemcpyHostToDevice);
    cudaMemcpy(d_b,b,20,cudaMemcpyHostToDevice);

    add<<<1,5>>>(d_a,d_b,d_c);

    cudaMemcpy(c,d_c,20,cudaMemcpyDeviceToHost);

    for(int i=0;i<5;i++) printf("%d ",c[i]);
}