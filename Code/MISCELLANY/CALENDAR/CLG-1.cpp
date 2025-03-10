// TAB_TRIGGER "__CALENDAR"

struct CALENDAR_GRAPH
{
    typedef long long ll;

    vector<vector<pair<int,ll>>> L;
    vector<vector<ll>> arr1;
    vector<vector<ll>> arr2;
    vector<bool> mk;
    vector<ll> dp;
    int root;
    int N;

    void DFS(int nodo)
    {
        mk[nodo] = true;
        ll sum = 0;
        for(auto v : L[nodo])
        {
            if(!mk[v.first])DFS(v.first);
            if(arr1[nodo].size())arr1[nodo].push_back(arr1[nodo].back()+dp[v.first]*v.second);
            else arr1[nodo].push_back(dp[v.first]*v.second);
            if(arr2[nodo].size())arr2[nodo].push_back(arr2[nodo].back()+v.second);
            else arr2[nodo].push_back(v.second);
            sum += v.second*dp[v.first];
        }
        if(!L[nodo].size())dp[nodo] = 1;
        else dp[nodo] = sum;
    }

    void init(vector<vector<pair<int,ll>>> &tL, int troot = 0)
    {
        N = tL.size();
        L = tL;
        arr1.clear();
        arr2.clear();
        mk.clear();
        dp.clear();
        arr1.resize(N);
        arr2.resize(N);
        mk.resize(N);
        dp.resize(N);
        root = troot;
        DFS(root);
    }

    CALENDAR_GRAPH()
    {

    }

    CALENDAR_GRAPH(vector<vector<pair<int,ll>>> &tL, int troot = 0)
    {
        init(tL,troot);
    }

    ll get_num(vector<ll> vect)
    {
        int nodo = root;
        ll sum = 0;
        for(auto x : vect)
        {
            assert(0 <= x && x < arr2[nodo].back());
            int pos = upper_bound(arr2[nodo].begin(), arr2[nodo].end(), x) - arr2[nodo].begin();
            sum += arr1[nodo][pos]-(arr2[nodo][pos]-x)*dp[L[nodo][pos].first];
            nodo = L[nodo][pos].first;
        }
        return sum;
    }

    vector<ll> get_path(ll num)
    {
        assert(0 <= num && num < arr1[root].back());
        vector<ll> path;
        int nodo = root;
        while(arr1[nodo].size())
        {
            int pos = upper_bound(arr1[nodo].begin(), arr1[nodo].end(), num) - arr1[nodo].begin();
            ll cont = 0;
            if(pos)
            {
                cont = arr2[nodo][pos-1];
                num -= arr1[nodo][pos-1];
            }
            cont += num/dp[L[nodo][pos].first];
            num %= dp[L[nodo][pos].first];
            nodo = L[nodo][pos].first;
            path.push_back(cont);
        }
        return path;
    }
};

struct GREGORIAN_CALENDAR
{
    typedef long long ll;

    vector<string> _smonths = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    vector<string> _sdays = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    CALENDAR_GRAPH CL;

    GREGORIAN_CALENDAR()
    {
        vector<vector<pair<int,ll>>> L(13);
        L[0].push_back({1,25});
        L[1].push_back({2,3});
        L[1].push_back({3,1});
        L[2].push_back({4,24});
        L[2].push_back({5,1});
        L[3].push_back({4,25});
        L[4].push_back({6,3});
        L[4].push_back({7,1});
        L[5].push_back({6,4});
        L[6].push_back({11,1});
        L[6].push_back({8,1});
        L[6].push_back({11,1});
        L[6].push_back({10,1});
        L[6].push_back({11,1});
        L[6].push_back({10,1});
        L[6].push_back({11,1});
        L[6].push_back({11,1});
        L[6].push_back({10,1});
        L[6].push_back({11,1});
        L[6].push_back({10,1});
        L[6].push_back({11,1});
        L[7].push_back({11,1});
        L[7].push_back({9,1});
        L[7].push_back({11,1});
        L[7].push_back({10,1});
        L[7].push_back({11,1});
        L[7].push_back({10,1});
        L[7].push_back({11,1});
        L[7].push_back({11,1});
        L[7].push_back({10,1});
        L[7].push_back({11,1});
        L[7].push_back({10,1});
        L[7].push_back({11,1});
        L[8].push_back({12,28});
        L[9].push_back({12,29});
        L[10].push_back({12,30});
        L[11].push_back({12,31});
        CL.init(L,0);
    }

    ll date_to_days(ll year, ll month, ll day)
    {
        year--, month--, day--;
        ll y400 = year/400;
        year %= 400;
        ll y100 = year/100;
        year %= 100;
        ll y4 = year/4;
        year %= 4;
        vector<ll> vect = {y400, y100, y4, year, month, day};
        return CL.get_num(vect);
    }

    vector<ll> days_to_date(ll num)
    {
        vector<ll> vvv = CL.get_path(num);
        vector<ll> date;
        date.push_back(vvv[0]*400+vvv[1]*100+vvv[2]*4+vvv[3]+1);
        date.push_back(vvv[4]+1);
        date.push_back(vvv[5]+1);
        return date;
    }

    string day_of_the_week(ll year, ll month, ll day)
    {
        ll num = date_to_days(year, month, day);
        return _sdays[num%7];
    }

    vector<ll> next_day(ll year, ll month, ll day)
    {
        ll num = date_to_days(year, month, day);
        return days_to_date(num+1);
    }
};