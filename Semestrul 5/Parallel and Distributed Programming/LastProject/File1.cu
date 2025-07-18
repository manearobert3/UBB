#include <iostream>
#include <complex>
#include <vector>
#include <cmath>

using namespace std;

const double pi = acos(-1);

void fft(vector<complex<double>>& p, bool inverse)
{
    int n = p.size();

    if (n == 1)
        return;

    vector<complex<double>> pe(n / 2), po(n / 2);

    for (int i = 0; 2 * i < n; ++i)
    {
        pe[i] = p[2 * i];
        po[i] = p[2 * i + 1];
    }

    fft(pe, inverse);
    fft(po, inverse);

    double theta = 2.00 * pi / n * (inverse ? -1 : 1);

    complex<double> w(1), wn(cos(theta), sin(theta));

    for (int i = 0; 2 * i < n; ++i)
    {
        // perechile x si -x
        p[i] = pe[i] + w * po[i];
        p[i + n / 2] = pe[i] - w * po[i];
        if (inverse)
        {
            p[i] /= 2;
            p[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

vector<int> multiply(vector<int> const& a, vector<int> const& b)
{
    vector<complex<double>> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}

int main()
{
}