// TAB_TRIGGER "__GAME_GRAPH"

vector<int> GAME_GRAPH(const vector<vector<int>> &L)
{
    int N = L.size();
    vector<vector<int>> iL(N);
    vector<int> outgree(N);
    vector<int> state(N);

    for(int i = 0 ; i < N ; i++)
    {
        for(auto x : L[i])
        {
            iL[x].push_back(i);
        }
        outgree[i] = L[i].size();
    }

    queue<int> Q;

    for(int i = 0 ; i < N ; i++)
    {
        if(outgree[i] == 0)Q.push(i);
    }

    while(Q.size())
    {
        int nodo = Q.front();
        Q.pop();

        if(state[nodo] == 0)state[nodo] = 2;

        for(auto v : iL[nodo])
        {
            if(state[v])continue;
            if(state[nodo] == 2)
            {
                state[v] = 1;
                Q.push(v);
            }
            else if(state[nodo] == 1)
            {
                outgree[v]--;
                if(outgree[v] == 0)Q.push(v);
            }
        }
    }

    return state;
}