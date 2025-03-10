// TAB_TRIGGER "__EULER_TOUR"

int CHECK_EULER_TOUR(int N, vector<pair<int,int>> &edge, bool undigraph, int troot = -1)
{
    assert(troot == -1 || (troot >= 0 && troot < N));

    vector<vector<int>> L(N);

    for(int i = 0 ; i < edge.size() ; i++)
    {
        assert(edge[i].first >= 0 && edge[i].first < N);
        assert(edge[i].second >= 0 && edge[i].second < N);

        if(undigraph)
        {
            L[edge[i].first].push_back(edge[i].second);
            L[edge[i].second].push_back(edge[i].first);
        }
        else
        {
            L[edge[i].first].push_back(edge[i].second);
        }
    }

    vector<int> ingree(N);
    vector<int> outgree(N);
    vector<bool> mark(N);

    int total_edge = 0;

    for(int i = 0 ; i < N ; i++)
    {
        total_edge += L[i].size();
        for(auto v : L[i])
        {
            outgree[i]++;
            ingree[v]++;
        }
    }

    int init = -1;
    vector<pair<int,int>> odd;

    for(int i = 0 ; i < N ; i++)
    {
        if(init == -1 && outgree[i])init = i;

        if(undigraph)
        {
            if(outgree[i]&1)odd.push_back({i,0});
        }
        else
        {
            if(outgree[i] != ingree[i])odd.push_back({i,outgree[i]-ingree[i]});
        }
    }

    int root = -1;

    if(odd.size())
    {
        if(undigraph)
        {
            if(odd.size() != 2)return -1;

            if(odd[0].first > odd[1].first)swap(odd[0],odd[1]);

            if(troot != -1)
            {
                if(troot == odd[0].first)root = troot;
                else if(troot == odd[1].first)root = troot;
                else return -1;
            }
            else root = odd[0].first;
        }
        else
        {
            if(odd.size() != 2)return -1;
            if(odd[0].second < odd[1].second)swap(odd[0],odd[1]);
            if(odd[0].second == 1 && odd[1].second == -1)
            {
                if(troot != -1)
                {
                    if(troot == odd[0].first)root = troot;
                    else return -1;
                }
                else root = odd[0].first;
            }
            else return -1;
        }
    }
    else
    {
        if(troot != -1)root = troot;
        else root = init;
    }

    queue<int> Q;
    mark[root] = true;
    Q.push(root);

    int temp_edge = 0;

    while(!Q.empty())
    {
        int nodo = Q.front();
        Q.pop();

        temp_edge += L[nodo].size();

        for(auto v : L[nodo])
        {
            if(!mark[v])
            {
                mark[v] = true;
                Q.push(v);
            }
        }
    }

    if(total_edge != temp_edge)return -1;
    return root;
}

vector<int> EULER_TOUR(int N, vector<pair<int,int>> &edge, bool undigraph, int troot = -1)
{
    vector<int> res;
    int root = CHECK_EULER_TOUR(N,edge,undigraph,troot);

    if(root == -1)
    {
        return res;
    }

    vector<vector<int>> L(N);
    vector<vector<int>> id(N);
    vector<vector<int>> inv(N);

    for(int i = 0 ; i < edge.size() ; i++)
    {
        if(undigraph)
        {
            L[edge[i].first].push_back(edge[i].second);
            L[edge[i].second].push_back(edge[i].first);

            id[edge[i].first].push_back(i);
            id[edge[i].second].push_back(i+edge.size());

            if(edge[i].first == edge[i].second)
            {
                int sz = inv[edge[i].first].size();

                inv[edge[i].first].push_back(sz+1);
                inv[edge[i].second].push_back(sz);
            }
            else
            {
                int sz2 = inv[edge[i].second].size();
                int sz1 = inv[edge[i].first].size();

                inv[edge[i].first].push_back(sz2);
                inv[edge[i].second].push_back(sz1);
            }
        }
        else
        {
            L[edge[i].first].push_back(edge[i].second);

            id[edge[i].first].push_back(i);
        }
    }

    vector<vector<bool>> mark(N);
    vector<int> ptr(N);

    for(int i = 0 ; i < N ; i++)
    {
        mark[i].resize(L[i].size());
    }

    stack<pair<int,int>> S;
    S.push({root,-1});

    while(!S.empty())
    {
        int nodo = S.top().first;

        while(ptr[nodo] < L[nodo].size() && mark[nodo][ptr[nodo]])
        {
            ptr[nodo]++;
        }

        if(ptr[nodo] == L[nodo].size())
        {
            res.push_back(S.top().second);
            S.pop();
        }
        else
        {
            mark[nodo][ptr[nodo]] = true;
            if(undigraph)mark[L[nodo][ptr[nodo]]][inv[nodo][ptr[nodo]]] = true;
            S.push({L[nodo][ptr[nodo]],id[nodo][ptr[nodo]]});
        }
    }

    reverse(res.begin(),res.end());

    return res;
}