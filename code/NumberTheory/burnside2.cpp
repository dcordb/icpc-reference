//need factorial and inverse fatorial
//also need phi[n]

//Utility function for multinomials
int cnt(int n, int g, vector<int> &a)//here g is a divisor of gcd(a1,a2,...,an)
{
    long long int r = fact[n];
    for(int x : a)r = 1LL*r*ifact[x/g]%P;
    return r;
}

//Calculates differents values when rotations are neglected
int zc(int n, int gc, vector<int> &a)//here gc is gcd(a1,a2,...,an) PD: precalc gc for speed up
{
    long long int r = 0;
    for(int i = 1; i*i<=n; ++i)
    {
        if(i*i==n)
        {
            if(gc%i==0)r += 1LL*phi[i]*cnt(n/i,i,a)%P;
            if(r>=P)r-=P;
        }
        else if(n%i==0)
        {
            if(gc%i==0)r += 1LL*phi[i]*cnt(n/i,i,a)%P;
            if(r>=P)r-=P;
            if(gc%(n/i)==0)r += 1LL*phi[n/i]*cnt(i,n/i,a)%P;
            if(r>=P)r-=P;
        }
    }
    return r*fpow(n,P-2)%P;
}

//Calculates differents values when rotations and reflections are neglected
int zd(int n, int gc,int ci, vector<int> &a)//here ci stand for amount of odd values of a
{
	int ans = 1LL*zc(n,gc,a)*fpow(2,P-2)%P;
	if(n&1)
    {
        if(ci==1)
        {
            int r = cnt(n/2,2,a);
            ans += 1LL*r*fpow(2,P-2)%P;
            if(ans>=P)ans-=P;
        }
    }
    else
    {
        if(ci==0)
        {
            int cur = 1LL*cnt(n/2,2,a)*fpow(4,P-2)%P;
            ans += cur;
            if(ans>=P)ans-=P;
            cur = 1LL*cnt((n-2)/2,2,a)*fpow(4,P-2)%P;
            for(int x : a)
				{
                ans += 1LL*cur*(x/2)%P;
                if(ans>=P)ans-=P;
            }
        }
        else if(ci==2)
        {
            int cur = 2LL*cnt((n-2)/2,2,a)*fpow(4,P-2)%P;
            ans += cur;
            if(ans>=P)ans-=P;
        }
    }
    return ans;
}
