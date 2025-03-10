// TAB_TRIGGER "__CONVEX_HULL_TRICK"

template<typename T, class F = less<T>>
struct CONVEX_HULL_TRICK
{
    deque<pair<T,T>> D;
    bool best(pair<T,T> p1, pair<T,T> p2, pair<T,T> p3)
    {
        return (p3.second-p1.second)*(p2.first-p3.first) <= (p3.second-p2.second)*(p1.first-p3.first);
    }
    void insert(pair<T,T> p)
    {
        pair<T,T> temp1, temp2;

        if(D.size() && p.first == D.back().first)
        {
            if(!F()(D.back().second,p.second))D.pop_back();
            else return;
        }

        while(D.size() > 1)
        {
            temp1 = D.back();
            D.pop_back();
            temp2 = D.back();
            D.push_back(temp1);
            if(best(p,temp1,temp2))D.pop_back();
            else break;
        }
        D.push_back(p);
    }
    T f(pair<T,T> p, T x)
    {
        return p.first*x+p.second;
    }
    T get(T x)
    {
        pair<T,T> temp1, temp2;
        while(D.size() > 1)
        {
            temp1 = D.front();
            D.pop_front();
            temp2 = D.front();
            D.push_front(temp1);
            if(!F()(f(temp1,x),f(temp2,x)))D.pop_front();
            else break;
        }
        return f(D.front(),x);
    }
};