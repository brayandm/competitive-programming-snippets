// TAB_TRIGGER "__CARTESIAN_TREE"

template<typename T, class F = less<T>>
int CARTESIAN_TREE(vector<vector<int>> &L, const vector<T> &arr)
{
    int N = arr.size();
    L.clear();
    L.resize(N);
    stack<int> st;
    vector<int> parent(N,-1);
    for(int i = 0 ; i < N ; i++)
    {
        int last = -1;
        while(!st.empty() && F()(arr[i],arr[st.top()]))last = st.top(), st.pop();
        if(!st.empty())parent[i] = st.top();
        if(last >= 0)parent[last] = i;
        st.push(i);
    }
    int root = -1;
    for(int i = 0 ; i < N ; i++)
    {
        if(parent[i] == -1)root = i;
        else L[parent[i]].push_back(i);
    }
    return root;
}