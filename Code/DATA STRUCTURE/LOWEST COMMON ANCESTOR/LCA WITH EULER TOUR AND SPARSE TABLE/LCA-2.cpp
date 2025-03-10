// TAB_TRIGGER "__LCA_EULER_RMQ"

struct LCA
{
    vector<vector<int>> T;
    vector<int> height, euler, first;
    vector<bool> visited;
    int n;
    LCA(const vector<vector<int>> &adj, int root = 0)
    {
        n = adj.size();
        height.resize(n);
        first.resize(n);
        euler.reserve(n*2);
        visited.assign(n,false);
        DFS(adj,root);
        RMQ(euler);
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
    void RMQ(const vector<int> &arr)
    {
        T.resize(arr.size());
        for(int i = 0 ; i < T.size() ; i++)T[i].resize(31-__builtin_clz(arr.size())+1), T[i][0] = arr[i];
        for(int j = 1 ; j <= 31-__builtin_clz(arr.size()) ; j++)
            for(int i = 0 ; i+(1<<j)-1 < T.size() ; i++)
                T[i][j] = (height[T[i][j-1]] < height[T[i+(1<<(j-1))][j-1]]) ? T[i][j-1] : T[i+(1<<(j-1))][j-1];
    }
    int query(int u, int v)
    {
        int left = first[u], right = first[v];
        if(left > right)
            swap(left, right);
        int k = 31-__builtin_clz(right-left+1);
        return (height[T[left][k]] < height[T[right-(1<<k)+1][k]]) ? T[left][k] : T[right-(1<<k)+1][k];
    }
};