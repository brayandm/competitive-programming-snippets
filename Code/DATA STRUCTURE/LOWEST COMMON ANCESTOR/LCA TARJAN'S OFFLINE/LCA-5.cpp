// TAB_TRIGGER "__LCA_TARJAN_S_OFFLINE"

vector<int> LCA_OFFLINE(const vector<vector<int>> &adj, const vector<pair<int,int>> &queries, int root = 0)
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
}