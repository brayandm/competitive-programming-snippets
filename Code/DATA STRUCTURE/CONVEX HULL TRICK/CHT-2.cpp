// TAB_TRIGGER "__CONVEX_HULL_TRICK"

template<typename T>
struct convex_hull_trick
{
    using point = std::complex<T>;
    using hull = std::vector<point>;

    void insert(const point &p)
    {
        hull lu(1, p), uh(1, p);
        for (std::size_t i = 0; i < lower_hull.size(); ++i)
            if (lower_hull[i].empty())
            {
                lu.swap(lower_hull[i]);
                uh.swap(upper_hull[i]);
                break;
            }
            else
            {
                lu = merge(lu, lower_hull[i], [](T val)
                {
                    return val <= 0;
                });
                uh = merge(uh, upper_hull[i], [](T val)
                {
                    return val >= 0;
                });
                lower_hull[i].clear();
                upper_hull[i].clear();
            }
        if (!lu.empty())
        {
            lower_hull.emplace_back(lu);
            upper_hull.emplace_back(uh);
        }
    }

    point extreme(const point &p) const
    {
        const auto &h = p.imag() > 0 ? upper_hull : lower_hull;
        point best;
        bool found = false;
        for (const hull &_h : h)
        {
            if (_h.empty()) continue;
            std::size_t lo = 0, hi = _h.size() - 1, mid;
            while (lo < hi)
            {
                mid = (lo + hi) / 2;
                point q = _h[mid] - _h[mid + 1];
                long double x = (long double) real(p) * real(q) + (long double) imag(p) * imag(q);
                int sign = x < -1e-10 ? -1 : x > 1e-10 ? 1 : 0;
                if (sign <= 0) lo = mid + 1;
                else hi = mid;
            }
            if (!found || dot(best, p) <= dot(_h[lo], p)) best = _h[lo];
            found = true;
        }
        assert(found);
        return best;
    }

    static T cross(const point &a, const point &b)
    {
        return std::imag(std::conj(a) * b);
    }
    static T dot(const point &a, const point &b)
    {
        return std::real(std::conj(a) * b);
    }

    void swap(convex_hull_trick &other)
    {
        lower_hull.swap(other.lower_hull);
        upper_hull.swap(other.upper_hull);
    }

private:
    std::vector<hull> lower_hull, upper_hull;

    template<typename F>
    static hull merge(const hull &a, const hull &b, const F &cond)
    {
        auto comp = [](const point &p, const point &q)
        {
            return p.real() < q.real() || (p.real() == q.real() && p.imag() < q.imag());
        };
        hull h;
        auto sign = [](long double x)
        {
            return x < -1e-10 ? -1 : x > 1e-10 ? 1 : 0 ;
        };
        auto add_point = [&](const point &p)
        {
            while (h.size() >= 2)
            {
                point a = h.end()[-1] - h.end()[-2], b = p - h.end()[-2];
                long double x = (long double) real(a) * imag(b) - (long double) imag(a) * real(b);
                if (!cond(sign(x))) break;
                h.pop_back();
            }
            h.emplace_back(p);
        };
        for (std::size_t i = 0, j = 0; i < a.size() || j < b.size();)
            add_point(i == a.size() || (j != b.size() && comp(b[j], a[i])) ? b[j++] : a[i++]);
        return h;
    }

    static int comp(T p, T q, T a, T b)
    {
        if (!p && !a) return 0;
        if (p < 0 && a >= 0) return -1;
        if (p >= 0 && a < 0) return 1;
        if (a <= 0 && p <= 0) return -comp(-p, q, -a, b);
        T v1 = p / q, v2 = a / b;
        if (v1 > v2) return 1;
        if (v1 < v2) return -1;
        p = p % q;
        a = a % b;
        if (!a && !p) return 0;
        if (!a) return 1;
        if (!p) return -1;
        return -comp(q, p, b, a);
    }
};