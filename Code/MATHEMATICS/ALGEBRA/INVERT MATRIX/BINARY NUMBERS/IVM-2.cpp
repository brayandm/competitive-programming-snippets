// TAB_TRIGGER "__INVERT_MATRIX_BINARY"

bool INVERT_MATRIX(vector<bitset<__sz_bset>> A, int N, vector<bitset<__sz_bset>> &B)
{
    B.assign(N,bitset<__sz_bset>(0));

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
                swap(A[i], A[j]);
                swap(B[i], B[j]);
                break;
            }
        }

        if(!A[i][i])
        {
            return false;
        }

        for(int j = 0 ; j < N ; j++)
        {
            if(i != j && A[j][i])
            {
                A[j] ^= A[i];
                B[j] ^= B[i];
            }
        }
    }

    return true;
}