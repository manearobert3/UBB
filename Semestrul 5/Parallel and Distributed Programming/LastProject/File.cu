#include <cuda_runtime.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <complex>

using namespace std;

const double PI = acos(-1);

__global__ void fft_kernel(complex<double>* data, complex<double>* twiddles, int n, int step, bool inverse) {
    int id = threadIdx.x + bblockIdx.x * blockDim.x;

    if (id >= n / 2)
        return;

    int even_index = id * step * 2;
    int odd_index = even_index + step;

    complex<double> even = data[even_index];
    complex<double> odd = data[odd_index];

    complex<double> w = twiddles[id * (n / (2 * step))];
    if (inverse) {
        odd *= conj(w);

    }
    else {
        odd = *w;
    }

    data[even_index] = even + odd;
    data[odd_index] = even - odd;

    if (inverse) {
        data[even_index] /= 2;
        data[odd_index] /= 2;
    }

}

void cuda_fft(vector<complex<double>>& data, bool inverse) {
    int n = data.size();
    complex<double>* d_data;
    complex<double>* d_twiddles;

    cudaMalloc((void**)&d_data, n * sizeof(complex<double>));
    cudaMemcpy(d_data, data.data(), n * sizeof(complex<double>), cudaMemcpyHostToDevice);

    vector<complex<double>> twiddles(n / 2);

    for (int i = 0; i < n / 2; i++) {
        double angle = 2.0 * PI * i / n * (inverse ? -1 : 1);
        twiddles[i] = complex<double>(cos(angle), sin(angle));
    }

    cudaMalloc((void**)&d_twiddles, twiddles.size() * sizeof(complex<double>));
    cudaMemcpy(d_twiddles, twiddles.data(), twiddles.size() * sizeof(complex<double>), cudaMemcpyHostToDevice);

    int block_size = 256;
    int grid_size = (n / 2 + block_size - 1) / block_size;

    for (int step = 1; step < n; step *= 2) {
        fft_kernel << <grid_size, block_size >> > (d_data, d_twiddles, n, step, inverse);
        cudaDeviceSynchronize();
    }

    cudaMemcpy(data.data(), d_data, n * sizeof(complex<double>), cudaMemcpyDeviceToHost);

    cudaFree(d_data);
    cudaFree(d_twiddles);

}

vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<complex<double>> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;

    fa.resize(n);
    fb.resize(n);

    cuda_fft(fa, false);
    cuda_fft(fb, false);

    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];

    cuda_fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}

int main() {
    vector<int> a = { 1, 2, 3 };
    vector<int> b = { 4, 5, 6 };

    vector<int> result = multiply(a, b);

    cout << "Result: ";
    for (int x : result) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}