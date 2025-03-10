// TAB_TRIGGER "__CENTROID_DECOMPOSITION"

int CENTROID_DECOMPOSITION(vector<vector<int>> &Lcent, vector<vector<int>> &L, int root)
{
    int N = L.size();
    vector<bool> mk(N);
    vector<int> sz(N);
    Lcent.clear();
    Lcent.resize(N);
    function<void(int,int)> DFS = [&](int nodo, int padre)
    {
        sz[nodo] = 1;
        for(auto v : L[nodo])
        {
            if(v != padre && !mk[v])
            {
                DFS(v, nodo);
                sz[nodo] += sz[v];
            }
        }
    };
    function<int(int,int,int)> centroid = [&](int nodo, int padre, int tam)
    {
        for(auto v : L[nodo])
        {
            if(v != padre && !mk[v] && sz[v] > tam/2)
            {
                return centroid(v, nodo, tam);
            }
        }
        return nodo;
    };
    function<int(int)> solve = [&](int nodo)
    {
        DFS(nodo, -1);
        int cent = centroid(nodo, -1, sz[nodo]);
        mk[cent] = true;
        for(auto v : L[cent])
        {
            if(!mk[v])
            {
                Lcent[cent].push_back(solve(v));
            }
        }
        return cent;
    };
    return solve(root);
}