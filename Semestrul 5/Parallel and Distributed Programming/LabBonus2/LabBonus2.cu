#include <cuda_runtime.h>
#include <device_launch_parameters.h>

__global__ void polynomialMultiplicationKernel(const int* A, const int* B, int* C, int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    // Each thread computes C[i] if i is within the valid range
    if (i < 2 * n - 1)
    {
        int sum = 0;
        for (int j = 0; j <= i; j++) {
            // Ensure indices are in range
            if (j < n && (i - j) < n) {
                sum += A[j] * B[i - j];
            }
        }
        C[i] = sum;
    }
}
