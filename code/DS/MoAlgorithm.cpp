//Mo's Algorithm Complejidad: O((n + m) * R * O(add + rem))

int R; //R = sqrt(n)

struct query {
    int l, r, id;

    query() {}

    query(int l, int r, int id) : l(l), r(r), id(id) {}

    bool operator < (const query &q) const {
        if(l / R != q.l / R)
            return l / R < q.l / R;
        //return r < q.r;
        return ((l / R) & 1) ? r < q.r : r > q.r; //este es mas rapido
    }
};

query q[MAXM];

void add(int i) {
    res += 1LL * a[i] * (2LL * freq[a[i]] + 1);
    freq[a[i]]++;
}

void rem(int i) {
    freq[a[i]]--;
    res -= 1LL * a[i] * (2LL * freq[a[i]] + 1);
}

int main() {
    scanf("%d%d", &n, &m); R = sqrt(n); //importante, setear R

    //esto es del problema especifico
    //////////////////////////////////
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    
    for(int i = 1; i <= m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        q[i] = query(a, b, i);
    }

    //////////////////////////////////

    sort(q + 1, q + m + 1); //ordenar queries

    int curL = 1, curR = 0;

    for(int i = 1; i <= m; i++) {
        int L = q[i].l;
        int R = q[i].r;

        while(curL > L) {
            add(--curL);
        }

        while(curR < R) {
            add(++curR);
        }

        while(curL < L) {
            rem(curL++);
        }

        while(curR > R) {
            rem(curR--);
        }

        ans[q[i].id] = res;
    }
}