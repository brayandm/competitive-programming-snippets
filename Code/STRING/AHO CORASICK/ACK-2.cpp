// TAB_TRIGGER "__AHO_CORASICK"

template<typename T, typename F>
struct AHO_CORASICK
{
    vector<pair<int,int>> lim;
    vector<vector<int>> glink;
    vector<vector<int>> words;
    vector<unordered_map<F,pair<int,bool>>> tgo;
    vector<int> pt_string;
    vector<int> dict_link;
    vector<int> vtime;
    vector<int> link;
    vector<int> abi;
    vector<int> ch;
    vector<int> p;
 
    int cant_string = 0;
    int sz = 0;
 
    bool ok_match = false;
    bool ok_link_tree = false;
 
    void init()
    {
        lim.clear();
        glink.clear();
        words.clear();
        tgo.clear();
        pt_string.clear();
        dict_link.clear();
        vtime.clear();
        link.clear();
        abi.clear();
        ch.clear();
        p.clear();
 
        cant_string = 0;
        sz = 0;
 
        ok_match = false;
        ok_link_tree = false;
 
        new_node(-1,-1);
    }
 
    void build(vector<T> &vect)
    {
        init();
        for(int i = 0 ; i < vect.size() ; i++)
        {
            add_string(vect[i]);
        }
    }
 
    int size()
    {
        return sz;
    }
 
    void new_node(int tp, int tch)
    {
        sz++;
        tgo.emplace_back();
        dict_link.push_back(-1);
        words.emplace_back();
        link.push_back(-1);
        ch.push_back(tch);
        p.push_back(tp);
    }
 
    AHO_CORASICK()
    {
        init();
    }
 
    void add_string(T cad)
    {
        int pt = 0;
        for(int i = 0 ; i < cad.size() ; i++)
        {
            F tch = cad[i];
            auto it = &tgo[pt][tch];
            if((*it).second == false)
            {
                (*it).second = true;
                (*it).first = sz;
                new_node(pt, tch);
            }
            pt = (*it).first;
        }
        words[pt].push_back(pt_string.size());
        pt_string.push_back(pt);
    }
 
    void build_link_tree()
    {
        ok_link_tree = true;
        glink.resize(sz);
        for(int i = 1 ; i < sz ; i++)
        {
            glink[get_link(i)].push_back(i);
        }
    }
 
    void build_match()
    {
        ok_match = true;
        if(ok_link_tree == false)build_link_tree();
        vtime.resize(sz);
        lim.resize(sz);
        abi.resize(sz+1);
        int ct = 0;
        function<void(int)> DFS = [&](int nodo)
        {
            vtime[nodo] = ++ct;
            for(auto v : glink[nodo])
            {
                DFS(v);
            }
            lim[nodo] = {vtime[nodo], ct};
        };
        DFS(0);
    }
 
    void abi_update(int x, int v)
    {
        while(x < abi.size())
        {
            abi[x] += v;
            x += x&-x;
        }
    }
 
    int abi_query(int x)
    {
        int res = 0;
        while(x)
        {
            res += abi[x];
            x -= x&-x;
        }
        return res;
    }
 
    int abi_range(int a, int b)
    {
        return abi_query(b) - abi_query(a-1);
    }
 
    vector<int> match(vector<T> vcad)
    {
        if(ok_match == false)build_match();
        vector<int> ups;
        for(auto cad : vcad)
        {
            int pt = 0;
            for(int i = 0 ; i < cad.size() ; i++)
            {
                pt = go(pt, cad[i]);
                abi_update(vtime[pt], 1);
                ups.push_back(vtime[pt]);
            }
        }
        vector<int> res(pt_string.size());
        for(int i = 0 ; i < pt_string.size() ; i++)
        {
            res[i] = abi_range(lim[pt_string[i]].first, lim[pt_string[i]].second);
        }
        for(auto x : ups)
        {
            abi_update(x, -1);
        }
        return res;
    }
 
    vector<int> match_offline(vector<T> vcad)
    {
        if(ok_link_tree == false)build_link_tree();
        vector<int> dp(sz);
        for(auto cad : vcad)
        {
            int pt = 0;
            for(int i = 0 ; i < cad.size() ; i++)
            {
                pt = go(pt, cad[i]);
                dp[pt]++;
            }
        }
        function<void(int)> DFS = [&](int nodo)
        {
            for(auto v : glink[nodo])
            {
                DFS(v);
                dp[nodo] += dp[v];
            }
        };
        DFS(0);
        vector<int> res(pt_string.size());
        for(int i = 0 ; i < pt_string.size() ; i++)
        {
            res[i] = dp[pt_string[i]];
        }
        return res;
    }
 
    int get_dictionary_link(int nodo)
    {
        if(dict_link[nodo] == -1)
        {
            if(nodo == 0 || p[nodo] == 0)dict_link[nodo] = 0;
            else
            {
                int v = get_link(nodo);
                if(words[v].size())dict_link[nodo] = v;
                else dict_link[nodo] = get_dictionary_link(v);
            }
        }
        return dict_link[nodo];
    }
 
    int get_link(int nodo)
    {
        if(link[nodo] == -1)
        {
            if(nodo == 0 || p[nodo] == 0)link[nodo] = 0;
            else link[nodo] = go(get_link(p[nodo]), ch[nodo]);
        }
        return link[nodo];
    }
 
    int go(int nodo, F tch)
    {
        auto it = &tgo[nodo][tch];
        if((*it).second == false)
        {
            (*it).second = true;
            (*it).first = (nodo == 0) ? 0 : go(get_link(nodo),tch);
        }
        return (*it).first;
    }
};