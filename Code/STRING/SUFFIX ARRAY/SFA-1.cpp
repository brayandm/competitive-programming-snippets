// TAB_TRIGGER "__SUFFIX_ARRAY"

template<typename T>
struct SUFFIX_ARRAY
{
    int n;
    vector<int> sa, rank, lcp;
    SUFFIX_ARRAY(T s):n(s.size() + 1),sa(n),rank(n),lcp(n)
    {
        if(is_same<T, string>::value);
        else if(is_same<T, vector<int>>::value)s.push_back(numeric_limits<int>::min());
        else if(is_same<T, vector<long long>>::value)s.push_back(numeric_limits<long long>::min());
        else assert(0);
        vector<int> _sa(n), bucket(n);
        iota(sa.rbegin(),sa.rend(),0);
        sort(next(sa.begin()),sa.end(),[&](int i, int j)
        {
            return s[i] < s[j];
        });
        for(int i = 1, j = 0 ; i < n ; ++i)
        {
            rank[sa[i]] = rank[sa[i-1]] + (i == 1 || s[sa[i-1]] < s[sa[i]]);
            if(rank[sa[i]] != rank[sa[i-1]])bucket[++j] = i;
        }
        for(int len = 1 ; len <= n ; len += len)
        {
            for(int i = 0, j ; i < n ; ++i)
            {
                if((j = sa[i] - len) < 0) j += n;
                _sa[bucket[rank[j]]++] = j;
            }
            sa[_sa[bucket[0] = 0]] = 0;
            for(int i = 1, j = 0 ; i < n ; ++i)
            {
                if(rank[_sa[i]] != rank[_sa[i-1]] || rank[_sa[i]+len] != rank[_sa[i-1] + len])bucket[++j] = i;
                sa[_sa[i]] = j;
            }
            copy(sa.begin(),sa.end(),rank.begin());
            sa.swap(_sa);
            if(rank[sa[n-1]] == n-1) break;
        }
        for(int i = 0, j = rank[lcp[0] = 0], k = 0 ; i < n-1 ; ++i, ++k)
            while(k >= 0 && s[i] != s[sa[j-1]+k])
                lcp[j] = k--, j = rank[sa[j]+1];
    }
};