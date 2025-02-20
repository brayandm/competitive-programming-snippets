// TAB_TRIGGER "__GENERATE_DIVISORS"

vector<ll> GENERATE_DIVISORS(const vector<pair<ll,int>> &fact)
{
    vector<ll> div = {1};
    for(int i = 0 ; i < fact.size() ; i++)
    {
        vector<ll> temp;
        ll p = 1;
        for(int j = 0 ; j <= fact[i].second ; j++)
        {
            vector<ll> nw, tp;
            for(int k = 0 ; k < div.size() ; k++)tp.push_back(div[k]*p);
            merge(temp.begin(),temp.end(),tp.begin(),tp.end(),back_inserter(nw));
            swap(temp,nw);
            p *= fact[i].first;
        }
        swap(div,temp);
    }
    return div;
}