// TAB_TRIGGER "__XOR_BASIS_BITSET"

struct XOR_BASIS
{
    vector<bitset<__sz_bset>> basis;
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

    void insert(bitset<__sz_bset> mask)
    {
        for(int i = 0 ; i < D ; i++)
        {
            if(mask[i] == 0)continue;

            if(basis[i].none())
            {
                basis[i] = mask;
                sz++;
                return;
            }

            mask ^= basis[i];
        }
    }
};