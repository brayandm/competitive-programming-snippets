// TAB_TRIGGER "__SPARSE_TABLE_RMQ"

template<typename T, class F = less<T>>
struct RMQ
{
    vector<vector<T>> A;
    RMQ(const vector<T> &arr)
    {
        A.resize(arr.size());
        for(int i = 0 ; i < A.size() ; i++)A[i].resize(31-__builtin_clz(arr.size())+1), A[i][0] = arr[i];
        for(int j = 1 ; j <= 31-__builtin_clz(arr.size()) ; j++)
            for(int i = 0 ; i+(1<<j)-1 < A.size() ; i++)
                if(F()(A[i][j-1],A[i+(1<<(j-1))][j-1]))A[i][j] = A[i][j-1];
                else A[i][j] = A[i+(1<<(j-1))][j-1];
    }
    T query(int a, int b)
    {
        if(a > b)swap(a,b);
        int k = 31-__builtin_clz(b-a+1);
        if(F()(A[a][k],A[b-(1<<k)+1][k]))return A[a][k];
        else return A[b-(1<<k)+1][k];
    }
};