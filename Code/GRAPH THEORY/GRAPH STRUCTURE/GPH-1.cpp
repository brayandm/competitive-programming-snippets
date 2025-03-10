// TAB_TRIGGER "__GRAPH_STRUCTURE"

struct GRAPH
{
    vector<vector<int>> L;

    GRAPH(int N)
    {
        L.resize(N);
    }

    void add_edge(int a, int b)
    {
        assert(0 <= a && a < L.size() && 0 <= b && b < L.size());
        L[a].push_back(b);
        L[b].push_back(a);
    }

    vector<bool> bipartiteness()
    {
        int N = L.size();
        vector<bool> mk(N), col(N);
        bool flag = true;

        function<void(int)> DFS = [&](int nodo)
        {
            mk[nodo] = true;
            for(auto v : L[nodo])
            {
                if(!mk[v])
                {
                    col[v] = !col[nodo];
                    DFS(v);
                }
                else if(col[v] == col[nodo])
                {
                    flag = false;
                }
            }
        };

        for(int i = 0 ; i < N ; i++)
        {
            if(!mk[i])
            {
                DFS(i);
            }
        }

        if(!flag)
        {
            col.clear();
        }

        return col;
    }

    vector<int> cyclicality()
    {
        int N = L.size();
        vector<bool> mk(N), in(N);
        vector<int> temp, cyc;

        function<void(int,int)> DFS = [&](int nodo, int padre)
        {
            temp.push_back(nodo);
            mk[nodo] = true;
            in[nodo] = true;
            for(auto v : L[nodo])
            {
                if(!mk[v])
                {
                    DFS(v,nodo);
                    if(cyc.size())return;
                }
                else if(in[v] && v != padre)
                {
                    do
                    {
                        cyc.push_back(temp.back());
                        temp.pop_back();
                    }
                    while(cyc.back() != v);
                    return;
                }

            }
            temp.pop_back();
            in[nodo] = false;
        };

        for(int i = 0 ; i < N ; i++)
        {
            if(!mk[i])
            {
                DFS(i,-1);
                if(cyc.size())return cyc;
            }
        }

        return cyc;
    }

    vector<int> connectivity()
    {
        int N = L.size();
        vector<bool> mk(N);
        vector<int> comp(N);
        int contg = 0;

        function<void(int)> DFS = [&](int nodo)
        {
            mk[nodo] = true;
            comp[nodo] = contg;
            for(auto v : L[nodo])
            {
                if(!mk[v])
                {
                    DFS(v);
                }
            }
        };

        for(int i = 0 ; i < N ; i++)
        {
            if(!mk[i])
            {
                DFS(i);
                contg++;
            }
        }

        return comp;
    }

    vector<int>& operator[](int nodo)
    {
        return L[nodo];
    }
};