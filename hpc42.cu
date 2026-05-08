#include <stdio.h>

__global__void mul(int *a,int *b,int *c){
    int i=threadIdx.x, j=threadIdx.y;
    int n=2, sum=0;
    for(int k=0;k<n;k++)
        sum+=a[i*n+k]*b[k*n+j];
    c[i*n+j]=sum;
}

int main(){
    int a[4]={1,2,3,4}, b[4]={5,6,7,8}, c[4];
    int *d_a,*d_b,*d_c;

    cudaMalloc(&d_a,16); cudaMalloc(&d_b,16); cudaMalloc(&d_c,16);
    cudaMemcpy(d_a,a,16,cudaMemcpyHostToDevice);
    cudaMemcpy(d_b,b,16,cudaMemcpyHostToDevice);

    dim3 t(2,2);
    mul<<<1,t>>>(d_a,d_b,d_c);

    cudaMemcpy(c,d_c,16,cudaMemcpyDeviceToHost);

    for(int i=0;i<4;i++) printf("%d ",c[i]);
}