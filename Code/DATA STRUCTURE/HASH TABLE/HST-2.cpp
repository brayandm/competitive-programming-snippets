// TAB_TRIGGER "__HASH_TABLE"

const int __MAXTAM = 1e5;
typedef int __tkey;
typedef int __tvalue;
typedef long long ll;
vector<pair<__tkey,__tvalue>> __arr[__MAXTAM];
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
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
        return uniform_int_distribution<ll>(a,b)(rng);
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
struct HASH_RAND
{
    typedef unsigned long long ull;
    ll bas = 0;
    ll mod = 0;
    ull hash(ull a, ull b)
    {
        __uint128_t tp;
        a++;
        b++;
        tp = a;
        tp *= bas;
        tp += b;
        tp %= mod;
        return tp;
    }
    HASH_RAND()
    {
        tie(bas, mod) = HASH_RANDOM_PRIMES(__MAXTAM/2,__MAXTAM);
    }

} random_hash;
struct HASH
{
    /*unordered_map<key,value,hash> mp*/
    typedef long long ll;
    size_t operator()(const ll &x)const
    {
        ll has = random_hash.hash(0,x);
        return has;
    }
    size_t operator()(const pair<ll,ll> &x)const
    {
        ll has = random_hash.hash(x.first,x.second);
        return has;
    }
    size_t operator()(const vector<ll> &vect)const
    {
        ll has = 0;
        for(auto x : vect)has = random_hash.hash(has,x);
        return has;
    }
    size_t operator()(const string &cad)const
    {
        ll has = 0;
        for(auto x : cad)has = random_hash.hash(has,x);
        return has;
    }
};
int __hash(__tkey key)
{
    HASH hs;
    return hs(key);
}
void __set(__tkey key, __tvalue value)
{
    int hs = __hash(key);
    for(int i = 0 ; i < __arr[hs].size() ; i++)
    {
        if(__arr[hs][i].first == key)
        {
            __arr[hs][i].second = value;
            return;
        }
    }
    __arr[hs].push_back({key, value});
}
__tvalue __get(__tkey key)
{
    int hs = __hash(key);
    for(int i = 0 ; i < __arr[hs].size() ; i++)
    {
        if(__arr[hs][i].first == key)
        {
            return __arr[hs][i].second;
        }
    }
    __arr[hs].emplace_back();
    __arr[hs].back().first = key;
    return __arr[hs].back().second;
}
void __delete(__tkey key)
{
    int hs = __hash(key);
    for(int i = 0 ; i < __arr[hs].size() ; i++)
    {
        if(__arr[hs][i].first == key)
        {
            __arr[hs].erase(__arr[hs].begin()+i);
            return;
        }
    }
}
bool __find(__tkey key)
{
    int hs = __hash(key);
    for(int i = 0 ; i < __arr[hs].size() ; i++)
    {
        if(__arr[hs][i].first == key)
        {
            return true;
        }
    }
    return false;
}
struct __unordered_map
{
    struct reference
    {
        __tkey key;
        void operator=(__tvalue value)
        {
            __set(key, value);
        }
        operator __tvalue() const
        {
            return __get(key);
        }
    };
    reference operator[](__tkey key)
    {
        reference rf;
        rf.key = key;
        return rf;
    }
    void insert(pair<__tkey,__tvalue> x)
    {
        __set(x.first, x.second);
    }
    bool find(__tkey x)
    {
        return __find(x);
    }
    void erase(__tkey x)
    {
        __delete(x);
    }
};