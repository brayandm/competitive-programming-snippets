// TAB_TRIGGER "__XOR_BASIS_INTEGER"

typedef long long ll;

struct XOR_BASIS
{
    vector<ll> basis;
    int sz;
    int D;

    XOR_BASIS()
    {
        init(0);
    }

    XOR_BASIS(int n)
    {
        init(n);
    }

    void init(int n)
    {
        D = n;
        sz = 0;
        basis.clear();
        basis.resize(D);
    }

    void insert(ll mask)
    {
        for(int i = 0 ; i < D ; i++)
        {
            if((mask&(1ll<<i)) == 0)continue;

            if(!basis[i])
            {
                basis[i] = mask;
                sz++;
                return;
            }

            mask ^= basis[i];
        }
    }
};