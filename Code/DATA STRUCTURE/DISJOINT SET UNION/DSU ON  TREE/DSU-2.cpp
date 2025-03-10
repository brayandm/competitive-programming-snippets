// TAB_TRIGGER "__DISJOINT_SET_UNION_ON_TREE"

void DSU_ON_TREE_ADD(int);
void DSU_ON_TREE_DELETE(int);
void DSU_ON_TREE_QUERY(int);

void DSU_ON_TREE(vector<vector<int>> &L, int root = 0)
{
    int N = L.size();
    vector<int> sz(N);
    vector<int> st(N);
    vector<int> ft(N);
    vector<int> ver(N);
    int contg = -1;
    function<void(int,int)> precal = [&](int nodo, int padre)
    {
        ver[++contg] = nodo;
        st[nodo] = contg;
        sz[nodo] = 1;
        for(auto v : L[nodo])
        {
            if(v != padre)
            {
                precal(v,nodo);
                sz[nodo] += sz[v];
            }
        }
        ft[nodo] = contg;
    };
    precal(root,-1);
    function<void(int,int,bool)> DSUT = [&](int nodo, int padre, bool keep)
    {
        int may = -1, big = -1;
        for(auto v : L[nodo])
            if(v != padre && sz[v] > may)
                may = sz[v], big = v;
     
        for(auto v : L[nodo])
            if(v != padre && v != big)
                DSUT(v,nodo,0);
     
        if(big != -1)DSUT(big,nodo,1);
     
        for(auto v : L[nodo])
            if(v != padre && v != big)
                for(int i = st[v] ; i <= ft[v] ; i++)
                    DSU_ON_TREE_ADD(ver[i]);
     
        DSU_ON_TREE_ADD(nodo);

        DSU_ON_TREE_QUERY(nodo);
     
        if(!keep)
            for(int i = st[nodo] ; i <= ft[nodo] ; i++)
                DSU_ON_TREE_DELETE(ver[i]);
    };
    DSUT(root,-1,false);   
}