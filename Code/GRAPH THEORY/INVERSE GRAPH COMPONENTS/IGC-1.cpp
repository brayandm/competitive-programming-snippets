// TAB_TRIGGER "__INVERSE_GRAPH_COMPONENTS"

vector<vector<int>> INVERSE_GRAPH_COMPONENTS(vector<vector<int>> &L)
{
    int N = L.size();

    vector<vector<int>> ady(N), comps;

    vector<bool> in(N);

    list<int> ls;

    for(int i = 0 ; i < N ; i++)
    {
        ls.push_back(i);
    }

    while(!ls.empty())
    {
        queue<int> Q;
        vector<int> cmp;

        Q.push(*ls.begin());
        cmp.push_back(*ls.begin());
        ls.erase(ls.begin());

        while(!Q.empty())
        {
            int nodo = Q.front();
            Q.pop();

            for(auto v : L[nodo])
            {
                in[v] = true;
            }

            vector<list<int>::iterator> temp;

            for(auto it = ls.begin() ; it != ls.end() ; it++)
            {
                if(!in[*it])
                {
                    temp.push_back(it);
                }
            }

            for(auto x : temp)
            {
                ady[nodo].push_back(*x);
                ady[*x].push_back(nodo);
                Q.push(*x);
                cmp.push_back(*x);
                ls.erase(x);
            }

            for(auto v : L[nodo])
            {
                in[v] = false;
            }
        }

        comps.push_back(cmp);
    }

    return comps;
}