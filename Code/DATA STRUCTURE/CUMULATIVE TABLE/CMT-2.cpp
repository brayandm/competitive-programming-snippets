// TAB_TRIGGER "__CUMULATIVE_TABLE_2D"

template<typename T>
struct CUMULATIVE_TABLE_2D
{
    vector<vector<T>> acum;

    CUMULATIVE_TABLE_2D(vector<vector<T>> &vect)
    {
        int N = vect.size();
        int M = vect[0].size();
        acum = vect;
        for(int i = 0 ; i < N ; i++)
        {
            for(int j = 0 ; j < M ; j++)
            {
                if(i)acum[i][j] += acum[i-1][j];
                if(j)acum[i][j] += acum[i][j-1];
                if(i && j)acum[i][j] -= acum[i-1][j-1];
            }
        }
    }

    T query(int x1, int y1, int x2, int y2)
    {
        T res = acum[x2][y2];
        if(x1)res -= acum[x1-1][y2];
        if(y1)res -= acum[x2][y1-1];
        if(x1 && y1)res += acum[x1-1][y1-1];
        return res;
    }
};