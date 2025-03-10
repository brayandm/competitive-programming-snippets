// TAB_TRIGGER "__HASH_TABLE"

struct HASH_RAND
{
    typedef unsigned long long ull;
    ull mod = 0;
    ull bas = 0;
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
    bool PRIME_TEST(ull x)
    {
        if(x < 2)return false;
        for(ull i = 2 ; i*i <= x ; i++)
        {
            if(x%i == 0)return false;
        }
        return true;
    }
    ull PRIME_RAND(ull a, ull b)
    {
        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        while(1)
        {
            ull num = uniform_int_distribution<ull>(a,b)(rng);
            if(PRIME_TEST(num))return num;
        }
    };
    HASH_RAND()
    {
        ull v1, v2;
        while(1)
        {
            v1 = PRIME_RAND(1e9,2e9);
            v2 = PRIME_RAND(1e9,2e9);
            if(v1 != v2)break;
        }
        if(v1 > v2)swap(v1,v2);
        bas = v1;
        mod = v2;
    }
} random_hash;

struct HASH
{
    /*unordered_map<key,value,hash> mp*/
    typedef long long ll;
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