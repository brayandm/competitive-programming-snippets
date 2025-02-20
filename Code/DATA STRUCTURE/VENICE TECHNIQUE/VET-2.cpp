// TAB_TRIGGER "__VENICE_TECHNIQUE"

template<typename T>
struct VENICE_SET
{
    T vmin = numeric_limits<T>::max();
    T vmax = numeric_limits<T>::min();
    T acum = 0;
    int sz = 0;
    void insert(T x)
    {
        sz++;
        vmin = min(vmin, x - acum);
        vmax = max(vmax, x - acum);
    }
    void update(T x)
    {
        acum += x;
    }
    T getmin()
    {
        assert(sz);
        return vmin + acum;
    }
    T getmax()
    {
        assert(sz);
        return vmax + acum;
    }
    int size()
    {
        return sz;
    }
};