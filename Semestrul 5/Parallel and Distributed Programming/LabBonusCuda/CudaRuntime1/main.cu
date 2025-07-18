#include <iostream>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void polynomialMultiplicationKernel(int* A, int* B, int* C, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < 2 * n - 1) {
        C[i] = 0;
        for (int j = 0; j <= i; j++) {
            if (j < n && (i - j) < n) {
                C[i] += A[j] * B[i - j];
            }
        }
    }
}

void polynomialMultiplication(int* A, int* B, int* C, int n) {
    int* d_A, * d_B, * d_C;

    size_t size = n * sizeof(int);
    cudaMalloc(&d_A, size);
    cudaMalloc(&d_B, size);
    cudaMalloc(&d_C, (2 * n - 1) * sizeof(int));

    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);

    int blockSize = 256;
    int numBlocks = (2 * n - 1 + blockSize - 1) / blockSize;

    polynomialMultiplicationKernel <<< numBlocks, blockSize >>> (d_A, d_B, d_C, n);

    cudaMemcpy(C, d_C, (2 * n - 1) * sizeof(int), cudaMemcpyDeviceToHost);

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
}
