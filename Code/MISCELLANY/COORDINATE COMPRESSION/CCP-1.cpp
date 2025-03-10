// TAB_TRIGGER "__COORDINATE_COMPRESSION"

struct COORDINATE_COMPRESSION
{
    typedef long long ll;

    vector<ll> vect;
    bool is_compress = true;

    int size()
    {
        if(!is_compress)compress();
        return vect.size();
    }

    void clear()
    {
        vect.clear();
        is_compress = true;
    }

    void insert(ll x)
    {
        vect.push_back(x);
        is_compress = false;
    }

    void compress()
    {
        sort(vect.begin(), vect.end());
        vect.resize(unique(vect.begin(), vect.end()) - vect.begin());
        is_compress = true;
    }

    vector<ll> compress_offline(vector<ll> vect)
    {
        if(!vect.size())return vect;

        vector<pair<ll,int>> vvv;

        for(int i = 0 ; i < vect.size() ; i++)
        {
            vvv.push_back({vect[i],i});
        }

        sort(vvv.begin(), vvv.end());

        int cont = 0;
        ll last = vvv[0].first;

        vect[vvv[0].second] = 0;

        for(int i = 1 ; i < vvv.size() ; i++)
        {
            if(vvv[i].first != last)
            {
                cont++;
                last = vvv[i].first;
            }
            vect[vvv[i].second] = cont;
        }

        return vect;
    }

    int get(ll x)
    {
        if(!is_compress)compress();
        int pos = lower_bound(vect.begin(), vect.end(), x) - vect.begin();
        assert(pos != vect.size() && vect[pos] == x);
        return pos;
    }

    ll iget(int x)
    {
        if(!is_compress)compress();
        assert(0 <= x && x < vect.size());
        return vect[x];
    }
};