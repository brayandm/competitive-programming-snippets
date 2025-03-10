// TAB_TRIGGER "__GAUSSIAN_ELIMINATION_BINARY"

int GAUSSIAN_ELIMINATION(vector<bitset<__sz_bset>> A, int N, int M, bitset<__sz_bset> &ans)
{
    const int INF = 2;

    vector<int> where(M, -1);

    for(int col = 0, row = 0 ; col < M && row < N ; col++)
    {
        for(int i = row ; i < N ; i++)
        {
            if(A[i][col])
            {   
                if(i == row)break;
                swap(A[i], A[row]);
                break;
            }
        }

        if(!A[row][col])
        {
            continue;
        }

        where[col] = row;

        for(int i = row+1 ; i < N ; i++)
        {
            if(A[i][col])
            {
                A[i] ^= A[row];
            }
        }

        row++;
    }

    ans.reset();

    vector<bool> vect(N);

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
            vect[i] = vect[i]^(ans[j]&A[i][j]);
        }
    }

    for(int i = 0 ; i < N ; i++)
    {
        bool xorr = 0;

        for(int j = 0 ; j < M ; j++)
        {
            xorr = xorr^(ans[j]*A[i][j]);
        }

        if(xorr != A[i][M])
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