#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

void DBG() { cerr << "]" << '\n'; }
template<class H, class... T> void DBG(H h, T... t) {
    cerr << h;
    if (sizeof...(t)) cerr << ", ";
    DBG(t...);
}

#ifdef LOCAL // compile with -DLOCAL
    #define dbg(...) cerr << "LINE(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#else
    #define dbg(...) 0
#endif

const int64 INF = numeric_limits <int64> :: max() / 2;

struct info {
    using T = vector <vector <int64> >;
    T dp;

    info() { dp = neutro().dp; }

    info(int value) {
        dp = neutro().dp;
        dp[0][1] = value;
        dp[1][1] = -value;
    }

    info(T dp) : dp(dp) {}

    static info neutro() { return info(T(2, vector <int64> (2, -INF))); }

    info merge(const info &other) {
        T ans = neutro().dp;

        for(int s = 0; s < 2; s++) {
            for(int p = 0; p < 2; p++) {
                ans[s][p] = max(ans[s][p], max(dp[s][p], other.dp[s][p]));

                for(int r = 0; r < 2; r++)
                    ans[s][p ^ r] = max(ans[s][p ^ r], dp[s][p] + other.dp[s ^ p][r]);
            }
        }

        return info(ans);
    }
};

template <typename T>
struct stree {
    int n;
    vector <T> t;
    
    //vector a must be 0-indexed
    stree(vector <int> a) : n(a.size()) {
        t.assign(2 * n, T::neutro());

        for(int i = 0; i < n; i++)
            t[i + n] = T(a[i]);

        for(int i = n - 1; i > 0; i--)
            t[i] = t[2 * i].merge(t[2 * i + 1]);
    }

    //position (0-indexed) and value
    void upd(int i, int x) {
        for(t[i += n] = T(x); i >>= 1;)
            t[i] = t[2 * i].merge(t[2 * i + 1]);
    }

    //query from [l, r], 0-indexed
    T query(int l, int r) {
        T L, R;

        for(l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if(l & 1) L = L.merge(t[l++]);
            if(!(r & 1)) R = t[r--].merge(R);
        }

        return L.merge(R);
    }
};

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t; cin >> t;

    while(t--) {
        int n, q; cin >> n >> q;

        vector <int> a(n);
        for(int &o : a)
            cin >> o;

        stree <info> st(a);

        info opt = st.query(0, n - 1);
        cout << max(opt.dp[0][0], opt.dp[0][1]) << '\n';

        while(q--) {
            int l, r;
            cin >> l >> r;
            l--, r--;

            if(l != r) {
                st.upd(l, a[r]);
                st.upd(r, a[l]);
                swap(a[l], a[r]);
            }

            info opt = st.query(0, n - 1);
            cout << max(opt.dp[0][0], opt.dp[0][1]) << '\n';
        }
    }

    return 0;
}