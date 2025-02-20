// TAB_TRIGGER "__FAST_WALSH_HADAMARD_TRANSFORM_AND"

template<typename T>
void HADAMARD_AND(vector<T> &a, bool inverse = false)
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
                    a[i+j] = -x+y;
                    a[i+j+k] = x;
                }
                else
                {
                    a[i+j] = y;
                    a[i+j+k] = x+y;
                }
            }
        }
    }
}

template<typename T>
vector<T> FWHT_AND(vector<T> a, vector<T> b)
{
    bool eq = (a == b);
    int n = 1;

    while(n < (int)max(a.size(), b.size()))
    {
        n <<= 1;
    }

    a.resize(n);
    b.resize(n);

    HADAMARD_AND(a);

    if(eq)b = a;
    else HADAMARD_AND(b);

    for(int i = 0 ; i < n ; i++)
    {
        a[i] *= b[i];
    }

    HADAMARD_AND(a, true);

    return a;
}