// TAB_TRIGGER "__NUMERICAL_DIFFERENTIATION"

template<class F>
long double NUMERICAL_DIFFERENTIATION_FIRST_DERIVATIVE(F f, long double x)
{
    const long double EPS = 1e-9;
    const long double h = EPS*x;
    return (f(x+h)-f(x-h))/(2*h);
}

template<class F>
long double NUMERICAL_DIFFERENTIATION_FIRST_DERIVATIVE_OPTIMIZED(F f, long double x)
{
    const long double EPS = 1e-9;
    const long double h = EPS*x;
    return (-f(x+2*h)+8*f(x+h)-8*f(x-h)+f(x-2*h))/(12*h);
}

template<class F>
long double NUMERICAL_DIFFERENTIATION_SECOND_DERIVATIVE(F f, long double x)
{
    const long double EPS = 1e-6;
    const long double h = EPS*x;
    return (f(x+h)-2*f(x)+f(x-h))/(h*h);
}