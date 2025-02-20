// TAB_TRIGGER "__INTEGER_DIVISION"

typedef long long ll;

inline ll ceil(ll a, ll b)
{
    return a/b + ((a>0)^(b>0) ? 0 : a%b != 0);
}

inline ll floor(ll a, ll b)
{
    return a/b - ((a>0)^(b>0) ? a%b != 0 : 0);
}