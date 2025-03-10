// TAB_TRIGGER "__FAST_WALSH_HADAMARD_TRANSFORM_XOR_MULTIMOD"

typedef long double ld;
typedef complex<ld> point;

void HADAMARD_XOR(vector<point> &a, int MOD, bool inverse = false)
{
    const ld PI = acos(-1);

    function<point(ld,ld)> root = [&](ld a, ld b)
    {
        ld angle = ((ld)(2.0))*PI*a/b;
        point p = {cos(angle),sin(angle)};
        return p;
    };

    point M[MOD][MOD];
    point iM[MOD][MOD];
    point arr[MOD];
    point temp[MOD];

    for(int i = 0 ; i < MOD ; i++)
    {
        for(int j = 0 ; j < MOD ; j++)
        {
            M[i][j] = root(i*j,MOD);
            iM[i][j] = (point){1.0,0}/(M[i][j]*(point){(ld)MOD,0});
        }
    }

    int n = a.size();
    for(int k = 1 ; k < n ; k *= MOD)
    {
        for(int i = 0 ; i < n ; i += MOD*k)
        {
            for(int j = 0 ; j < k ; j++)
            {
                for(int x = 0 ; x < MOD ; x++)
                {
                    arr[x] = a[i+j+x*k];
                    temp[x] = 0;
                }

                if(inverse)
                {
                    for(int x = 0 ; x < MOD ; x++)
                    {
                        for(int y = 0 ; y < MOD ; y++)
                        {
                            temp[x] += iM[x][y]*arr[y];
                        }
                    }
                }
                else
                {
                    for(int x = 0 ; x < MOD ; x++)
                    {
                        for(int y = 0 ; y < MOD ; y++)
                        {
                            temp[x] += M[x][y]*arr[y];
                        }
                    }
                }

                for(int x = 0 ; x < MOD ; x++)
                {
                    a[i+j+x*k] = temp[x];
                }
            }
        }
    }
}

vector<ld> FWHT_XOR(vector<ld> v1, vector<ld> v2, int MOD)
{
    vector<point> a, b;

    for(auto x : v1)
    {
        a.push_back(x);
    }

    for(auto x : v2)
    {
        b.push_back(x);
    }

    int n = 1;

    while(n < (int)max(a.size(), b.size()))
    {
        n *= MOD;
    }

    a.resize(n);
    b.resize(n);

    HADAMARD_XOR(a, MOD);
    HADAMARD_XOR(b, MOD);

    for(int i = 0 ; i < n ; i++)
    {
        a[i] *= b[i];
    }

    HADAMARD_XOR(a, MOD, true);

    vector<ld> res;

    for(auto x : a)
    {
        res.push_back(x.real());
    }

    return res;
}