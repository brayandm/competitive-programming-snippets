// TAB_TRIGGER "__LCA_EULER_RMQ_FAST"

struct LCA
{
    vector<int> height, euler, first;
    vector<bool> visited;
    int n;

    int sz_rmq;
    static const int bits = 30;
    vector<int> mask, rmq;

    int op(int x, int y)
    {
        return height[euler[x]] < height[euler[y]] ? x : y;
    }
    int msb(int x)
    {
        return __builtin_clz(1)-__builtin_clz(x);
    }
    int small(int r, int sz = bits)
    {
        return r-msb(mask[r]&((1<<sz)-1));
    }
    void RMQ()
    {
        sz_rmq = euler.size(), mask.resize(sz_rmq), rmq.resize(sz_rmq);
        for(int i = 0, at = 0 ; i < sz_rmq ; mask[i++] = at |= 1)
        {
            at = (at<<1)&((1<<bits)-1);
            while(at and op(i, i-msb(at&-at)) == i)at ^= at&-at;
        }
        for(int i = 0 ; i < sz_rmq/bits ; i++)rmq[i] = small(bits*i+bits-1);
        for(int j = 1 ; (1<<j) <= sz_rmq/bits ; j++)for(int i = 0 ; i+(1<<j) <= sz_rmq/bits ; i++)
                rmq[sz_rmq/bits*j+i] = op(rmq[sz_rmq/bits*(j-1)+i], rmq[sz_rmq/bits*(j-1)+i+(1<<(j-1))]);
    }
    int query(int l, int r)
    {
        l = first[l], r = first[r];
        if(l > r)swap(l, r);
        if(r-l+1 <= bits)return euler[small(r, r-l+1)];
        int ans = op(small(l+bits-1), small(r));
        int x = l/bits+1, y = r/bits-1;
        if(x <= y)
        {
            int j = msb(y-x+1);
            ans = op(ans, op(rmq[sz_rmq/bits*j+x], rmq[sz_rmq/bits*j+y-(1<<j)+1]));
        }
        return euler[ans];
    }
    LCA(const vector<vector<int>> &adj, int root = 0)
    {
        n = adj.size();
        height.resize(n);
        first.resize(n);
        euler.reserve(n*2);
        visited.assign(n,false);
        DFS(adj,root);
        RMQ();
    }
    void DFS(const vector<vector<int>> &adj, int nodo)
    {
        visited[nodo] = true;
        first[nodo] = euler.size();
        euler.push_back(nodo);
        for(auto v : adj[nodo])
        {
            if(!visited[v])
            {
                height[v] = height[nodo]+1;
                DFS(adj,v);
                euler.push_back(nodo);
            }
        }
    }
};