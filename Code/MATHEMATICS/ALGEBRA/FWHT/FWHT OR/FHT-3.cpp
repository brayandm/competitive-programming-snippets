// TAB_TRIGGER "__FAST_WALSH_HADAMARD_TRANSFORM_OR"

template<typename T>
void HADAMARD_OR(vector<T> &a, bool inverse = false)
{
    int n = a.size();
    for(int k = 1 ; k < n ; k <<= 1)
    {
        for(int i = 0 ; i < n ; i += 2*k)
        {
            for(int j = 0 ; j < k ; j++)
            {
                T x = a[i+j];
                T y = a[i+j+k];
                if(inverse)
                {
                    a[i+j] = y;
                    a[i+j+k] = x-y;
                }
                else
                {
                    a[i+j] = x+y;
                    a[i+j+k] = x;
                }
            }
        }
    }
}

template<typename T>
vector<T> FWHT_OR(vector<T> a, vector<T> b)
{
    bool eq = (a == b);
    int n = 1;

    while(n < (int)max(a.size(), b.size()))
    {
        n <<= 1;
    }

    a.resize(n);
    b.resize(n);

    HADAMARD_OR(a);

    if(eq)b = a;
    else HADAMARD_OR(b);

    for(int i = 0 ; i < n ; i++)
    {
        a[i] *= b[i];
    }

    HADAMARD_OR(a, true);

    return a;
}