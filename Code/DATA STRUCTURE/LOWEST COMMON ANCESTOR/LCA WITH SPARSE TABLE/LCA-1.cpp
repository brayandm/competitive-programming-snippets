// TAB_TRIGGER "__LCA_RMQ"

struct LCA
{
    int LOG = 0;
    vector<vector<int>> T;
    vector<int> height;
    vector<bool> visited;
    int n;
    LCA(const vector<vector<int>> &adj, int root = 0)
    {
        n = adj.size();
        int temp = n-1;
        while(temp)temp /= 2, LOG++;
        height.resize(n);
        visited.assign(n,false);
        T.resize(n);
        for(int i = 0 ; i < T.size() ; i++)T[i].resize(LOG+1);
        T[root][0] = -1;
        DFS(adj,root);
        precal();
    }
    void DFS(const vector<vector<int>> &adj, int nodo)
    {
        visited[nodo] = true;
        for(auto v : adj[nodo])
        {
            if(!visited[v])
            {
                T[v][0] = nodo;
                height[v] = height[nodo]+1;
                DFS(adj,v);
            }
        }
    }
    void precal()
    {
        for(int j = 1 ; j <= LOG ; j++)
            for(int i = 0 ; i < n ; i++)
                if(T[i][j-1] != -1)T[i][j] = T[T[i][j-1]][j-1];
                else T[i][j] = -1;
    }
    int query(int u, int v)
    {
        if(height[u] < height[v])swap(u,v);
        for(int i = LOG ; i >= 0 ; i--)
            if(height[u]-(1<<i) >= height[v])
                u = T[u][i];
        if(u == v)return u;
        for(int i = LOG ; i >= 0 ; i--)
            if(T[u][i] != T[v][i])
                u = T[u][i], v = T[v][i];
        return T[u][0];
    }
};