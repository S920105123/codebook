#include<bits/stdc++.h>  
using namespace std;  
typedef long long ll;  
const int N =100000;  
ll n, m, p= 24851, fac[N];  
void init()  
{  
    int i;  
    fac[0] =1;  
    for(i =1; i <= p; i++)  
        fac[i] = fac[i-1]*i % p;  
}  
ll q_pow(ll a, ll b)  
{  
    ll  ans =1;  
    while(b)  
    {  
        if(b &1)  ans = ans * a % p;  
        b>>=1;  
        a = a*a % p;     
    }  
    return  ans;  
}  
  
ll C(ll n, ll m)  
{  
    if(m > n)  return 0;  
    return  fac[n]*q_pow(fac[m]*fac[n-m], p-2) % p;  
}  
  
ll Lucas(ll n, ll m )  
{  
    if(m ==0)  return 1;  
    else return  (C(n%p, m%p)*Lucas(n/p, m/p))%p;  
}  
  
int main()  
{  
	init();  
    while(scanf("%lld %lld", &n, &m)!=EOF)  
    {  
       
        printf("%lld\n", Lucas(n-1, m-1));  
    }  
    return 0;  
}  