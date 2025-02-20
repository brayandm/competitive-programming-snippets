// TAB_TRIGGER "__RANDOM"

typedef long long ll;
mt19937_64 _rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937 _rng(chrono::steady_clock::now().time_since_epoch().count());
// uniform_int_distribution<datatype>(a,b)(_rng);
// shuffle(vect.begin(),vect.end(),_rng);

ll rng(ll a, ll b)
{
    return uniform_int_distribution<ll>(a,b)(_rng);
}