#include<bits/stdc++.h>

using namespace std;

typedef long long int ll;

ll dlog(ll a, ll b, ll m)
 {
    ll ans = 1e18 , n = (ll) sqrt (m + .0) + 1,an = 1;
    for (int i = 0; i<n; ++i) an = (an*a)%m;
    map<ll,ll> vals;
    for (ll i=1, cur=an; i<=n; ++i) 
    {
        if (!vals.count(cur))vals[cur] = i;
        cur = (cur*an)%m;
    }
    for (ll i=0, cur=b; i<=n; ++i) 
    {
        if (vals.count(cur)) 
        {
            ll tmp = vals[cur] * n - i;
            ans = min(ans,tmp);
        }
        cur = (cur*a)%m;
    }
    if(ans != 1e18)
        return ans;
    else
        return -1;
}


int main()
{
    int t;scanf("%d", &t);
    while(t--)
    {
        ll a,b,m;scanf("%lld %lld %lld", &a, &b, &m);
        printf("%lld\n", dlog(a,b,m)); 
    }

   return 0;
}
