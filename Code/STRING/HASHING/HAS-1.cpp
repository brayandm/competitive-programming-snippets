// TAB_TRIGGER "__HASHING"

typedef long long ll;

const int HASH_ALPHABET_MAX_VALUE = 300;
const int HASH_SIZE = 1;

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

struct HASH_RAND
{
    vector<ll> bas;
    vector<ll> mod;
    int sz;
    HASH_RAND(int N)
    {
        assert(N > 0 & N <= 20);
        sz = N;
        for(int i = 0 ; i < N ; i++)
        {
            pair<ll,ll> pp = HASH_RANDOM_PRIMES(1e9,2e9);
            bas.push_back(pp.first);
            mod.push_back(pp.second);
        }
    }
} random_hash(HASH_SIZE);

struct HASH_POWER
{
    vector<vector<ll>> P;
    int sz;
    int K;
    HASH_POWER()
    {
        sz = HASH_ALPHABET_MAX_VALUE, K = random_hash.sz;
        P.resize(sz+1,vector<ll>(K));
        for(int j = 0 ; j < K ; j++)
        {
            P[0][j] = 1;
            for(int i = 0 ; i < sz ; i++)P[i+1][j] = P[i][j]*random_hash.bas[j]%random_hash.mod[j];
        }
    }
    void update(int N)
    {
        if(N < sz)return;
        P.resize(N+1,vector<ll>(K));
        for(int i = sz ; i < N ; i++)
        {
            for(int j = 0 ; j < K ; j++)
            {
                P[i+1][j] = P[i][j]*random_hash.bas[j]%random_hash.mod[j];
            }
        }
        sz = N;
    }
} hash_powers;

struct HASH
{
    vector<ll> hs;
    friend bool operator==(const HASH &h1, const HASH &h2)
    {
        for(int i = 0 ; i < h1.hs.size() ; i++)
        {
            if(h1.hs[i] != h2.hs[i])return false;
        }
        return true;
    }
    friend bool operator!=(const HASH &h1, const HASH &h2)
    {
        for(int i = 0 ; i < h1.hs.size() ; i++)
        {
            if(h1.hs[i] != h2.hs[i])return true;
        }
        return false;
    }
    friend bool operator<(const HASH &h1, const HASH &h2)
    {
        for(int i = 0 ; i < h1.hs.size() ; i++)
        {
            if(h1.hs[i] < h2.hs[i])return true;
        }
        return false;
    }
};

template<typename T>
HASH _HASHING(const T &s)
{
    int N = s.size(), K = random_hash.sz;
    HASH hh;
    hh.hs.resize(K);
    for(int j = 0 ; j < K ; j++)
    {
        for(int i = 0 ; i < N ; i++)hh.hs[j] = (hh.hs[j]*random_hash.bas[j]+s[i])%random_hash.mod[j];
    }
    return hh;
}

template<typename T>
HASH _RHASHING(const T &s)
{
    int N = s.size(), K = random_hash.sz;
    HASH hh;
    hh.hs.resize(K);
    for(int j = 0 ; j < K ; j++)
    {
        for(int i = N-1 ; i >= 0 ; i--)hh.hs[j] = (hh.hs[j]*random_hash.bas[j]+s[i])%random_hash.mod[j];
    }
    return hh;
}

template<typename T>
HASH _PHASHING(const T &s)
{
    int N = s.size(), K = random_hash.sz;
    HASH hh;
    hh.hs.resize(K);
    for(int j = 0 ; j < K ; j++)
    {
        for(int i = 0 ; i < N ; i++)hh.hs[j] = (hh.hs[j]+hash_powers.P[s[i]][j])%random_hash.mod[j];
    }
    return hh;
}

template<typename T>
struct HASHING
{
    vector<vector<ll>> H, rH, pH;
    int N, K;
    HASHING()
    {
    }
    HASHING(const T &s)
    {
        set(s);
    }
    void set(const T &s)
    {
        N = s.size();
        K = random_hash.sz;
        hash_powers.update(N);
        H.clear();
        rH.clear();
        pH.clear();
        H.resize(N+2,vector<ll>(K));
        rH.resize(N+2,vector<ll>(K));
        pH.resize(N+2,vector<ll>(K));
        for(int j = 0 ; j < K ; j++)
        {
            for(int i = 0 ; i < N ; i++)H[i+1][j] = (H[i][j]*random_hash.bas[j]+s[i])%random_hash.mod[j];
            for(int i = N-1 ; i >= 0 ; i--)rH[i+1][j] = (rH[i+2][j]*random_hash.bas[j]+s[i])%random_hash.mod[j];
            for(int i = 0 ; i < N ; i++)pH[i+1][j] = (pH[i][j]+hash_powers.P[s[i]][j])%random_hash.mod[j];
        }
    }
    HASH ha(int a, int b)
    {
        if(a > b)swap(a,b);
        assert(a >= 0 && b < N);
        HASH tp;
        for(int j = 0 ; j < K ; j++)
        {
            tp.hs.push_back((H[b+1][j]+random_hash.mod[j]-H[a][j]*hash_powers.P[b-a+1][j]%random_hash.mod[j])%random_hash.mod[j]);
        }
        return tp;
    }
    HASH rha(int a, int b)
    {
        if(a > b)swap(a,b);
        assert(a >= 0 && b < N);
        HASH tp;
        for(int j = 0 ; j < K ; j++)
        {
            tp.hs.push_back((rH[a+1][j]+random_hash.mod[j]-rH[b+2][j]*hash_powers.P[b-a+1][j]%random_hash.mod[j])%random_hash.mod[j]);
        }
        return tp;
    }
    HASH pha(int a, int b)
    {
        if(a > b)swap(a,b);
        assert(a >= 0 && b < N);
        HASH tp;
        for(int j = 0 ; j < K ; j++)
        {
            tp.hs.push_back((pH[b][j]+random_hash.mod[j]-pH[a-1][j])%random_hash.mod[j]);
        }
        return tp;
    }
};