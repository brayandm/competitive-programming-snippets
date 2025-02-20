// TAB_TRIGGER "__NEWTON_METHOD"

template<class F, class G>
long double NEWTON_METHOD(F f, G df, long double x)
{
    for(int i = 0 ; i < 100 ; i++)
    {
        long double fx = f(x), dfx = df(x);
        x = x-fx/dfx;
        if(abs(f(x)) < 1e-12)
        {
            break;
        }
    }
    return x;
}