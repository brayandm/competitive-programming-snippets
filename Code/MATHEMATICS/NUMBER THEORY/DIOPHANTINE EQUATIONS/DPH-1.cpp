// TAB_TRIGGER "__DIOPHANTINE_EQUATIONS"

template<typename T>
T EXT_GCD(T a, T b, T &x, T &y)
{
    if(a == 0)
    {
        x = 0;
        y = 1;
        return b;
    }
    T p = b / a;
    T g = EXT_GCD(b - p * a, a, y, x);
    x -= p * y;
    return g;
}

template<typename T>
bool DIOPHANTINE(T a, T b, T c, T &x, T &y, T &g)
{
    if(a == 0 && b == 0)
    {
        if(c == 0)
        {
            x = y = g = 0;
            return true;
        }
        return false;
    }
    if(a == 0)
    {
        if(c % b == 0)
        {
            x = 0;
            y = c / b;
            g = abs(b);
            return true;
        }
        return false;
    }
    if(b == 0)
    {
        if(c % a == 0)
        {
            x = c / a;
            y = 0;
            g = abs(a);
            return true;
        }
        return false;
    }
    g = EXT_GCD(a, b, x, y);
    if(c % g != 0)
    {
        return false;
    }
    T dx = c / a;
    c -= dx * a;
    T dy = c / b;
    c -= dy * b;
    x = dx + (T) ((__int128) x * (c / g) % b);
    y = dy + (T) ((__int128) y * (c / g) % a);
    g = abs(g);
    return true;
    // |x|, |y| <= max(|a|, |b|, |c|) [tested]
}

bool CHINESE_REMAINDER_THEOREM(long long k1, long long m1, long long k2, long long m2, long long &k, long long &m)
{
    k1 %= m1;
    if(k1 < 0) k1 += m1;
    k2 %= m2;
    if(k2 < 0) k2 += m2;
    long long x, y, g;
    if(!DIOPHANTINE(m1, -m2, k2 - k1, x, y, g))
    {
        return false;
    }
    long long dx = m2 / g;
    long long delta = x / dx - (x % dx < 0);
    k = m1 * (x - dx * delta) + k1;
    m = m1 / g * m2;
    assert(0 <= k && k < m);
    return true;
}

void NORMALIZE(vector<pair<long long, long long>> &vect)
{
    if(!vect.size())return;

    int N = vect.size();

    sort(vect.begin(), vect.end());

    vector<pair<long long, long long>> temp;

    for(int i = 0 ; i < N-1 ; i++)
    {
        if(vect[i].first != vect[i+1].first && vect[i].first <= vect[i].second)
        {
            temp.push_back(vect[i]);
        }
    }

    if(vect.back().first <= vect.back().second)
    {
        temp.push_back(vect.back());
    }

    vect.clear();

    if(!temp.size())return;

    N = temp.size();

    for(int i = 1 ; i < N ; i++)
    {
        temp[i-1].second = min(temp[i-1].second, temp[i].first-1);
        vect.push_back(temp[i-1]);
    }

    vect.push_back(temp.back());
}

bool IS_NORMALIZE(vector<pair<long long, long long>> &vect)
{
    int N = vect.size();

    for(int i = 0 ; i < N ; i++)
    {
        if(vect[i].first > vect[i].second)return false;
        if(i && vect[i-1].second > vect[i].first)return false;
    }

    return true;
}

long long DIOPHANTINE_EQUATIONS(long long A, long long B, long long C, vector<pair<long long, long long>> &v1, vector<pair<long long, long long>> &v2, long long &R1, long long &R2, long long &DX, long long &DY, vector<pair<long long, long long>> &lambda)
{
    assert(v1.size() && v2.size());

    if(!IS_NORMALIZE(v1))NORMALIZE(v1);
    if(!IS_NORMALIZE(v2))NORMALIZE(v2);

    for(int i = 0 ; i < v1.size() ; i++)
    {
        assert(v1[i].first <= v1[i].second);
        if(i)assert(v1[i-1].second < v1[i].first);
    }

    for(int i = 0 ; i < v2.size() ; i++)
    {
        assert(v2[i].first <= v2[i].second);
        if(i)assert(v2[i-1].second < v2[i].first);
    }

    R1 = R2 = DX = DY = 0;
    lambda.clear();

    if(A == 0 && B == 0)
    {
        if(C)return 0;

        R1 = v1[0].first;
        R2 = v2[0].first;

        long long s1 = 0, s2 = 0;

        for(auto x : v1)
        {
            s1 += (x.second-x.first+1);
        }

        for(auto y : v2)
        {
            s2 += (y.second-y.first+1);
        }

        return s1*s2;
    }
    if(A == 0)
    {
        if(C % B)return 0;

        bool ok = false;

        for(auto y : v2)
        {
            if(y.first <= C/B && C/B <= y.second)ok = true;
        }

        if(!ok)return 0;

        R1 = v1[0].first;
        R2 = C/B;
        DX = 1;
        DY = 0;

        long long s1 = 0;

        for(auto x : v1)
        {
            s1 += (x.second-x.first+1);
        }

        lambda = v1;

        for(auto &p : lambda)
        {
            p.first -= v1[0].first;
            p.second -= v1[0].first;
        }

        return s1;
    }
    if(B == 0)
    {
        if(C % A)return 0;

        bool ok = false;

        for(auto x : v1)
        {
            if(x.first <= C/A && C/A <= x.second)ok = true;
        }

        if(!ok)return 0;

        R1 = C/A;
        R2 = v2[0].first;
        DX = 0;
        DY = 1;

        long long s2 = 0;

        for(auto y : v2)
        {
            s2 += (y.second-y.first+1);
        }

        lambda = v2;

        for(auto &p : lambda)
        {
            p.first -= v2[0].first;
            p.second -= v2[0].first;
        }

        return s2;
    }

    long long X, Y, G;

    DIOPHANTINE(A,B,C,X,Y,G);

    if(C % G != 0)return 0;

    long long dx = B/G, dy = -A/G;

    function<long long(long long, long long)> down = [&](long long x, long long y)
    {
        if(y >= 0 || y%x == 0)return y/x;
        else return y/x + (x > 0 ? -1 : 1);
    };

    function<long long(long long, long long)> up = [&](long long x, long long y)
    {
        if(y <= 0 || y%x == 0)return y/x;
        else return y/x + (x > 0 ? 1 : -1);
    };

    vector<pair<long long, long long>> it1, it2;

    for(auto x : v1)
    {
        long long p1 = up(dx, x.first-X), p2 = down(dx, x.second-X);

        if(dx < 0)swap(p1, p2);

        if(p1 <= p2)it1.push_back({p1,p2});
    }

    if(dx < 0)reverse(it1.begin(), it1.end());

    for(auto y : v2)
    {
        long long p1 = up(dy, y.first-Y), p2 = down(dy, y.second-Y);

        if(dy < 0)swap(p1, p2);

        if(p1 <= p2)it2.push_back({p1,p2});
    }

    if(dy < 0)reverse(it2.begin(), it2.end());

    int pt1 = 0, pt2 = 0;

    while(pt1 < it1.size() && pt2 < it2.size())
    {
        long long me = min(it1[pt1].second, it2[pt2].second), ma = max(it1[pt1].first, it2[pt2].first);

        if(ma <= me)
        {
            if(lambda.size() && lambda.back().second+1 == ma)
            {
                lambda.back().second = me;
            }
            else
            {
                lambda.push_back({ma, me});
            }
        }

        if(it1[pt1].second < it2[pt2].second)pt1++;
        else pt2++;
    }

    if(!lambda.size())return 0;

    if(dx > 0)
    {
        R1 = X + dx*lambda[0].first;
        R2 = Y + dy*lambda[0].first;
        DX = dx;
        DY = dy;

        long long init = lambda[0].first;

        for(auto &p : lambda)
        {
            p.first -= init;
            p.second -= init;
        }
    }
    else
    {
        R1 = X + dx*lambda.back().second;
        R2 = Y + dy*lambda.back().second;
        DX = -dx;
        DY = -dy;

        long long init = lambda.back().second;

        for(auto &p : lambda)
        {
            p.first = init-p.first;
            p.second = init-p.second;
            swap(p.first, p.second);
        }

        reverse(lambda.begin(), lambda.end());
    }

    long long sum = 0;

    for(auto p : lambda)
    {
        sum += (p.second-p.first+1);
    }

    return sum;
}

long long DIOPHANTINE_SOLUTIONS_COUNTER(long long A, long long B, long long C, vector<pair<long long, long long>> &v1, vector<pair<long long, long long>> &v2)
{
    long long X, Y, dx, dy;
    vector<pair<long long, long long>> lambda;
    return DIOPHANTINE_EQUATIONS(A,B,C,v1,v2,X,Y,dx,dy,lambda);
}

vector<pair<long long, long long>> GET_DIOPHANTINE_SOLUTIONS(vector<long long> &vect, long long A, long long B, long long C, vector<pair<long long, long long>> &v1, vector<pair<long long, long long>> &v2)
{
    long long X, Y, dx, dy;
    vector<pair<long long, long long>> lambda;
    long long cont = DIOPHANTINE_EQUATIONS(A,B,C,v1,v2,X,Y,dx,dy,lambda);

    for(auto x : vect)
    {
        assert(0 <= x && x < cont);
    }

    bool is_order = true;

    for(int i = 1 ; i < vect.size() ; i++)
    {
        if(vect[i-1] > vect[i])is_order = false;
    }

    vector<pair<long long, long long>> sol;

    if(A == 0 && B == 0 && C == 0)
    {
        vector<__int128> sum;
        vector<long long> sum2;

        sum.push_back(0);
        sum2.push_back(0);

        long long s1 = 0, s2 = 0;

        for(auto y : v2)
        {
            s2 += (y.second-y.first+1);
            sum2.push_back(s2);
        }

        for(auto x : v1)
        {
            s1 += (x.second-x.first+1);
            sum.push_back(s1);
            sum.back() *= (__int128) s2;
        }

        if(is_order)
        {
            int pos = 0;

            for(auto x : vect)
            {
                while(sum[pos] <= x)pos++;
                long long nw = x-sum[pos-1];
                long long t1 = v1[pos-1].first + nw/s2;
                long long x2 = nw%s2;
                int pos2 = upper_bound(sum2.begin(), sum2.end(), x2) - sum2.begin();
                long long nw2 = x2-sum2[pos2-1];
                long long t2 = v2[pos2-1].first + nw2;

                sol.push_back({t1, t2});
            }

            return sol;
        }

        for(auto x : vect)
        {
            int pos = upper_bound(sum.begin(), sum.end(), x) - sum.begin();
            long long nw = x-sum[pos-1];
            long long t1 = v1[pos-1].first + nw/s2;
            long long x2 = nw%s2;
            int pos2 = upper_bound(sum2.begin(), sum2.end(), x2) - sum2.begin();
            long long nw2 = x2-sum2[pos2-1];
            long long t2 = v2[pos2-1].first + nw2;

            sol.push_back({t1, t2});
        }

        return sol;
    }

    vector<long long> sum;

    sum.push_back(0);

    for(auto p : lambda)
    {
        sum.push_back(sum.back() + (p.second-p.first+1));
    }

    if(is_order)
    {
        int pos = 0;

        for(auto x : vect)
        {
            while(sum[pos] <= x)pos++;
            long long nw = x-sum[pos-1];
            long long t1 = X+dx*(lambda[pos-1].first+nw);
            long long t2 = Y+dy*(lambda[pos-1].first+nw);
            sol.push_back({t1,t2});
        }

        return sol;
    }

    for(auto x : vect)
    {
        int pos = upper_bound(sum.begin(), sum.end(), x) - sum.begin();
        long long nw = x-sum[pos-1];
        long long t1 = X+dx*(lambda[pos-1].first+nw);
        long long t2 = Y+dy*(lambda[pos-1].first+nw);
        sol.push_back({t1,t2});
    }

    return sol;
}