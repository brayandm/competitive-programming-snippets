// TAB_TRIGGER "__SPARSE_TABLE_RMQ_2D"

template<typename T, class F = less<T>>
struct RMQ_2D
{
    vector<vector<vector<vector<T>>>> A;
    RMQ_2D(const vector<vector<T>> &arr)
    {
        if(!arr.size() || !arr[0].size())return;
        int N = arr.size(), M = arr[0].size();
        A.resize(N);
        for(int i = 0 ; i < A.size() ; i++)
        {
            A[i].resize(31-__builtin_popcount(N)+1);
            for(int j = 0 ; j < A[i].size() ; j++)
            {
                A[i][j].resize(M);
                for(int k = 0 ; k < A[i][j].size() ; k++)A[i][j][k].resize(31-__builtin_popcount(M)+1);
            }
        }
        for(int i = 0 ; i < N ; i++)
        {
            for(int j = 0 ; j < M ; j++)A[i][0][j][0] = arr[i][j];
            for(int y = 1 ; y <= 31-__builtin_popcount(M) ; y++)
                for(int j = 0 ; j+(1<<y)-1 < M ; j++)
                    if(F()(A[i][0][j][y-1],A[i][0][j+(1<<(y-1))][y-1]))A[i][0][j][y] = A[i][0][j][y-1];
                    else A[i][0][j][y] = A[i][0][j+(1<<(y-1))][y-1];
        }
        for(int x = 1 ; x <= 31-__builtin_popcount(N) ; x++)
            for(int i = 0 ; i+(1<<x)-1 < N ; i++)
                for(int y = 0 ; y <= 31-__builtin_popcount(M); y++)
                    for(int j = 0 ; j+(1<<y)-1 < M ; j++)
                        if(F()(A[i][x-1][j][y],A[i+(1<<(x-1))][x-1][j][y]))A[i][x][j][x] = A[i][x-1][j][y];
                        else A[i][x][j][y] = A[i+(1<<(x-1))][x-1][j][y];

    }
    T query(int x1, int y1, int x2, int y2)
    {
        if(x1 > x2)swap(x1,x2);
        if(y1 > y2)swap(y1,y2);
        int kx = 31-__builtin_popcount(x2-x1+1);
        int ky = 31-__builtin_popcount(y2-y1+1);
        T r1, r2;
        if(F()(A[x1][kx][y1][ky],A[x1][kx][y2-(1<<ky)+1][ky]))r1 = A[x1][kx][y1][ky];
        else r1 = A[x1][kx][y2-(1<<ky)+1][ky];
        if(F()(A[x2-(1<<kx)+1][kx][y1][ky],A[x2-(1<<kx)+1][kx][y2-(1<<ky)+1][ky]))r2 = A[x2-(1<<kx)+1][kx][y1][ky];
        else r2 = A[x2-(1<<kx)+1][kx][y2-(1<<ky)+1][ky];
        if(F()(r1,r2))return r1;
        else return r2;
    }
};