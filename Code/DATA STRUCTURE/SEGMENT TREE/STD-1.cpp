// TAB_TRIGGER "__SEGMENT_TREE"

typedef long long ll;

template<typename T, typename Q>
struct SEGMENT_TREE
{
    ll Li, Ri;

    int pt = 0;

    vector<T> ST;
    vector<int> L;
    vector<int> R;
    vector<bool> lazy;

    T query_res;
    bool query_flag, bs_flag;
    ll bs_pos;

    void new_node()
    {
        ST.push_back(T{});
        L.push_back(0);
        R.push_back(0);
        lazy.push_back(false);
    }

    SEGMENT_TREE()
    {

    }

    SEGMENT_TREE(ll a, ll b)
    {
        init(a,b);
    }

    void clear()
    {
        pt = 0;
        ST.clear();
        L.clear();
        R.clear();
        lazy.clear();
        new_node();
    }

    void init(ll a, ll b)
    {
        assert(a <= b);
        Li = a, Ri = b;
        clear();
    }

    void build(vector<T> &vect)
    {
        assert(Ri-Li+1 == (ll)vect.size());
        ST_build(0,Li,Ri,vect);
    }

    void insert(ll x, T nod)
    {
        ST_insert(0,Li,Ri,x,nod);
    }

    template<class F>
    ll binary_search_right(ll a, ll b, F f, T &tp)
    {
        query_res = T{};
        query_flag = false;
        bs_flag = false;
        bs_pos = b+1;
        ST_binary_search_right(0,Li,Ri,a,b,f);
        if(bs_flag)
        {
            tp = query_res;
            return bs_pos;
        }
        else
        {
            tp = T{};
            return bs_pos;
        }
    }

    template<class F>
    ll binary_search_left(ll a, ll b, F f, T &tp)
    {
        query_res = T{};
        query_flag = false;
        bs_flag = false;
        bs_pos = a-1;
        ST_binary_search_left(0,Li,Ri,a,b,f);
        if(bs_flag)
        {
            tp = query_res;
            return bs_pos;
        }
        else
        {
            tp = T{};
            return bs_pos;
        }
    }

    void update(ll x, Q &up)
    {
        ST_update(0,Li,Ri,x,x,up);
    }

    void update(ll a, ll b, Q &up)
    {
        ST_update(0,Li,Ri,a,b,up);
    }

    T query(ll x)
    {
        query_res = T{};
        query_flag = false;
        ST_query(0,Li,Ri,x,x);
        return query_res;
    }

    T query(ll a, ll b)
    {
        query_res = T{};
        query_flag = false;
        ST_query(0,Li,Ri,a,b);
        return query_res;
    }

    void ST_build(int node, ll l, ll r, vector<T> &vect)
    {
        if(l == r)
        {
            ST[node] = vect[l-Li];
            return;
        }
        else
        {
            L[node] = ++pt;
            new_node();
            R[node] = ++pt;
            new_node();
        }

        ll mid = l+(r-l)/2;

        ST_build(L[node],l,mid,vect);
        ST_build(R[node],mid+1,r,vect);

        ST[node].merge(ST[L[node]],ST[R[node]]);
    }

    void ST_insert(int node, ll l, ll r, ll x, T &nod)
    {
        if(l != r)
        {
            if(L[node] == 0)
            {
                L[node] = ++pt;
                new_node();
            }
            if(R[node] == 0)
            {
                R[node] = ++pt;
                new_node();
            }
        }

        if(lazy[node])
        {
            if(l != r)
            {
                ST[node].propagation(ST[L[node]],ST[R[node]]);
                lazy[L[node]] = true;
                lazy[R[node]] = true;
            }
            ST[node].update(l,r);
            lazy[node] = false;
        }

        if(x < l || r < x)return;

        if(l == r)
        {
            ST[node] = nod;
            return;
        }

        ll mid = l+(r-l)/2;

        ST_insert(L[node],l,mid,x,nod);
        ST_insert(R[node],mid+1,r,x,nod);

        ST[node].merge(ST[L[node]],ST[R[node]]);
    }

    template<class F>
    void ST_binary_search_right(int node, ll l, ll r, ll a, ll b, F &f)
    {
        if(l != r)
        {
            if(L[node] == 0)
            {
                L[node] = ++pt;
                new_node();
            }
            if(R[node] == 0)
            {
                R[node] = ++pt;
                new_node();
            }
        }

        if(lazy[node])
        {
            if(l != r)
            {
                ST[node].propagation(ST[L[node]],ST[R[node]]);
                lazy[L[node]] = true;
                lazy[R[node]] = true;
            }
            ST[node].update(l,r);
            lazy[node] = false;
        }

        if(a <= l && r <= b)
        {
            T query_temp = query_res;
            bool flag_temp = query_flag;
            if(query_flag)
            {
                T temp;
                temp.merge(query_res, ST[node]);
                query_res = temp;
            }
            else
            {
                query_res = ST[node];
                query_flag = true;
            }
            if(f(query_res))
            {
                query_res = query_temp;
                query_flag = flag_temp;
                ST_binary_search_into_right(node,l,r,f);
                bs_flag = true;
            }
            return;
        }

        ll mid = l+(r-l)/2;

        if(a <= mid)ST_binary_search_right(L[node],l,mid,a,b,f);
        if(bs_flag)return;
        if(b > mid)ST_binary_search_right(R[node],mid+1,r,a,b,f);
    }

    template<class F>
    void ST_binary_search_into_right(int node, ll l, ll r, F &f)
    {
        if(l != r)
        {
            if(L[node] == 0)
            {
                L[node] = ++pt;
                new_node();
            }
            if(R[node] == 0)
            {
                R[node] = ++pt;
                new_node();
            }
        }

        if(lazy[node])
        {
            if(l != r)
            {
                ST[node].propagation(ST[L[node]],ST[R[node]]);
                lazy[L[node]] = true;
                lazy[R[node]] = true;
            }
            ST[node].update(l,r);
            lazy[node] = false;
        }

        ll mid = l+(r-l)/2;

        if(l == r)
        {
            if(query_flag)
            {
                T temp;
                temp.merge(query_res, ST[node]);
                query_res = temp;
            }
            else
            {
                query_res = ST[node];
                query_flag = true;
            }
            bs_pos = l;
            return;
        }

        if(l != mid)
        {
            if(L[L[node]] == 0)
            {
                L[L[node]] = ++pt;
                new_node();
            }
            if(R[L[node]] == 0)
            {
                R[L[node]] = ++pt;
                new_node();
            }
        }

        if(lazy[L[node]])
        {
            if(l != mid)
            {
                ST[L[node]].propagation(ST[L[L[node]]],ST[R[L[node]]]);
                lazy[L[L[node]]] = true;
                lazy[R[L[node]]] = true;
            }
            ST[L[node]].update(l,mid);
            lazy[L[node]] = false;
        }

        T query_temp = query_res;
        bool flag_temp = query_flag;
        if(query_flag)
        {
            T temp;
            temp.merge(query_res, ST[L[node]]);
            query_res = temp;
        }
        else
        {
            query_res = ST[L[node]];
            query_flag = true;
        }

        if(f(query_res))
        {
            query_res = query_temp;
            query_flag = flag_temp;
            ST_binary_search_into_right(L[node],l,mid,f);
        }
        else
        {
            ST_binary_search_into_right(R[node],mid+1,r,f);
        }
    }

    template<class F>
    void ST_binary_search_left(int node, ll l, ll r, ll a, ll b, F &f)
    {
        if(l != r)
        {
            if(L[node] == 0)
            {
                L[node] = ++pt;
                new_node();
            }
            if(R[node] == 0)
            {
                R[node] = ++pt;
                new_node();
            }
        }

        if(lazy[node])
        {
            if(l != r)
            {
                ST[node].propagation(ST[L[node]],ST[R[node]]);
                lazy[L[node]] = true;
                lazy[R[node]] = true;
            }
            ST[node].update(l,r);
            lazy[node] = false;
        }

        if(a <= l && r <= b)
        {
            T query_temp = query_res;
            bool flag_temp = query_flag;
            if(query_flag)
            {
                T temp;
                temp.merge(ST[node], query_res);
                query_res = temp;
            }
            else
            {
                query_res = ST[node];
                query_flag = true;
            }
            if(f(query_res))
            {
                query_res = query_temp;
                query_flag = flag_temp;
                ST_binary_search_into_left(node,l,r,f);
                bs_flag = true;
            }
            return;
        }

        ll mid = l+(r-l)/2;

        if(b > mid)ST_binary_search_left(R[node],mid+1,r,a,b,f);
        if(bs_flag)return;
        if(a <= mid)ST_binary_search_left(L[node],l,mid,a,b,f);
    }

    template<class F>
    void ST_binary_search_into_left(int node, ll l, ll r, F &f)
    {
        if(l != r)
        {
            if(L[node] == 0)
            {
                L[node] = ++pt;
                new_node();
            }
            if(R[node] == 0)
            {
                R[node] = ++pt;
                new_node();
            }
        }

        if(lazy[node])
        {
            if(l != r)
            {
                ST[node].propagation(ST[L[node]],ST[R[node]]);
                lazy[L[node]] = true;
                lazy[R[node]] = true;
            }
            ST[node].update(l,r);
            lazy[node] = false;
        }

        ll mid = l+(r-l)/2;

        if(l == r)
        {
            if(query_flag)
            {
                T temp;
                temp.merge(ST[node], query_res);
                query_res = temp;
            }
            else
            {
                query_res = ST[node];
                query_flag = true;
            }
            bs_pos = l;
            return;
        }

        if(mid+1 != r)
        {
            if(L[R[node]] == 0)
            {
                L[R[node]] = ++pt;
                new_node();
            }
            if(R[R[node]] == 0)
            {
                R[R[node]] = ++pt;
                new_node();
            }
        }

        if(lazy[R[node]])
        {
            if(mid+1 != r)
            {
                ST[R[node]].propagation(ST[L[R[node]]],ST[R[R[node]]]);
                lazy[L[R[node]]] = true;
                lazy[R[R[node]]] = true;
            }
            ST[R[node]].update(mid+1,r);
            lazy[R[node]] = false;
        }

        T query_temp = query_res;
        bool flag_temp = query_flag;
        if(query_flag)
        {
            T temp;
            temp.merge(ST[R[node]], query_res);
            query_res = temp;
        }
        else
        {
            query_res = ST[R[node]];
            query_flag = true;
        }

        if(f(query_res))
        {
            query_res = query_temp;
            query_flag = flag_temp;
            ST_binary_search_into_left(R[node],mid+1,r,f);
        }
        else
        {
            ST_binary_search_into_left(L[node],l,mid,f);
        }
    }

    void ST_update(int node, ll l, ll r, ll a, ll b, Q &up)
    {
        if(l != r)
        {
            if(L[node] == 0)
            {
                L[node] = ++pt;
                new_node();
            }
            if(R[node] == 0)
            {
                R[node] = ++pt;
                new_node();
            }
        }

        if(lazy[node])
        {
            if(l != r)
            {
                ST[node].propagation(ST[L[node]],ST[R[node]]);
                lazy[L[node]] = true;
                lazy[R[node]] = true;
            }
            ST[node].update(l,r);
            lazy[node] = false;
        }

        if(r < a || l > b)return;

        if(a <= l && r <= b)
        {
            ST[node].push(up);
            if(l != r)
            {
                ST[node].propagation(ST[L[node]],ST[R[node]]);
                lazy[L[node]] = true;
                lazy[R[node]] = true;
            }
            ST[node].update(l,r);
            return;
        }

        ll mid = l+(r-l)/2;

        ST_update(L[node],l,mid,a,b,up);
        ST_update(R[node],mid+1,r,a,b,up);

        ST[node].merge(ST[L[node]],ST[R[node]]);
    }

    void ST_query(int node, ll l, ll r, ll a, ll b)
    {
        if(l != r)
        {
            if(L[node] == 0)
            {
                L[node] = ++pt;
                new_node();
            }
            if(R[node] == 0)
            {
                R[node] = ++pt;
                new_node();
            }
        }

        if(lazy[node])
        {
            if(l != r)
            {
                ST[node].propagation(ST[L[node]],ST[R[node]]);
                lazy[L[node]] = true;
                lazy[R[node]] = true;
            }
            ST[node].update(l,r);
            lazy[node] = false;
        }

        if(a <= l && r <= b)
        {
            if(query_flag)
            {
                T temp;
                temp.merge(query_res, ST[node]);
                query_res = temp;
            }
            else
            {
                query_res = ST[node];
                query_flag = true;
            }
            return;
        }

        ll mid = l+(r-l)/2;

        if(a <= mid)ST_query(L[node],l,mid,a,b);
        if(b > mid)ST_query(R[node],mid+1,r,a,b);
    }
};

struct QUERY
{
    ll sum = 0;
};

struct NODE
{
    ll sum = 0;
    ll lazysum = 0;
    void merge(NODE &H1, NODE &H2)
    {
        sum = H1.sum + H2.sum;
    }
    void push(QUERY &Q)
    {
        lazysum = Q.sum;
    }
    void update(ll l, ll r)
    {
        sum += (r-l+1)*lazysum;
        lazysum = 0;
    }
    void propagation(NODE &H1, NODE &H2)
    {
        H1.lazysum += lazysum;
        H2.lazysum += lazysum;
    }
};