// TAB_TRIGGER "__DISJOINT_SET_UNION"

struct DSU
{
    vector<int> DS;
    DSU(int N)
    {
        DS.resize(N);
        fill(DS.begin(),DS.end(),-1);
    }
    int find(int x)
    {
        if(DS[x] < 0)return x;
        return DS[x] = find(DS[x]);
    }
    void join(int a, int b)
    {
        a = find(a);
        b = find(b);
        if(a == b)return;
        if(DS[a] > DS[b])swap(a,b);
        DS[a] += DS[b];
        DS[b] = a;
    }
};