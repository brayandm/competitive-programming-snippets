// TAB_TRIGGER "__LCA_EULER_ST"

struct LCA
{
    vector<int> height, euler, first, ST;
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
        int m = euler.size();
        ST.resize(m*4);
        ST_build(1,0,m-1);
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
    void ST_build(int nodo, int l, int r)
    {
        if(l == r)ST[nodo] = euler[l];
        else
        {
            int mid = (l+r)/2;
            ST_build(nodo*2,l,mid);
            ST_build(nodo*2+1,mid+1,r);
            int m1 = ST[nodo*2], m2 = ST[nodo*2+1];
            ST[nodo] = (height[m1] < height[m2]) ? m1 : m2;
        }
    }
    int ST_query(int nodo, int l, int r, int a, int b)
    {
        if(l > b || r < a)return -1;
        if(a <= l && r <= b)return ST[nodo];
        int mid = (l+r)/2;
        int left = ST_query(nodo*2,l,mid,a,b);
        int right = ST_query(nodo*2+1,mid+1,r,a,b);
        if(left == -1)return right;
        if(right == -1)return left;
        return height[left] < height[right] ? left : right;
    }
    int query(int u, int v)
    {
        int left = first[u], right = first[v];
        if(left > right)
            swap(left, right);
        return ST_query(1,0,euler.size()-1,left,right);
    }
};