// TAB_TRIGGER "__DSU_WITH_ROLLBACKS"

struct DSU_WITH_ROLLBACKS
{
    struct dsu_save
    {
        int u, urank, v, vrank, comps;
        bool bipart, bipart_comp;
    };

    stack<dsu_save> op;

    vector<int> rnk;
    vector<bool> col;
    vector<bool> bip;
    bool bipartite;
    int comps;

    DSU_WITH_ROLLBACKS()
    {

    }

    DSU_WITH_ROLLBACKS(int N)
    {
        init(N);
    }

    void init(int N)
    {
        rnk.clear();
        col.clear();
        bip.clear();
        while(!op.empty())op.pop();
        rnk.resize(N);
        col.resize(N);
        bip.resize(N);
        for(int i = 0 ; i < N ; i++)
        {
            rnk[i] = 1;
            col[i] = false;
            bip[i] = true;
        }
        bipartite = true;
        comps = N;
    }

    pair<int,bool> find(int x)
    {
        if(rnk[x] > 0)return {x, col[x]};
        pair<int,bool> tp = find(-rnk[x]);
        tp.second ^= col[x];
        return tp;
    }

    void join(int a, int b)
    {
        pair<int,bool> ta = find(a), tb = find(b);
        a = ta.first;
        b = tb.first;
        if(a == b)
        {
            op.push({a, rnk[a], b, rnk[b], comps, bipartite, bip[a]});
            if(ta.second == tb.second)bipartite = false, bip[a] = false;
            return;
        }
        if(rnk[a] < rnk[b])swap(a,b);
        op.push({a, rnk[a], b, rnk[b], comps, bipartite, bip[a]});
        comps--;
        rnk[a] += rnk[b];
        rnk[b] = -a;
        col[b] = col[b]^(ta.second == tb.second);
        bip[a] = bip[a]&bip[b];
    }

    void rollback()
    {
        if(op.empty())return;
        dsu_save x = op.top();
        op.pop();
        comps = x.comps;
        bipartite = x.bipart;
        rnk[x.u] = x.urank;
        col[x.u] = false;
        bip[x.u] = x.bipart_comp;
        rnk[x.v] = x.vrank;
        col[x.v] = false;
    }
};