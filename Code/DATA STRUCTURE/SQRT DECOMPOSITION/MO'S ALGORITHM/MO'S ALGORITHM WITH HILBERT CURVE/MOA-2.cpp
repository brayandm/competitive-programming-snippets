// TAB_TRIGGER "__MO_S_ALGORITHM"

void MO_S_ADD(int);
void MO_S_REMOVE(int);
ll MO_S_GET_ANSWER();

inline int64_t HILBERT_ORDER(int x, int y, int pow, int rotate)
{
    if(pow == 0)return 0;
    int hpow = 1 << (pow-1);
    int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
    seg = (seg + rotate) & 3;
    const int rotateDelta[4] = {3, 0, 0, 1};
    int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    int nrot = (rotate + rotateDelta[seg]) & 3;
    int64_t subSquareSize = int64_t(1) << (2*pow - 2);
    int64_t ans = seg * subSquareSize;
    int64_t add = HILBERT_ORDER(nx, ny, pow-1, nrot);
    ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
    return ans;
}

vector<ll> MO_S_ALGORITHM(vector<pair<int,int>> &queries)
{
    int N = 0;
    for(int i = 0 ; i < queries.size() ; i++)
    {
        N = max(N, queries[i].second);
    }
    int Q = queries.size();
    struct Query
    {
        int id, ord;
    };
    vector<Query> que(Q);
    for(int i = 0 ; i < Q ; i++)
    {
        que[i].id = i;
        que[i].ord = HILBERT_ORDER(queries[i].first,queries[i].second,__lg(N)+1,0);
    }
    sort(que.begin(),que.end(),[&](const Query &x, const Query &y)
    {
        return x.ord < y.ord;
    });
    int cur_l = 0;
    int cur_r = -1;
    vector<ll> res(Q);
    for(int i = 0 ; i < Q ; i++)
    {
        int l = queries[que[i].id].first;
        int r = queries[que[i].id].second;
        while(cur_l > l)
        {
            cur_l--;
            MO_S_ADD(cur_l);
        }
        while(cur_r < r)
        {
            cur_r++;
            MO_S_ADD(cur_r);
        }
        while(cur_l < l)
        {
            MO_S_REMOVE(cur_l);
            cur_l++;
        }
        while(cur_r > r)
        {
            MO_S_REMOVE(cur_r);
            cur_r--;
        }
        res[que[i].id] = MO_S_GET_ANSWER();
    }
    return res;
}