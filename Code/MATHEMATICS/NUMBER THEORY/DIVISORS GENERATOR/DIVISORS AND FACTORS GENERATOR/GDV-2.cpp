// TAB_TRIGGER "__GENERATE_DIVISORS_AND_FACTORS"

vector<pair<ll,vector<pair<ll,int>>>> GENERATE_DIVISORS_AND_FACTORS(const vector<pair<ll,int>> &fact)
{
    vector<pair<ll,vector<pair<ll,int>>>> div = {{1,{}}};

    for(int i = 0 ; i < fact.size() ; i++)
    {
        vector<pair<ll,vector<pair<ll,int>>>> temp;
        ll p = 1;
        for(int j = 0 ; j <= fact[i].second ; j++)
        {
            vector<pair<ll,vector<pair<ll,int>>>> nw, tp;
            for(int k = 0 ; k < div.size() ; k++)
            {
                tp.push_back({div[k].first*p,div[k].second});
                tp.back().second.push_back({fact[i].first,j});
            }
            merge(temp.begin(),temp.end(),tp.begin(),tp.end(),back_inserter(nw));
            swap(temp,nw);
            p *= fact[i].first;
        }
        swap(div,temp);
    }
    return div;
}