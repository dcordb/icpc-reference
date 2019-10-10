#include <bits/stdc++.h>
    
using namespace std;

int phi(int m)
{
   int r = m;
   for(int i = 2; i*i<=m; ++i)
   {
      if(m%i)continue;
      r/=i;r*=(i-1);
      while(m%i==0)m/=i;
   }
   if(m>1)r/=m,r*=(m-1);
   return r;
}

long long int zc(int n, int m)
{
   long long int ans = 0;
   for(int i = 1; i*i<=n; ++i)
   {
      if(n%i)continue;
      ans += 1ll*phi(i)*(pow(1.0*m,n/i)+.000001);
      if(i!=n/i)ans += 1ll*phi(n/i)*(pow(1.0*m,i)+.000001);
   }
   return ans/n;
}

long long int zd(int n, int m)
{
   double ans = .5*zc(n,m);
   if(n&1)
      ans += pow(1.0*m,(n-1)/2 + 1)*.5;
   else ans += (pow(1.0*m,n/2) + pow(1.0*m,n/2+1))*.25;
   return (long long int)(ans+.001); 
}

int main()
{
   int n, m;
   while(scanf("%d%d", &n, &m)!=EOF)
   {
     if(n==-1)break;
     printf("%I64d\n", zc(n,m));
   }

   return 0;
}