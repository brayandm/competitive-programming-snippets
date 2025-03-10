// TAB_TRIGGER "__GAUSSIAN_ELIMINATION_REAL"

typedef long double ld;

int GAUSSIAN_ELIMINATION(vector<vector<ld>> A, vector<ld> &ans)
{
    const ld EPS = 1e-9;
    const int INF = 2;

    int N = (int)A.size();
    int M = (int)A[0].size()-1;

    vector<int> where(M, -1);

    for(int col = 0, row = 0 ; col < M && row < N ; col++)
    {
        int sel = row;

        for(int i = row ; i < N ; i++)
        {
            if(abs(A[i][col]) > abs(A[sel][col]))
            {
                sel = i;
            }
        }

        if(abs(A[sel][col]) < EPS)
        {
            continue;
        }

        for(int i = col ; i <= M ; i++)
        {
            swap(A[sel][i], A[row][i]);
        }

        where[col] = row;

        for(int i = row+1 ; i < N ; i++)
        {
            ld c = A[i][col]/A[row][col];

            for(int j = col ; j <= M ; j++)
            {
                A[i][j] -= A[row][j]*c;
            }
        }

        row++;
    }

    ans.assign(M, 0);

    vector<ld> vect(N);

    for(int i = 0 ; i < N ; i++)
    {
        vect[i] = A[i][M];
    }

    for(int j = M-1 ; j >= 0 ; j--)
    {
        if(where[j] != -1)
        {
            ans[j] = vect[where[j]]/A[where[j]][j];
        }

        for(int i = 0 ; i < N ; i++)
        {
            vect[i] -= ans[j]*A[i][j];
        }
    }

    for(int i = 0 ; i < N ; i++)
    {
        ld sum = 0;

        for(int j = 0 ; j < M ; j++)
        {
            sum += ans[j]*A[i][j];
        }

        if(abs(sum - A[i][M]) > EPS)
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