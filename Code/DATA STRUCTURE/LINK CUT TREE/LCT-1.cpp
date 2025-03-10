// TAB_TRIGGER "__LINK_CUT_TREE"

struct LINK_CUT_TREE
{
    struct node
    {
        node *ch[2], *p;
        bool rev;
        int sz, vsub, sub;
        int val, sum, lazy;

        node()
        {
            ch[0] = ch[1] = p = NULL;
            rev = 0;
            sz = vsub = sub = 0;
            val = sum = lazy = 0;
            update();
        }

        int get_sz(node *x)
        {
            return x ? x->sz : 0;
        }

        int get_sub(node *x)
        {
            return x ? x->sub : 0;
        }

        int get_sum(node *x)
        {
            return x ? x->sum : 0;
        }

        void prop() // lazy prop
        {
            if(rev)
            {
                swap(ch[0], ch[1]);
                if(ch[0])ch[0]->rev ^= 1;
                if(ch[1])ch[1]->rev ^= 1;
                rev = 0;
            }
            if(lazy)
            {
                sum += sz*lazy;
                val += lazy;
                if(ch[0])ch[0]->lazy += lazy;
                if(ch[1])ch[1]->lazy += lazy;
                lazy = 0;
            }
        }

        void update() // recalc vals
        {
            if(ch[0])ch[0]->prop();
            if(ch[1])ch[1]->prop();
            sz = 1 + get_sz(ch[0]) + get_sz(ch[1]);
            sub = 1 + get_sub(ch[0]) + get_sub(ch[1]) + vsub;
            sum = val + get_sum(ch[0]) + get_sum(ch[1]);
        }

        void update_vsub(node *x, bool add) // update virtual children
        {
            if(add)vsub += x->sub;
            else vsub -= x->sub;
        }

        int dir()
        {
            if(!p)return -2; // root of LCT component
            if(p->ch[0] == this)return 0; // left child
            if(p->ch[1] == this)return 1; // right child
            return -1; // root of current splay tree
        }

        bool is_root()
        {
            return dir() < 0;
        }

        friend void set_link(node *x, node *y, int d)
        {
            if(y)y->p = x;
            if(d >= 0)x->ch[d] = y;
        }

        void rot() // assume p and p->p propagated
        {
            assert(!is_root());
            int x = dir();
            node *g = p;
            set_link(g->p, this, g->dir());
            set_link(g, ch[x^1], x);
            set_link(this, g, x^1);
            g->update();
        }

        void splay() // bring this to top of splay tree
        {
            while(!is_root() && !p->is_root())
            {
                p->p->prop(), p->prop(), prop();
                dir() == p->dir() ? p->rot() : rot();
                rot();
            }
            if(!is_root())p->prop(), prop(), rot();
            prop();
            update();
        }

        node* find_by_order(int k) // find by order of splay tree
        {
            prop();
            int z = get_sz(ch[0]);
            if(k == z)
            {
                splay();
                return this;
            }
            return k < z ? ch[0]->find_by_order(k) : ch[1]->find_by_order(k-z-1);
        }

        void access() // puts node on the preferred path, splay (right subtree is empty)
        {
            for(node *v = this, *pre = NULL ; v ; v = v->p)
            {
                v->splay(); // now update virtual children
                if(pre)v->update_vsub(pre, false);
                if(v->ch[1])v->update_vsub(v->ch[1], true);
                v->ch[1] = pre;
                v->update();
                pre = v;
            }
            splay();
            assert(!ch[1]);
        }

        void make_root() // make node root of LCT component
        {
            access();
            rev ^= 1;
            access();
            assert(!ch[0] && !ch[1]);
        }

        friend node* lca(node *x, node *y)
        {
            if(x == y)return x;
            x->access(), y->access();
            if(!x->p)return NULL;
            x->splay();
            return x->p ?: x; // y was below x in latter case
        } // access at y did not affect x -> not connected

        friend bool connected(node *x, node *y)
        {
            return lca(x, y);
        }

        int depth() // # nodes above
        {
            access();
            return get_sz(ch[0]);
        }

        node* get_root() // get root of LCT component
        {
            access();
            node *a = this;
            while(a->ch[0])a = a->ch[0], a->prop();
            a->access();
            return a;
        }

        node* ancestor(int k) // get k-th parent on path to root
        {
            access();
            k = get_sz(ch[0])-k;
            assert(k >= 0);
            return find_by_order(k);
        }

        void set(int v)
        {
            access();
            val = v;
            update();
        }

        friend void link(node *x, node *y, bool force = 0) // make y parent of x
        {
            assert(!connected(x, y));
            if(force)x->make_root();
            else
            {
                x->access();
                assert(!x->ch[0]);
            }
            y->access();
            set_link(y, x, 1);
            y->update();
        }

        friend void cut(node *y) // cut y from its parent
        {
            y->access();
            assert(y->ch[0]);
            y->ch[0]->p = NULL;
            y->ch[0] = NULL;
            y->update();
        }

        friend void cut(node *x, node *y) // if x, y adj in tree
        {
            x->make_root();
            y->access();
            assert(y->ch[0] == x && !x->ch[0] && !x->ch[1]);
            cut(y);
        }
    };

    node* operator[](int i)
    {
        return &data[i];
    }

    int operator[](node *i)
    {
        return i - &data[0];
    }

    vector<node> data;
    LINK_CUT_TREE(int n) : data(n) {}
};