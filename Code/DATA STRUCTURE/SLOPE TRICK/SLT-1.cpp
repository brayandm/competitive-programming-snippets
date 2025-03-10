// TAB_TRIGGER "__SLOPE_TRICK"

vector<long long> SLOPE_TRICK(vector<long long> vect)
{
    int N = vect.size();
    priority_queue<long long> Q;
    vector<long long> ans;
    for(int i = 0 ; i < N ; i++)
    {
        Q.push(vect[i]);
        ans.push_back(Q.top());
        if(vect[i] < Q.top())
        {
            Q.pop();
            Q.push(vect[i]);
        }
    }
    for(int i = N-2 ; i >= 0 ; i--)
    {
        ans[i] = min(ans[i], ans[i+1]);
    }
    return ans;
}