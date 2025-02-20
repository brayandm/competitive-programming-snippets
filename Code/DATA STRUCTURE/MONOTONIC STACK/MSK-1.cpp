// TAB_TRIGGER "__MONOTONIC_STACK"

template<typename T, class F = less<T>>
struct MONOTONIC_STACK
{
    stack<pair<T,int>> S;
    int sz = 0;
    void insert(T x)
    {
        sz++;
        if(S.empty() || F()(x,S.top().first))S.push({x,sz});
    }
    void erase()
    {
        assert(sz);
        sz--;
        if(S.top().second > sz)S.pop();
    }
    int get()
    {
        assert(sz);
        return S.top().first;
    }
};