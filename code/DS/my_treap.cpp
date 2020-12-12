//NOT FINISHED

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

random_device rd{};
auto gen = mt19937(rd());
auto uniform = uniform_int_distribution();
///////////////////////////////////////////

/*
    Treap maintaining distinct keys. If equal keys are needed add a pair{x, c++} for each
    x you want to add.

    It mantains the following properties for a node u with subtrees a and b as children:
        1- p(u) <= min(p(a), p(b))
        2- k(a) < k(u) < k(b)
*/

struct no_info {};

template <typename K, typename T>
struct node {
    K k;        //key
    int p;      //priority
    int ch[2];  //children... 0 is left, 1 is right
    T d;        //data of node

    node(K k, int p = uniform(gen), T d = no_info{}) : k(k), p(p), d(d) { ch[0] = ch[1] = -1; }
};

template <typename K, typename T>
struct treap {
    using Node = node <K, T>;
    vector <Node> t;

    int new_node(const Node &x) {
        t.push_back(x);
        return (int) t.size() - 1;
    }

    int rotate(int u, int v, int w) {
        if(t[v].p >= t[u].p) {
            t[u].ch[w] = v;
            return u;
        }

        t[u].ch[w] = t[v].ch[w ^ 1];
        t[v].ch[w ^ 1] = u;

        return v;
    }

    int insert(int u, const Node &x) {
        if(u == -1)
            return new_node(x);

        if(x.k == t[u].k)
            return u;

        int w = x.k > t[u].k;
        return rotate(u, insert(t[u].ch[w], x), w);
    }

    int find(int u, const K &k) {
        while(u != -1) {
            if(k == t[u].k)
                return u;
            
            u = t[u].ch[k > t[u].k];
        }

        return -1;
    }

    pair <int, int> split(int u, const K &k) {
        //always remember to join when done
        return insert(u, Node(k, -1));
    }

    int get_max(int u) {
        int mx = numeric_limits <int> :: min();

        while(u != -1) {
            mx = t[u].k;
            u = t[u].ch[1];
        }

        return mx;
    }

    int get_min(int u) {
        int mn = numeric_limits <int> :: max();

        while(u != -1) {
            mn = t[u].k;
            u = t[u].ch[0];
        }

        return mn;
    }

    //all nodes from u must be less than all nodes from v
    int join(int u, int v) {
        #ifdef LOCAL
            (assert(get_max(u) < get_min(v)));
        #endif

        assert(u != -1 || v != -1);  //both can't be -1

        if(u == -1 || v == -1)
            return (u == -1) ? v : u;

        if(t[u].p <= t[v].p) {
            t[u].ch[1] = join(t[u].ch[1], v);
            return u;
        }

        t[v].ch[0] = join(u, t[v].ch[0]);
        return v;
    }

    int erase(int u, const K &k) {
        if(k == t[u].k)
            return join(t[u].ch[0], t[u].ch[1]);

        int r = u, p = -1, w = -1;

        while(u != -1) {
            if(k == t[u].k) {
                t[p].ch[w] = join(t[u].ch[0], t[u].ch[1]);
                break;
            }

            p = u, w = k > t[u].k;
            u = t[u].ch[w];
        }

        assert(u != -1);  //key k doesn't exists
        return r;
    }

    int dfs_depth(int u) {
        if(u == -1)
            return 0;

        return max(dfs_depth(t[u].ch[0]), dfs_depth(t[u].ch[1])) + 1;
    }

    void dfs(int u) {
        if(u == -1)
            return;

        dbg(t[u].k, t[u].p);

        if(t[u].ch[0] != -1)
            cerr << "left son key = " << t[t[u].ch[0]].k << '\n';

        if(t[u].ch[1] != -1)
            cerr << "right son key = " << t[t[u].ch[1]].k << '\n';

        dfs(t[u].ch[0]);
        dfs(t[u].ch[1]);
    }
};

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int n, m;
    cin >> n >> m;

    treap <int, (1, (int) 1e6);

    vector <int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        st.upd(0, 1, a[i], -1);
    }

    vector <int> b(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> b[i];
        st.upd(0, 1, b[i], +1);
    }

    int q;
    cin >> q;

    while(q--) {
        int op, x, y; cin >> op >> x >> y;

        if(op == 1) {
            st.upd(0, 1, a[x], +1);
            a[x] = y;
            st.upd(0, 1, a[x], -1);
        }

        else if(op == 2) {
            st.upd(0, 1, b[x], -1);
            b[x] = y;
            st.upd(0, 1, b[x], +1);
        }

        cout << st.fnd_neg(0) << '\n';
    }

    return 0;
}