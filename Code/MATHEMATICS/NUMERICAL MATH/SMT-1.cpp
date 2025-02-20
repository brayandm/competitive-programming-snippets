// TAB_TRIGGER "__SECANT_METHOD"

template<class F>
long double SECANT_METHOD(F f, long double x1, long double x2)
{
    for(int i = 0 ; i < 100 ; i++)
    {
        long double f1 = f(x1), f2 = f(x2), xt = (x1*f2-x2*f1)/(f2-f1);
        x1 = x2, x2 = xt;
        if(abs(f(x2)) < 1e-12)
        {
            break;
        }
    }
    return x2;
}