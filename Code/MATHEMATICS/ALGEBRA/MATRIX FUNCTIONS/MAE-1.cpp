// TAB_TRIGGER "__MATRIX_EXPONENTATION"

const ll MOD2 = MOD*MOD;

struct MATRIX
{
    vector<vector<ll>> mat;

    MATRIX() {};

    MATRIX(const vector<vector<ll>> vect)
    {
        *this = vect;
    }

    MATRIX& operator=(const vector<vector<ll>> vect)
    {
        mat = vect;
        return *this;
    }

    void print()
    {
        cerr << '\n';
        for(int i = 0 ; i < mat.size() ; i++)
        {
            cerr << "[";
            for(int j = 0 ; j < mat[i].size() ; j++)
            {
                if(j)cerr << ", ";
                cerr << mat[i][j];
            }
            cerr << "]" << '\n';
        }
        cerr << '\n';
    }

    friend void print(MATRIX A)
    {
        cerr << '\n';
        for(int i = 0 ; i < A.mat.size() ; i++)
        {
            cerr << "[";
            for(int j = 0 ; j < A.mat[i].size() ; j++)
            {
                if(j)cerr << ", ";
                cerr << A.mat[i][j];
            }
            cerr << "]" << '\n';
        }
        cerr << '\n';
    }

    MATRIX identity(int N)
    {
        MATRIX A(vector<vector<ll>>(N,vector<ll>(N)));
        for(int i = 0 ; i < N ; i++)A.mat[i][i] = 1;
        return A;
    }

    MATRIX& operator+(MATRIX A)
    {
        *this = sum(*this,A);
        return *this;
    }

    MATRIX& operator+=(MATRIX A)
    {
        *this = sum(*this,A);
        return *this;
    }

    MATRIX& operator*(MATRIX A)
    {
        *this = mult(*this,A);
        return *this;
    }

    MATRIX& operator*=(MATRIX A)
    {
        *this = mult(*this,A);
        return *this;
    }

    MATRIX sum(const MATRIX &A, const MATRIX &B)
    {
        MATRIX C(vector<vector<ll>>(A.mat.size(),vector<ll>(A.mat[0].size())));

        for(int i = 0 ; i < C.mat.size() ; i++)
        {
            for(int j = 0 ; j < C.mat[0].size() ; j++)
            {
                C.mat[i][j] = A.mat[i][j] + B.mat[i][j];
                if(C.mat[i][j] >= MOD)C.mat[i][j] -= MOD;
            }
        }

        return C;
    }

    MATRIX mult(const MATRIX &A, const MATRIX &B)
    {
        MATRIX C(vector<vector<ll>>(A.mat.size(),vector<ll>(B.mat[0].size())));

        for(int i = 0 ; i < C.mat.size() ; i++)
        {
            for(int j = 0 ; j < C.mat[i].size() ; j++)
            {
                for(int k = 0 ; k < A.mat[i].size() ; k++)
                {
                    C.mat[i][j] += A.mat[i][k] * B.mat[k][j];
                    if(C.mat[i][j] >= MOD2)C.mat[i][j] -= MOD2;
                }
            }
        }

        for(int i = 0 ; i < C.mat.size() ; i++)
        {
            for(int j = 0 ; j < C.mat[0].size() ; j++)
            {
                C.mat[i][j] %= MOD;
            }
        }

        return C;
    }

    void pow(ll e)
    {
        MATRIX res = identity(mat.size());
        while(e)
        {
            if(e&1)res = mult(res,*this);
            *this = mult(*this,*this);
            e /= 2;
        }
        *this = res;
    }

    friend MATRIX pow(MATRIX A, ll e)
    {
        A.pow(e);
        return A;
    }

    void sumpow(MATRIX &S, MATRIX &A, ll e)
    {
        if(e == 1)S = *this, A = *this;
        else if(e&1)sumpow(S,A,e-1), A = mult(A,*this), S = sum(S,A);
        else sumpow(S,A,e/2), S = sum(S,mult(A,S)), A = mult(A,A);
    }

    void sumpow(ll e)
    {
        MATRIX S, A;
        sumpow(S,A,e);
        *this = S;
    }

    friend MATRIX sumpow(MATRIX A, ll e)
    {
        A.sumpow(e);
        return A;
    }
};