// TAB_TRIGGER "__MONOTONIC_STACK"

template<typename T, class F = less<T>, class G = less<T>>
struct MONOTONIC_STACK
{
    const T oo = (G()(-4e18,4e18) ? 4e18 : -4e18);

    vector<pair<int,T>> S;
    vector<int> res;
    vector<T> vect;

    void insert(T x)
    {
        S.push_back({vect.size(),oo});
        vect.push_back(x);
        if(res.size())
        {
            if(F()(vect[S[res.back()].first] + S[res.back()].second, vect[S.back().first] + S.back().second))res.push_back(res.back());
            else res.push_back(res.size());
        }
        else res.push_back(res.size());
    }

    void update(T x)
    {
        if(vect.size() == 0)return;
        int best = -1;
        while(S.size() && G()(x,S.back().second))
        {
            if(best == -1) best = S.back().first;
            else
            {
                if(F()(vect[S.back().first], vect[best]))best = S.back().first;
            }
            S.pop_back();
            res.pop_back();
        }
        if(best == -1)return;
        S.push_back({best,x});
        if(res.size())
        {
            if(F()(vect[S[res.back()].first] + S[res.back()].second, vect[S.back().first] + S.back().second))res.push_back(res.back());
            else res.push_back(res.size());
        }
        else res.push_back(res.size());
    }

    T get()
    {
        assert(vect.size());
        return vect[S[res.back()].first] + S[res.back()].second;
    }
};