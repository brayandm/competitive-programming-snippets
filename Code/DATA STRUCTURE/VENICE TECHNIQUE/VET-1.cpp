// TAB_TRIGGER "__VENICE_TECHNIQUE"

template<typename T>
struct VENICE_SET
{
    multiset<T> st;
    T acum = 0;
    void insert(T x)
    {
        st.insert(x - acum);
    }
    void erase(T x)
    {
        st.erase(st.find(x - acum));
    }
    void update(T x)
    {
        acum += x;
    }
    T getmin()
    {
        assert(st.size());
        return *st.begin() + acum;
    }
    T getmax()
    {
        assert(st.size());
        return *(--st.end()) + acum;
    }
    int size()
    {
        return st.size();
    }
};