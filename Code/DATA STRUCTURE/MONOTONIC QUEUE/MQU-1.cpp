// TAB_TRIGGER "__MONOTONIC_QUEUE"

template<typename T, class F = less<T>>
struct MONOTONIC_QUEUE
{
    deque<pair<T,int>> D;
    int sz = 0;
    int pt = 0;
    void insert(T x)
    {
        sz++;
        while(!D.empty() && !F()(D.back().first,x))D.pop_back();
        D.push_back({x,pt++});
    }
    void erase()
    {
        assert(sz);
        sz--;
        if(pt-D.front().second > sz)D.pop_front();
    }
    T get()
    {
        assert(sz);
        return D.front().first;
    }
};