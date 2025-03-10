// TAB_TRIGGER "__LI_CHAO_TREE"

template<typename T, class F = less<T>>
struct LI_CHAO_TREE
{
    bool sz = true;
    struct node
    {
        T func;
        node *L = NULL, *R = NULL;
    } ST;
    ll Li, Ri;
    LI_CHAO_TREE(ll a, ll b)
    {
        Li = a, Ri = b;
    }
    void add_function(T nw)
    {
        if(sz)ST.func = nw, sz = false;
        else li_chao_tree_update(nw,&ST,Li,Ri);
    }
    T get(ll x)
    {
        assert(!sz);
        return li_chao_tree_query(x,&ST,Li,Ri);
    }
    void li_chao_tree_update(T nw, node *pt, ll l, ll r)
    {
        ll m = (l+r)/2;
        bool lef = F()(nw.f(l),pt->func.f(l));
        bool mid = F()(nw.f(m),pt->func.f(m));
        if(mid)swap(nw,pt->func);
        if(l == r)return;
        if(lef != mid)
        {
            if(pt->L == NULL)pt->L = new node(), pt->L->func = nw;
            else li_chao_tree_update(nw,pt->L,l,m);
        }
        else
        {
            if(pt->R == NULL)pt->R = new node(), pt->R->func = nw;
            else li_chao_tree_update(nw,pt->R,m+1,r);
        }
    }
    T li_chao_tree_query(ll x, node *pt, ll l, ll r)
    {
        if(l == r)return pt->func;
        ll m = (l+r)/2;
        T tp = pt->func;
        if(x <= m && pt->L != NULL)
        {
            T qu = li_chao_tree_query(x,pt->L,l,m);
            if(F()(qu.f(x),tp.f(x)))tp = qu;
        }
        else if(pt->R != NULL)
        {
            T qu = li_chao_tree_query(x,pt->R,m+1,r);
            if(F()(qu.f(x),tp.f(x)))tp = qu;
        }
        return tp;
    }
};

struct line
{
    ll m, n;
    ll f(ll x)
    {
        return m*x+n;
    }
};