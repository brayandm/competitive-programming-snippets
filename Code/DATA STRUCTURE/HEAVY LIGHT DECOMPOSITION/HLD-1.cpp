// TAB_TRIGGER "__HEAVY_LIGHT_DECOMPOSITION"

struct HEAVY_LIGHT_DECOMPOSITION
{
    int N;
    vector<int> heavy, root, depth, pos, ipos, parent;
    int currentPos;
    int precal(const vector<vector<int>> &L, int nodo, int padre)
    {
        parent[nodo] = padre, heavy[nodo] = -1;
        int size = 1, maxSubtree = 0;
        for(auto v : L[nodo])
        {
            if(v != padre)
            {
                depth[v] = depth[nodo] + 1;
                int subtree = precal(L, v, nodo);
                if(subtree > maxSubtree)
                    heavy[nodo] = v, maxSubtree = subtree;
                size += subtree;
            }
        }
        return size;
    }
    void DFS(const vector<vector<int>> &L, int nodo, int padre)
    {
        pos[nodo] = ++currentPos;
        ipos[currentPos] = nodo;
        if(heavy[nodo] != -1)
        {
            root[heavy[nodo]] = root[nodo];
            DFS(L, heavy[nodo], nodo);
        }
        for(auto v : L[nodo])
        {
            if(v != padre && v != heavy[nodo])
            {
                root[v] = v;
                DFS(L, v, nodo);
            }
        }
    }
    HEAVY_LIGHT_DECOMPOSITION(const vector<vector<int>> &L, int ROOT = 0)
    {
        N = L.size();
        heavy.resize(N);
        root.resize(N);
        depth.resize(N);
        pos.resize(N);
        ipos.resize(N);
        parent.resize(N);
        depth[ROOT] = 0;
        currentPos = -1;
        root[ROOT] = ROOT;
        precal(L,ROOT,-1);
        DFS(L,ROOT,-1);
    }
    vector<pair<int,int>> get_paths(int u, int v)
    {
        vector<pair<int,int>> paths;
        for(; root[u] != root[v] ; v = parent[root[v]])
        {
            if(depth[root[u]] > depth[root[v]])swap(u, v);
            paths.push_back({pos[root[v]], pos[v]});
        }
        if(depth[u] > depth[v])swap(u, v);
        paths.push_back({pos[u], pos[v]});
        return paths;
    }
    int go_up(int u, int k)
    {
        for(; pos[u] - pos[root[u]] < k ; u = parent[root[u]])
            k -= pos[u] - pos[root[u]] + 1;
        return ipos[pos[u] - k];
    }
};