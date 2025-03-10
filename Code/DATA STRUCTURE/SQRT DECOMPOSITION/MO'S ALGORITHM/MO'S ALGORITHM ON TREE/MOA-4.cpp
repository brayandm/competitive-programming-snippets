// TAB_TRIGGER "__MO_S_ALGORITHM_ON_TREE"

void MO_S_ON_TREE_ADD(int);
void MO_S_ON_TREE_REMOVE(int);
ll MO_S_ON_TREE_GET_ANSWER();

vector<ll> MO_S_ALGORITHM_ON_TREE(vector<vector<int>> &L, vector<pair<int,int>> &queries, int root = 0)
{
    int N = L.size(), Q = queries.size();
    //M = N/sqrt(Q)
    const int SQRT_N = 500;
    int dfn_(0), block_(0), stk_(0);
    vector<int> nxt(2*N-1), to(2*N-1), hd(N), dfn(N), block_id(N), stk(N), parent_of(N);
    vector<bool> inPath(N);
    for(int u = 0, pt = 1 ; u < N ; u++)
    {
        for(auto v : L[u])
        {
            nxt[pt] = hd[u];
            to[pt] = v;
            hd[u] = pt++;
        }
    }
    struct Query
    {
        int u, v, id;
    };
    vector<Query> que(Q);
    for(int i = 0 ; i < Q ; i++)
    {
        que[i].u = queries[i].first;
        que[i].v = queries[i].second;
        que[i].id = i;
    }
    function<void(int,int)> dfs = [&](int u, int f )
    {
        dfn[u] = dfn_++;
        parent_of[u] = f;
        int saved_rbp = stk_;
        for(int v = hd[u] ; v ; v = nxt[v])
        {
            if(to[v] == f)continue;
            dfs(to[v],u);
            if(stk_-saved_rbp < SQRT_N)continue;
            for(++block_ ; stk_ != saved_rbp ; )
                block_id[stk[--stk_]] = block_;
        }
        stk[stk_++] = u;
    };
    dfs(root,-1);
    while(stk_)block_id[stk[--stk_]] = block_;
    sort(que.begin(),que.end(),[&](const Query &x, const Query &y)
    {
        return tie(block_id[x.u],dfn[x.v]) < tie(block_id[y.u],dfn[y.v]);
    });
    auto LCA_OFFLINE = [&](const vector<vector<int>> &adj, const vector<pair<int,int>> &queries, int root = 0)
    {
        int N = adj.size(), Q = queries.size();
        vector<vector<pair<int,int>>> que(N);
        vector<int> ancestor(N);
        vector<bool> mk(N);
        for(int i = 0 ; i < Q ; i++)
        {
            que[queries[i].first].push_back({queries[i].second,i});
            que[queries[i].second].push_back({queries[i].first,i});
        }
        struct DSU
        {
            vector<int> DS;
            DSU(int N)
            {
                DS.resize(N);
                fill(DS.begin(),DS.end(),-1);
            }
            int find(int x)
            {
                if(DS[x] < 0)return x;
                return DS[x] = find(DS[x]);
            }
            void join(int a, int b)
            {
                a = find(a);
                b = find(b);
                if(a == b)return;
                if(DS[a] > DS[b])swap(a,b);
                DS[a] += DS[b];
                DS[b] = a;
            }
        } dsu(N);
        vector<int> res(Q);
        function<void(int)> dfs = [&](int nodo)
        {
            mk[nodo] = true;
            ancestor[nodo] = nodo;
            for(auto v : adj[nodo])
            {
                if(!mk[v])
                {
                    dfs(v);
                    dsu.join(nodo,v);
                    ancestor[dsu.find(nodo)] = nodo;
                }
            }
            for(auto x : que[nodo])
            {
                if(mk[x.first])
                {
                    res[x.second] = ancestor[dsu.find(x.first)];
                }
            }
        };
        dfs(root);
        return res;
    };
    vector<pair<int,int>> qu;
    for(int i = 0 ; i < Q ; i++)
    {
        if(!i)qu.push_back({root,que[i].u}),qu.push_back({root,que[i].v});
        else qu.push_back({que[i-1].u,que[i].u}),qu.push_back({que[i-1].v,que[i].v});
        qu.push_back({que[i].u,que[i].v});
    }
    vector<int> lca = LCA_OFFLINE(L,qu,root);
    function<void(int)> SymmetricDifference = [&](int u)
    {
        if(inPath[u])MO_S_ON_TREE_REMOVE(u);
        else MO_S_ON_TREE_ADD(u);
        inPath[u] = inPath[u]^1;
    };
    function<void(int&,int,int)> traverse = [&](int &origin_u, int u, int g)
    {
        for( ; origin_u != g ; origin_u = parent_of[origin_u])SymmetricDifference(origin_u);
        for(int v = u ; v != origin_u ; v = parent_of[v])SymmetricDifference(v);
        origin_u = u;
    };
    int U = root, V = root;
    vector<ll> res(Q);
    for(int i = 0 ; i < Q ; i++)
    {
        traverse(U,que[i].u,lca[i*3]);
        traverse(V,que[i].v,lca[i*3+1]);
        SymmetricDifference(lca[i*3+2]);
        res[que[i].id] = MO_S_ON_TREE_GET_ANSWER();
        SymmetricDifference(lca[i*3+2]);
    }
    return res;
}