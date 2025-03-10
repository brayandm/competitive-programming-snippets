// TAB_TRIGGER "__MANACHER"

template<typename T>
struct MANACHER
{
    vector<int> rad;
    vector<pair<int,int>> pal;
    MANACHER(const T &s)
    {
        int N = 2*s.size();
        rad.resize(N);
        for(int i = 0, j = 0, k ; i < N ; i += k, j = max(j-k,0ll))
        {
            for(; i >= j && i+j+1 < N && s[(i-j)/2] == s[(i+j+1)/2] ; j++);
            rad[i] = j;
            for(k = 1 ; i >= k && rad[i] >= k && rad[i-k] != rad[i]-k ; k++)
                rad[i+k] = min(rad[i-k],rad[i]-k);
        }
        for(int i = 0 ; i < N ; i++)if(rad[i])pal.push_back({(i-rad[i]+1)/2,(i+rad[i]-1)/2});
    }
    bool is_pal(int b, int e)
    {
        if(b > e)swap(b,e);
        int n = rad.size()/2;
        return b >= 0 && e < n && rad[b+e] >= e-b+1;
    }
};