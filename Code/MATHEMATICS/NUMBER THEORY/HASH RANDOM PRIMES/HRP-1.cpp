// TAB_TRIGGER "__HASH_RANDOM_PRIMES"

typedef long long ll;
mt19937_64 HASH_RANDOM_PRIMES_GENERATOR(chrono::steady_clock::now().time_since_epoch().count());

pair<ll,ll> HASH_RANDOM_PRIMES(ll a, ll b)
{
    function<ll(ll,ll,ll)> mul = [&](ll a, ll b, ll m)
    {
        ll res = 0;
        while(b)
        {
            if(b&1)res = (res+a)%m;
            a = (a+a)%m;
            b >>= 1;
        }
        return res;
    };
    function<ll(ll,ll,ll)> pow = [&](ll a, ll b, ll m)
    {
        ll res = 1;
        while(b)
        {
            if(b&1)res = mul(res,a,m);
            a = mul(a,a,m);
            b >>= 1;
        }
        return res;
    };
    function<bool(ll,ll,ll,ll)> witness = [&](ll a, ll s, ll d, ll n)
    {
        ll x = pow(a, d, n);
        if(x == 1 || x == n-1)return 0;
        for(ll i = 0 ; i < s-1 ; i++)
        {
            x = mul(x, x, n);
            if(x == 1)return 1;
            if(x == n-1)return 0;
        }
        return 1;
    };
    function<bool(ll)> miller_rabin = [&](ll n)
    {
        if(n < 2)return 0;
        if(n == 2)return 1;
        if(n%2 == 0)return 0;
        ll d = n-1, s = 0;
        while(d%2 == 0)
        {
            s++;
            d /= 2;
        }
        vector<ll> test = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
        for(ll p : test)
        {
            if(p >= n)break;
            else if(witness(p, s, d, n))return 0;
        }
        return 1;
    };
    function<ll(ll,ll)> rd = [&](ll a, ll b)
    {
        return uniform_int_distribution<ll>(a,b)(HASH_RANDOM_PRIMES_GENERATOR);
    };
    function<ll(ll,ll)> random_prime = [&](ll a, ll b)
    {
        while(1)
        {
            ll num = rd(a,b);
            if(miller_rabin(num))return num;
        }
        return 0ll;
    };
    while(1)
    {
        ll p1 = random_prime(a,b);
        ll p2 = random_prime(a,b);
        if(__gcd(p1,p2) == 1)
        {
            if(p1 > p2)swap(p1,p2);
            return {p1,p2};
        }
    }
    return {0ll,0ll};
}