// TAB_TRIGGER "__GRUNDY_NUMBERS"

int MEX(const vector<int> &vect)
{
    int N = vect.size();
    vector<bool> mk(N);
    for(int i = 0 ; i < N ; i++)
    {
        if(vect[i] < N)mk[vect[i]] = true;
    }
    for(int i = 0 ; i < N ; i++)
    {
        if(!mk[i])return i;
    }
    return N;
}

vector<int> GRUNDY_NUMBERS(const vector<vector<int>> &L)
{
    int N = L.size();
    vector<int> ingree(N);
    vector<int> gn(N);
    vector<int> ts;

    for(int i = 0 ; i < N ; i++)
    {
        for(auto x : L[i])
        {
            ingree[x]++;
        }
    }

    queue<int> Q;

    for(int i = 0 ; i < N ; i++)
    {
        if(ingree[i] == 0)Q.push(i);
    }

    while(Q.size())
    {
        int nodo = Q.front();
        Q.pop();

        ts.push_back(nodo);

        for(auto v : L[nodo])
        {
            ingree[v]--;
            if(ingree[v] == 0)Q.push(v);
        }
    }

    reverse(ts.begin(), ts.end());

    for(auto nodo : ts)
    {
        vector<int> vvv;
        for(auto v : L[nodo])
        {
            vvv.push_back(gn[v]);
        }
        gn[nodo] = MEX(vvv);
    }

    return gn;
}