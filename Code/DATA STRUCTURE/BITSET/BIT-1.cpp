// TAB_TRIGGER "__BITSET"

struct BITSET
{
    const int BAS = 128;
    const __uint128_t MBAS = 127;
    const __uint128_t DBAS = 7;
    const __uint128_t unit = 1;

    vector<__uint128_t> vect;
    __uint128_t lastmask;
    int sz;

    BITSET()
    {

    }

    BITSET(int n)
    {
        init(n);
    }

    BITSET(vector<bool> other)
    {
        *this = other;
    }

    int size()
    {
        return sz;
    }

    void init(int n)
    {
        vect.clear();
        sz = n;
        for(int i = 0 ; i < (sz>>DBAS) ; i++)
        {
            vect.emplace_back();
        }
        if(sz&MBAS)
        {
            vect.emplace_back();
        }
        lastmask = (unit<<(sz&MBAS))-1;
    }

    void resize(int n)
    {
        int tam = n>>DBAS;
        if(n&MBAS)tam++;
        if(sz <= n)
        {
            while(vect.size() < tam)
            {
                vect.emplace_back();
            }
        }
        else
        {
            while(vect.size() > tam)
            {
                vect.pop_back();
            }
            __uint128_t mask = (unit<<(n&MBAS))-1;
            if(n&MBAS)
            {
                vect.back() &= mask;
            }
        }
        sz = n;
        lastmask = (unit<<(sz&MBAS))-1;
    }

    vector<bool> get()
    {
        vector<bool> vvv;
        int tam = sz>>DBAS;
        int ltam = sz&MBAS;
        for(int i = 0 ; i < tam ; i++)
        {
            for(int j = 0 ; j < BAS ; j++)
            {
                if(vect[i]&(unit<<j))vvv.push_back(1);
                else vvv.push_back(0);
            }
        }
        if(ltam)
        {
            for(int j = 0 ; j < ltam ; j++)
            {
                if(vect.back()&(unit<<j))vvv.push_back(1);
                else vvv.push_back(0);
            }
        }
        return vvv;
    }

    bool get_value(int x)
    {
        assert(0 <= x && x < sz);
        if(vect[x>>DBAS]&(unit<<(x&MBAS)))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void set_value(int x, bool val)
    {
        assert(0 <= x && x < sz);
        if(val)
        {
            vect[x>>DBAS] |= (unit<<(x&MBAS));
        }
        else
        {
            vect[x>>DBAS] &= (~(unit<<(x&MBAS)));
        }
    }

    BITSET& operator=(const vector<bool> &other)
    {
        this->init(other.size());
        for(int i = 0 ; i < other.size() ; i++)
        {
            this->set_value(i, other[i]);
        }
        return *this;
    }

    BITSET& operator=(const BITSET &other)
    {
        this->vect = other.vect;
        this->lastmask = other.lastmask;
        this->sz = other.sz;
        return *this;
    }

    friend BITSET operator^(BITSET &bst1, BITSET &bst2)
    {
        BITSET bst(max(bst1.sz, bst2.sz));
        auto op = [&](__uint128_t a, __uint128_t b)
        {
            return a^b;
        };
        BITSET_BITWISE_OPERATION(bst, bst1, bst2, op);
        return bst;
    }

    BITSET& operator^=(BITSET &other)
    {
        *this = (*this)^other;
        return *this;
    }

    friend BITSET operator&(BITSET &bst1, BITSET &bst2)
    {
        BITSET bst(max(bst1.sz, bst2.sz));
        auto op = [&](__uint128_t a, __uint128_t b)
        {
            return a&b;
        };
        BITSET_BITWISE_OPERATION(bst, bst1, bst2, op);
        return bst;
    }

    BITSET& operator&=(BITSET &other)
    {
        *this = (*this)&other;
        return *this;
    }

    friend BITSET operator|(BITSET &bst1, BITSET &bst2)
    {
        BITSET bst(max(bst1.sz, bst2.sz));
        auto op = [&](__uint128_t a, __uint128_t b)
        {
            return a|b;
        };
        BITSET_BITWISE_OPERATION(bst, bst1, bst2, op);
        return bst;
    }

    BITSET& operator|=(BITSET &other)
    {
        *this = (*this)|other;
        return *this;
    }

    template<class F>
    friend void BITSET_BITWISE_OPERATION(BITSET &bst, BITSET &bst1, BITSET &bst2, F &op)
    {
        int tam = min(bst1.vect.size(), bst2.vect.size());
        for(int i = 0 ; i < tam-1 ; i++)
        {
            bst.vect[i] = op(bst1.vect[i], bst2.vect[i]);
        }
        __uint128_t mask1 = -1, mask2 = -1;
        if(bst1.vect.size() == tam)
        {
            if(bst1.lastmask)
            {
                mask1 = bst1.lastmask;
            }
        }
        if(bst2.vect.size() == tam)
        {
            if(bst2.lastmask)
            {
                mask2 = bst2.lastmask;
            }
        }
        if(mask1 < mask2)
        {
            bst.vect[tam-1] = mask1&op(bst1.vect[tam-1]&mask1, bst2.vect[tam-1]&mask1);
            bst.vect[tam-1] ^= bst2.vect[tam-1]&(mask2^mask1);
        }
        else
        {
            bst.vect[tam-1] = mask2&op(bst1.vect[tam-1]&mask2, bst2.vect[tam-1]&mask2);
            bst.vect[tam-1] ^= bst1.vect[tam-1]&(mask1^mask2);
        }
        if(bst1.sz < bst2.sz)
        {
            for(int i = tam ; i < bst.vect.size() ; i++)
            {
                bst.vect[i] = bst2.vect[i];
            }
        }
        else
        {
            for(int i = tam ; i < bst.vect.size() ; i++)
            {
                bst.vect[i] = bst1.vect[i];
            }
        }
    }

    struct reference
    {
        int x;
        BITSET *bst;
        void operator=(bool val)
        {
            (*bst).set_value(x, val);
        }
        operator bool() const
        {
            return (*bst).get_value(x);
        }
    };

    reference operator[](int x)
    {
        reference rf;
        rf.x = x;
        rf.bst = this;
        return rf;
    }
};