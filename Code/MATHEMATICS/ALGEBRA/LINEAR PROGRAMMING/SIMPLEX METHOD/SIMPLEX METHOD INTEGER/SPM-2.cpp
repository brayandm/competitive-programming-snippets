// TAB_TRIGGER "__SIMPLEX_METHOD_INTEGER"

bool SIMPLEX_METHOD_INTEGER(vector<vector<double>> &A, vector<double> &B, vector<double> &C, long long &best, vector<long long> &solution)
{
    const double eps = 1e-9, oo = numeric_limits<double>::infinity();

    vector<double> x;
    double v = SIMPLEX_METHOD_PD(A, B, C, x);

    // Infeasible
    if(v == oo || v == -oo)return false;

    if((long long)ceil(v) >= best)return true;

    for(int i = 0 ; i < (int)x.size() ; i++)
    {
        double a = floor(x[i]);
        double b = ceil(x[i]);

        if(min(x[i] - a, b - x[i]) >= eps)
        {
            vector<vector<double>> NA = A;
            vector<double> NB = B;
            int vars = C.size();
            vector<double> nv(vars);
            nv[i] = -1;

            NA.push_back(nv);
            NB.push_back(-b);

            bool ok = SIMPLEX_METHOD_INTEGER(NA, NB, C, best, solution);

            NA.pop_back();
            NB.pop_back();

            nv[i] = 1;
            NA.push_back(nv);
            NB.push_back(a);
            ok |= SIMPLEX_METHOD_INTEGER(NA, NB, C, best, solution);

            return ok;
        }
    }

    // Solution is stored in x.
    // You may safely assume that it will be integer.

    long long cur_value = (long long)round(v);

    if(cur_value < best)
    {
        best = cur_value;
        solution = vector<long long>(x.begin(), x.end());
    }

    return true;
}