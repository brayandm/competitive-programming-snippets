// TAB_TRIGGER "__INVERT_MATRIX_REAL"

typedef long double ld;

bool INVERT_MATRIX(vector<vector<ld>> A, vector<vector<ld>> &B)
{
    const ld EPS = 1e-9;

    int N = (int)A.size();

    B.assign(N,vector<ld>(N));

    for(int i = 0 ; i < N ; i++)
    {
        B[i][i] = 1;
    }

    for(int i = 0 ; i < N ; i++)
    {
        int sel = i;

        for(int j = i ; j < N ; j++)
        {
            if(abs(A[j][i]) > abs(A[sel][i]))
            {
                sel = j;
            }
        }

        if(abs(A[sel][i]) < EPS)
        {
            return false;
        }

        for(int j = 0 ; j < N ; j++)
        {
            swap(A[sel][j], A[i][j]);
            swap(B[sel][j], B[i][j]);
        }

        ld c = A[i][i];

        for(int j = 0 ; j < N ; j++)
        {
            A[i][j] /= c;
            B[i][j] /= c;
        }

        for(int j = 0 ; j < N ; j++)
        {
            if(i == j)continue;

            ld c = A[j][i];

            for(int k = 0 ; k < N ; k++)
            {
                A[j][k] -= A[i][k]*c;
                B[j][k] -= B[i][k]*c;
            }
        }
    }

    return true;
}