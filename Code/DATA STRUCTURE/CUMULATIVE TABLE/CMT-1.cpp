// TAB_TRIGGER "__CUMULATIVE_TABLE"

template<typename T>
struct CUMULATIVE_TABLE
{
    vector<T> acum;

    CUMULATIVE_TABLE(vector<T> &vect)
    {
        int N = vect.size();
        acum = vect;
        for(int i = 0 ; i < N ; i++)
        {
            if(i)acum[i] += acum[i-1];
        }
    }

    T query(int a, int b)
    {
        T res = acum[b];
        if(a)res -= acum[a-1];
        return res;
    }
};