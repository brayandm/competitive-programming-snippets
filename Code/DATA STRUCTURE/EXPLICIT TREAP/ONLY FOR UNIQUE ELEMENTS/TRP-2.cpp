// TAB_TRIGGER "__TREAP"

template<typename T, class F = less<T>>
struct TREAP
{

private:

    struct node
    {
        T key;
        int prior = rng(), cnt = 0;
        node *l = nullptr, *r = nullptr;
    }*root = nullptr;

    T __end;
    T *_end = &__end;

    void clear(node *p)
    {
        if(!p)return;
        if(p->l)clear(p->l);
        if(p->r)clear(p->r);
        delete p;
    }

    void get(node *p, vector<T> &vect)
    {
        if(!p)return;
        if(p->l)get(p->l,vect);
        vect.push_back(p->key);
        if(p->r)get(p->r,vect);
    }

    int cnt(node *p)
    {
        return p ? p->cnt : 0;
    }

    void update(node *p)
    {
        if(p)p->cnt = cnt(p->l) + cnt(p->r) + 1;
    }

    void merge(node *&p, node *l, node *r)
    {
        if(!l || !r)p = l ? l : r;
        else if(l->prior > r->prior)merge(l->r, l->r, r), p = l;
        else merge(r->l, l, r->l), p = r;
        update(p);
    }

    void split(node *p, T key, node *&l, node *&r)
    {
        if(!p)l = r = nullptr;
        else if(F()(p->key, key))split(p->r, key, p->r, r), l = p;
        else split(p->l, key, l, p->l), r = p;
        update(p);
    }

    void xsplit(node *p, T key, node *&l, node *&r)
    {
        if(!p)l = r = nullptr;
        else if(!F()(key, p->key))xsplit(p->r, key, p->r, r), l = p;
        else xsplit(p->l, key, l, p->l), r = p;
        update(p);
    }

    void insert(node *&p, node *it)
    {
        if(!p)p = it;
        else if(it->prior > p->prior)split(p, it->key, it->l, it->r), p = it;
        else insert(F()(it->key, p->key) ? p->l : p->r, it);
        update(p);
    }

    void erase(node *&p, T key)
    {
        if(!p)return;
        if(!F()(p->key, key) && !F()(key, p->key))
        {
            node *it = p;
            merge(p, p->l, p->r);
            delete it;
        }
        else erase(F()(key, p->key) ? p->l : p->r, key);
        update(p);
    }

    T* find(node *p, T key)
    {
        if(!p)return end();
        if(!F()(p->key, key) && !F()(key, p->key))return &(p->key);
        return find(F()(key, p->key) ? p->l : p->r, key);
    }

    T* find_by_order(node *p, int k)
    {
        if(!p)return end();
        int pos = cnt(p->l)+1;
        if(pos == k+1)return &(p->key);
        return pos > k ? find_by_order(p->l, k) : find_by_order(p->r, k-pos);
    }

    void lower_bound(node *p, T key, T *&lb)
    {
        if(!p)return;
        if(!F()(p->key, key))lb = &(p->key), lower_bound(p->l, key, lb);
        else lower_bound(p->r, key, lb);
    }

    void upper_bound(node *p, T key, T *&ub)
    {
        if(!p)return;
        if(F()(key, p->key))ub = &(p->key), upper_bound(p->l, key, ub);
        else upper_bound(p->r, key, ub);
    }

public:

    int size()
    {
        if(root)return root->cnt;
        else return 0;
    }

    bool empty()
    {
        if(root)return false;
        return true;
    }

    void clear()
    {
        clear(root);
        root = nullptr;
    }

    T* end()
    {
        return _end;
    }

    vector<T> get()
    {
        vector<T> vect;
        get(root, vect);
        return vect;
    }

    void insert(T key)
    {
        if(find(root, key) != end())return;
        node *it = new node();
        it->key = key;
        insert(root, it);
    }

    void erase(T key)
    {
        erase(root, key);
    }

    T* find(T key)
    {
        return find(root, key);
    }

    int order_of_key(T key)
    {
        node *l, *r;
        split(root, key, l, r);
        int res = cnt(l);
        merge(root, l, r);
        return res;
    }

    T* find_by_order(int k)
    {
        return find_by_order(root, k);
    }

    T* lower_bound(T key)
    {
        T *lb = end();
        lower_bound(root, key, lb);
        return lb;
    }

    T* upper_bound(T key)
    {
        T *ub = end();
        upper_bound(root, key, ub);
        return ub;
    }
};