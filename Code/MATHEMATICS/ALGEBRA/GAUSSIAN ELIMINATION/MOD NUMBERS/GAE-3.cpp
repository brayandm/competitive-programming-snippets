// TAB_TRIGGER "__GAUSSIAN_ELIMINATION_MOD"

typedef long long ll;

int GAUSSIAN_ELIMINATION(vector<vector<ll>> A, vector<ll> &ans, const ll MOD)
{
    const int INF = 2;

    int N = (int)A.size();
    int M = (int)A[0].size()-1;

    vector<int> where(M, -1);

    for(int col = 0, row = 0 ; col < M && row < N ; col++)
    {
        for(int i = row ; i < N ; i++)
        {
            if(A[i][col])
            {
                if(i == row)break;
                for(int j = col ; j <= M ; j++)
                {
                    swap(A[i][j], A[row][j]);
                }
                break;
            }
        }

        if(!A[row][col])
        {
            continue;
        }

        where[col] = row;

        ll a = A[row][col], b = MOD-2, c = 1;

        while(b)
        {
            if(b&1)c = c*a%MOD;
            a = a*a%MOD;
            b >>= 1;
        }

        for(int i = col ; i <= M ; i++)
        {
            A[row][i] = A[row][i]*c%MOD;
        }

        for(int i = row+1 ; i < N ; i++)
        {
            if(A[i][col])
            {
                ll c = A[i][col];

                for(int j = col ; j <= M ; j++)
                {
                    A[i][j] = (A[i][j] + MOD - A[row][j]*c%MOD) % MOD;
                }
            }
        }

        row++;
    }

    ans.assign(M, 0);

    vector<ll> vect(N);

    for(int i = 0 ; i < N ; i++)
    {
        vect[i] = A[i][M];
    }

    for(int j = M-1 ; j >= 0 ; j--)
    {
        if(where[j] != -1)
        {
            ans[j] = vect[where[j]];
        }

        for(int i = 0 ; i < N ; i++)
        {
            vect[i] = (vect[i] + MOD - ans[j]*A[i][j]%MOD) % MOD;
        }
    }

    for(int i = 0 ; i < N ; i++)
    {
        ll sum = 0;

        for(int j = 0 ; j < M ; j++)
        {
            sum = (sum + ans[j]*A[i][j]) % MOD;
        }

        if(sum != A[i][M])
        {
            return 0;
        }
    }

    for(int i = 0 ; i < M ; i++)
    {
        if(where[i] == -1)
        {
            return INF;
        }
    }

    return 1;
}