// TAB_TRIGGER "__FACTORIAL"

ll FACTORIAL(ll N)
{
    assert(N >= 0);

    if(N == 0)return 1;

    ll SQ = 0;

    for(ll i = 1 ; i*i <= N ; i++)
    {
        SQ = i;
    }

    function<vector<mint>(ll,ll)> st = [&](ll a, ll b)
    {
        if(a == b)return (vector<mint>)
        {
            a,1
        };
        ll mid = (a+b)/2;
        return st(a,mid)*st(mid+1,b);
    };

    vector<mint> vect = st(1,SQ);

    ll tam = N/SQ;

    vector<mint> temp;

    for(ll i = 0, j = 0 ; i < tam ; i++, j+=SQ)
    {
        temp.push_back(j);
    }

    ll res = 1;

    for(ll i = tam*SQ+1 ; i <= N ; i++)
    {
        res = res*i%MOD;
    }

    vector<mint> vvv = evaluate(vect, temp);

    for(auto x : vvv)
    {
        res = res*x.val%MOD;
    }

    return res;
}