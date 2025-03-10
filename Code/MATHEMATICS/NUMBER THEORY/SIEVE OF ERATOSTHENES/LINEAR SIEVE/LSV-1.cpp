// TAB_TRIGGER "__LINEAR_SIEVE"

struct LINEAR_SIEVE
{
    vector<int> primes;
    vector<int> least;
    vector<int> cnt;
    vector<int> pw;
    vector<int> phi;
    vector<int> sigma;
    vector<int> mu;
    LINEAR_SIEVE(int N)
    {
        if(N < 1)N = 1;
        least.resize(N+1);
        cnt.resize(N+1);
        pw.resize(N+1);
        phi.resize(N+1);
        sigma.resize(N+1);
        mu.resize(N+1);
        pw[1] = 0;
        least[1] = cnt[1] = phi[1] = sigma[1] = mu[1] = 1;
        for(int i = 2 ; i <= N ; i++)
        {
            if(least[i] == 0)
            {
                primes.push_back(i);
                least[i] = i;
                cnt[i] = i;
                pw[i] = 1;
                phi[i] = i-1;
                sigma[i] = i+1;
                mu[i] = -1;
            }
            for(auto x : primes)
            {
                int nx = i*x;
                if(x > least[i] || nx > N)break;
                least[nx] = x;
                if(x == least[i])cnt[nx] = cnt[i]*least[i], pw[nx] = pw[i]+1;
                else cnt[nx] = least[nx], pw[nx] = 1;
                if(nx == cnt[nx])
                {
                    phi[nx] = cnt[nx]-cnt[nx]/least[nx];
                    sigma[nx] = (cnt[nx]*least[nx]-1)/(least[nx]-1);
                    mu[nx] = 0;
                }
                else
                {
                    phi[nx] = phi[nx/cnt[nx]]*phi[cnt[nx]];
                    sigma[nx] = sigma[nx/cnt[nx]]*sigma[cnt[nx]];
                    mu[nx] = mu[nx/cnt[nx]]*mu[cnt[nx]];
                }
            }
        }
    }
};