// TAB_TRIGGER "__MO_S_ALGORITHM"

void MO_S_ADD(int);
void MO_S_REMOVE(int);
ll MO_S_GET_ANSWER();

vector<ll> MO_S_ALGORITHM(vector<pair<int,int>> &queries)
{
    int Q = queries.size();
    //M = N/sqrt(Q)
    const int BLOCK_SIZE = 500;
    struct Query
    {
        int l, r, id;
    };
    vector<Query> que(Q);
    for(int i = 0 ; i < Q ; i++)
    {
        que[i].l = queries[i].first;
        que[i].r = queries[i].second;
        que[i].id = i;
    }
    sort(que.begin(),que.end(),[&](const Query &x, const Query &y)
    {
        if(x.l/BLOCK_SIZE != y.l/BLOCK_SIZE)return x.l < y.l;
        return (x.l/BLOCK_SIZE&1) ? (x.r < y.r) : (x.r > y.r);
    });
    int cur_l = 0;
    int cur_r = -1;
    vector<ll> res(Q);
    for(Query q : que)
    {
        while(cur_l > q.l)
        {
            cur_l--;
            MO_S_ADD(cur_l);
        }
        while(cur_r < q.r)
        {
            cur_r++;
            MO_S_ADD(cur_r);
        }
        while(cur_l < q.l)
        {
            MO_S_REMOVE(cur_l);
            cur_l++;
        }
        while(cur_r > q.r)
        {
            MO_S_REMOVE(cur_r);
            cur_r--;
        }
        res[q.id] = MO_S_GET_ANSWER();
    }
    return res;
}