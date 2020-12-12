/*
Range Minimum Query Data Structure
*/

template <typename T>
struct rmq { //0-indexed
    vector <int> lg;
    vector <vector <T>> dp;

    rmq(const vector <T> &a) : lg(a.size() + 1) {
        int n = a.size();

        for(int i = 1; i <= n; i++)
            lg[i] = log2(i);

        dp.resize(n, vector <T> (lg[n] + 1));
        for(int i = 0; i < n; i++)
            dp[i][0] = a[i];

        for(int j = 1; j <= lg[n]; j++) {
            for(int i = 0; i < n; i++) {
                int pos = i + (1 << (j - 1));
                dp[i][j] = dp[i][j - 1];
                
                if(pos < n)
                    dp[i][j] = merge(dp[i][j], dp[pos][j - 1]);
            }
        }
    }

    T merge(const T &a, const T &b) { //modify here
        return { min(a.first, b.first), max(a.second, b.second) };
    }

    T query(int a, int b) { // [, ] (inclusive in both ends)
        assert(a <= b);
        int k = lg[b - a + 1];
        return merge(dp[a][k], dp[b - (1 << k) + 1][k]);
    }
};

/*
Usage:
    rmq <pair <int, int>> r(p);
    r.query(a, b);

    This example show a simple RMQ holding a pair with minimum and maximum value over a range.
*/