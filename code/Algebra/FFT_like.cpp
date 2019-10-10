//Other FFTs like transforms.

//xor
const int M = 30011;

typedef vector<ll> poly;

int fpow(int b, int p)
{
    ll r = 1ll;
    while(p)
    {
        if(p&1)r*=b,r%=M;
        b = 1ll*b*b%M;
        p>>=1;
    }
    return r;
}

poly FWHT(poly P, bool inverse) {
    for (int len = 1; 2*len <= sz(P); len <<= 1) {
        for (int i = 0; i < sz(P); i += 2 * len) {
            for (int j = 0; j < len; j++) {
                int u = P[i + j];
                int v = P[i + len + j];
                P[i + j] = (u + v)%M;
                P[i + len + j] = (u - v + M)%M;
            }
        }
    }
    if (inverse) {
        for (int i = 0; i < sz(P); i++)
            P[i] = 1ll*P[i]*fpow(sz(P),M-2)%M;
    }
    return P;
}
//and
const int M[2]= {55871,16035109};

typedef vector<int> poly;

poly FAT(poly P, bool inverse, int val) {
    for (int len = 1; 2 * len <= sz(P); len <<= 1) {
        for (int i = 0; i < sz(P); i += 2 * len) {
            for (int j = 0; j < len; j++) {
                int u = P[i + j];
                int v = P[i + len + j];

                if (!inverse) {
                    P[i + j] = v;
                    P[i + len + j] = u + v;
                    if(P[i+len+j]>=M[val])P[i+len+j]-=M[val];
                } else {
                    P[i + j] = -u + v;
                    P[i + len + j] = u;
                    if(P[i+j]>=M[val])P[i+j]-=M[val];
                }
            }
        }
    }

    return P;
}

//or
typedef vector<int> poly;

inline poly FOT(poly P, bool inverse) {
    for (int len = 1; 2 * len <= sz(P); len <<= 1) {
        for (int i = 0; i < sz(P); i += 2 * len) {
            for (int j = 0; j < len; j++) {
                int u = P[i + j];
                int v = P[i + len + j];

                if (!inverse) {
                    P[i + j] = u;
                    P[i + len + j] = u + v;
                } else {
                    P[i + j] = u;
                    P[i + len + j] = -u + v;
                }
            }
        }
    }

    return P;
}
