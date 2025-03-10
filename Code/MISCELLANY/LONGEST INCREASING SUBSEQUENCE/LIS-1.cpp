// TAB_TRIGGER "__LONGEST_INCREASING_SUBSEQUENCE"

template<typename T>
vector<int> LIS(const vector<T> &arr)
{
    int N = arr.size();
    vector<int> lis, temp;
    for(int i = 0 ; i < N ; i++)
    {
        int pos = lower_bound(temp.begin(),temp.end(),arr[i])-temp.begin();
        if(pos == temp.size())temp.push_back(arr[i]);
        else temp[pos] = arr[i];
        lis.push_back(pos+1);
    }
    return lis;
}