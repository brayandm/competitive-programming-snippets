// TAB_TRIGGER "__INVERT_MATRIX_MOD"

typedef long long ll;

bool INVERT_MATRIX(vector<vector<ll>> A, vector<vector<ll>> &B, const ll MOD)
{
    int N = (int)A.size();

    B.assign(N,vector<ll>(N));

    for(int i = 0 ; i < N ; i++)
    {
        B[i][i] = 1;
    }

    for(int i = 0 ; i < N ; i++)
    {
        for(int j = i ; j < N ; j++)
        {
            if(A[j][i])
            {
                if(i == j)break;
                for(int k = 0 ; k < N ; k++)
                {
                    swap(A[i][k], A[j][k]);
                    swap(B[i][k], B[j][k]);
                }
                break;
            }
        }

        if(!A[i][i])
        {
            return false;
        }

        ll a = A[i][i], b = MOD-2, c = 1;

        while(b)
        {
            if(b&1)c = c*a%MOD;
            a = a*a%MOD;
            b >>= 1;
        }

        for(int j = 0 ; j < N ; j++)
        {
            A[i][j] = A[i][j]*c%MOD;
            B[i][j] = B[i][j]*c%MOD;
        }

        for(int j = 0 ; j < N ; j++)
        {
            if(i != j && A[j][i])
            {
                ll c = A[j][i];

                for(int k = 0 ; k < N ; k++)
                {
                    A[j][k] = (A[j][k] + MOD - A[i][k]*c%MOD) % MOD;
                    B[j][k] = (B[j][k] + MOD - B[i][k]*c%MOD) % MOD;
                }
            }
        }
    }

    return true;
}