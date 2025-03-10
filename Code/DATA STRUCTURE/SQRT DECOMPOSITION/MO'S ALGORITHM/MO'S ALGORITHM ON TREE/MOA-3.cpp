// TAB_TRIGGER "__MO_S_ALGORITHM_ON_TREE"

void MO_S_ON_TREE_ADD(int);
void MO_S_ON_TREE_REMOVE(int);
ll MO_S_ON_TREE_GET_ANSWER();

vector<ll> MO_S_ALGORITHM_ON_TREE(vector<vector<int>> &L, vector<pair<int,int>> &queries, int root = 0)
{
    int N = L.size(), Q = queries.size();
    //M = N/sqrt(Q)
    const int BLOCK_SIZE = (2*N)/((int)sqrt(Q)+1)+1;

    vector<int> euler(2*N), st(N), en(N);

    int contg = 0;

    function<void(int,int)> DFS = [&](int nodo, int padre)
    {
        euler[contg] = nodo;
        st[nodo] = contg++;
        for(auto v : L[nodo])
        {
            if(v != padre)
            {
                DFS(v, nodo);
            }
        }
        euler[contg] = nodo;
        en[nodo] = contg++;
    };

    LCA lca(L, root);
    DFS(root, -1);

    struct Query
    {
        int l, r, id, esp;
    };

    vector<Query> que(Q);

    for(int i = 0 ; i < Q ; i++)
    {
        if(st[queries[i].first] > st[queries[i].second])
        {
            swap(queries[i].first, queries[i].second);
        }
        int tlca = lca.query(queries[i].first, queries[i].second);
        if(tlca != queries[i].first)
        {
            que[i].esp = tlca;
            que[i].l = en[queries[i].first];
            que[i].r = st[queries[i].second];
            que[i].id = i;
        }
        else
        {
            que[i].esp = -1;
            que[i].l = st[queries[i].first];
            que[i].r = st[queries[i].second];
            que[i].id = i;
        }
    }

    sort(que.begin(),que.end(),[&](const Query &x, const Query &y)
    {
        if(x.l/BLOCK_SIZE != y.l/BLOCK_SIZE)return x.l < y.l;
        return (x.l/BLOCK_SIZE&1) ? (x.r < y.r) : (x.r > y.r);
    });

    int cur_l = 0;
    int cur_r = -1;

    vector<ll> res(Q);
    vector<bool> in(N);

    for(Query q : que)
    {
        while(cur_l > q.l)
        {
            cur_l--;
            int nodo = euler[cur_l];
            if(in[nodo])MO_S_ON_TREE_REMOVE(nodo);
            else MO_S_ON_TREE_ADD(nodo);
            in[nodo] = !in[nodo];
        }
        while(cur_r < q.r)
        {
            cur_r++;
            int nodo = euler[cur_r];
            if(in[nodo])MO_S_ON_TREE_REMOVE(nodo);
            else MO_S_ON_TREE_ADD(nodo);
            in[nodo] = !in[nodo];
        }
        while(cur_l < q.l)
        {
            int nodo = euler[cur_l];
            if(in[nodo])MO_S_ON_TREE_REMOVE(nodo);
            else MO_S_ON_TREE_ADD(nodo);
            in[nodo] = !in[nodo];
            cur_l++;
        }
        while(cur_r > q.r)
        {
            int nodo = euler[cur_r];
            if(in[nodo])MO_S_ON_TREE_REMOVE(nodo);
            else MO_S_ON_TREE_ADD(nodo);
            in[nodo] = !in[nodo];
            cur_r--;
        }
        if(q.esp != -1)MO_S_ON_TREE_ADD(q.esp);
        res[q.id] = MO_S_ON_TREE_GET_ANSWER();
        if(q.esp != -1)MO_S_ON_TREE_REMOVE(q.esp);
    }

    return res;
}