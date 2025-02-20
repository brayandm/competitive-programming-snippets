// TAB_TRIGGER "__HARMONIC_SERIES_PARTITION"

vector<pair<ll,ll>> HARMONIC_SERIES_PARTITION(ll N)
{
    vector<pair<ll,ll>> res;
    ll temp = 0;
    for(ll i = 1, la ; i <= N ; i = la+1)
    {
        la = N/(N/i);
        res.push_back({temp+1,la});
        temp = la;
    }
    return res;
}