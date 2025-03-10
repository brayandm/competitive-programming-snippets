// TAB_TRIGGER "__FAST_FOURIER_TRANSFORM"

struct point
{
    double x, y;
    point(double x = 0, double y = 0) : x(x), y(y) {}

    friend point operator+(const point &a, const point &b)
    {
        return {a.x + b.x, a.y + b.y};
    }
    friend point operator-(const point &a, const point &b)
    {
        return {a.x - b.x, a.y - b.y};
    }
    friend point operator*(const point &a, const point &b)
    {
        return {a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x};
    }
    friend point operator/(const point &a, double d)
    {
        return {a.x / d, a.y / d};
    }
};

void FFT(vector<point> &a, int sign = +1)
{
    int n = a.size();

    for(int i = 1, j = 0 ; i < n-1 ; i++)
    {
        for(int k = n >> 1 ; (j ^= k) < k ; k >>= 1);
        if(i < j)swap(a[i], a[j]);
    }

    double theta = 2 * atan2(0, -1) * sign;

    for(int m, mh = 1 ; (m = mh << 1) <= n ; mh = m)
    {
        point wm(cos(theta / m), sin(theta / m)), w(1, 0);

        for(int i = 0 ; i < n ; i += m, w = point(1, 0))
            for(int j = i, k = j + mh ; j < i + mh ; j++, k++, w = w * wm)
            {
                point x = a[j], y = a[k] * w;
                a[j] = x + y;
                a[k] = x - y;
            }
    }

    if(sign == -1)
        for(point &p : a)p = p / n;
}

vector<double> CONVOLVE(vector<double> v1, vector<double> v2)
{
    int N = 1, size = v1.size() + v2.size() - 1;
    while(N < size)N *= 2;

    v1.resize(N), v2.resize(N);

    vector<point> c1(v1.begin(), v1.end());
    vector<point> c2(v2.begin(), v2.end());

    FFT(c1), FFT(c2);

    for(int i = 0 ; i < N ; i++)c1[i] = c1[i]*c2[i];

    FFT(c1, -1);

    for(int i = 0 ; i < N ; i++)v1[i] = c1[i].x;

    v1.resize(size);

    return v1;
}