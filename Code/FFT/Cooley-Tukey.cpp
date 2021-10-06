//have to include these headers
#include <vector>
#include <complex>
#include <cmath>

using namespace std;
typedef complex<double> cpx;

//Cooley-Tukey FFT
void FFT(vector<cpx>& A, cpx w) {
    //base case
    int n = (int)A.size();
    if(n == 1) return;

    //split to even and odd
    vector<cpx> even(n / 2), odd(n / 2);
    for(int i = 0; i < n; ++i) {
        if(i & 1) odd[i / 2] = A[i];
        else even[i / 2] = A[i];
    }

    //Divide
    FFT(even, w * w);
    FFT(odd, w * w);

    cpx w_e(1, 0);

    //conquer
    for(int i = 0; i < n / 2; ++i) {
        A[i] = even[i] + w_e * odd[i];
        A[i + n / 2] = even[i] - w_e * odd[i];
        w_e *= w;
    }

    //Time complexity = n log n
}

//get discrete convolution of A and B
void product(vector<cpx>& A, vector<cpx>& B) {
    //get n, which satisfies n > 2 ^ ceil(log_2(size)) (when n = 2^k)
    int n = (A.size() <= B.size()) ? ceil(log2((double)B.size())) : ceil(log2((double)A.size()));
    n = pow(2, n + 1);

    A.resize(n);
    B.resize(n);
    vector<cpx> C(n);

    //n th root of unity (euler formula)
    cpx w(cos(2 * acos(-1) / n), sin(2 * acos(-1) / n));
    FFT(A, w);
    FFT(B, w);

    //multiply DFT
    for(int i = 0; i < n; ++i) C[i] = A[i] * B[i];

    //Inverse FFT to get Coefficient
    FFT(C, cpx(1, 0) / w);
    for(int i = 0; i < n; ++i) {
        C[i] /= cpx(n, 0);
        C[i] = cpx(round(C[i].real()), round(C[i].imag()));
    }
}

/*
//Cooley-Tukey FFT
void FFT(vector<cpx>& A, bool invert) {
    int n = (int)A.size();
    for(int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for(; j >= bit; bit >>= 1) j -= bit;
        j += bit;
        if(i < j) swap(A[i], A[j]);
    }    

    for(int length = 2; length <= n; length <<= 1) {
        double ang = 2 * PI / length * (invert ? -1 : 1);
        cpx w(cos(ang), sin(ang));

        for(int i = 0; i < n; i += length) {
            cpx w_i(1, 0);
            for(int j = 0; j < length / 2; ++j) {
                cpx u = A[i + j], v = A[i + j + length / 2] * w_i;
                A[i + j] = u + v;
                A[i + j + length / 2] = u - v;
                w_i *= w;
            }
        }
    }
    
    if(invert) {
        for(int i = 0; i < n; ++i) {
            A[i] /= cpx(n, 0);
            A[i] = cpx(round(A[i].real()), round(A[i].imag()));
        }
    }
}
*/ //faster version of FFT (https://blog.myungwoo.kr/54)