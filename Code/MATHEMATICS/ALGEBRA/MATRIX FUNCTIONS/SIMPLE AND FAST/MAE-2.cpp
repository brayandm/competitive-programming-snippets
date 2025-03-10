// TAB_TRIGGER "__MATRIX_EXPONENTATION"

const ll MOD2 = MOD*MOD;

typedef vector<vector<ll>> matrix;

matrix identity(int N)
{
    matrix A(N,vector<ll>(N));
    for(int i = 0 ; i < N ; i++)A[i][i] = 1;
    return A;
}

void print(matrix A)
{
    cerr << '\n';
    for(int i = 0 ; i < A.size() ; i++)
    {
        cerr << "[";
        for(int j = 0 ; j < A[i].size() ; j++)
        {
            if(j)cerr << ", ";
            cerr << A[i][j];
        }
        cerr << "]" << '\n';
    }
    cerr << '\n';
}

matrix mult(const matrix &A, const matrix &B)
{
    matrix C(A.size(),vector<ll>(B[0].size()));
    for(int i = 0 ; i < C.size() ; i++)
    {
        for(int j = 0 ; j < C[i].size() ; j++)
        {
            for(int k = 0 ; k < A[i].size() ; k++)
            {
                C[i][j] += A[i][k]*B[k][j];
                if(C[i][j] >= MOD2)C[i][j] -= MOD2;
            }
        }
    }
    for(int i = 0 ; i < C.size() ; i++)
    {
        for(int j = 0 ; j < C[0].size() ; j++)
        {
            C[i][j] %= MOD;
        }
    }
    return C;
}

matrix qpow(matrix A, ll e)
{
    matrix res = identity(A.size());
    while(e)
    {
        if(e&1)res = mult(res,A);
        A = mult(A,A);
        e /= 2;
    }
    return res;
}