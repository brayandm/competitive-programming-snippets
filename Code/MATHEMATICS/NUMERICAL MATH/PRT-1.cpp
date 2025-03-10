// TAB_TRIGGER "__POLYNOMIAL_ROOTS"

typedef long double ld;

vector<ld> POLYNOMIAL_ROOTS(vector<ld> vect)
{
    const ld INF = 1000;
    const ld EPS = 1e-9;

    int N = vect.size();

    vector<ld> ans;

    if(N < 2)return ans;

    if(N == 2)
    {
        ans.push_back(-vect[0]/vect[1]);
        return ans;
    }

    vector<ld> der;

    for(int i = 1 ; i < N ; i++)
    {
        der.push_back(vect[i]*(ld)(i));
    }

    vector<ld> vvv = POLYNOMIAL_ROOTS(der);

    vvv.insert(vvv.begin(), -INF);
    vvv.push_back(INF);

    sort(vvv.begin(), vvv.end());

    function<ld(ld)> f = [&](ld x)
    {
        ld res = 0;
        ld pw = 1;
        for(int i = 0 ; i < N ; i++)
        {
            res += pw*vect[i];
            pw *= x;
        }
        return res;
    };

    for(int i = 1 ; i < vvv.size() ; i++)
    {
        ld a = vvv[i-1], b = vvv[i], mid = 0, fa = 0, fmid = 0, fb = 0;

        pair<ld,ld> res = {1e18,1e18};

        for(int x = 0 ; x < 100 ; x++)
        {
            mid = (a+b)/2;

            fa = f(a);
            fmid = f(mid);
            fb = f(b);

            res = min(res, {abs(fa),a});
            res = min(res, {abs(fmid),mid});
            res = min(res, {abs(fb),b});

            if(a >= b || a >= mid || mid >= b)break;

            if(fa*fmid < 0)b = mid;
            else a = mid;

            if(abs(res.first) < EPS)break;
        }

        if(abs(res.first) < EPS)ans.push_back(res.second);
    }

    return ans;
};