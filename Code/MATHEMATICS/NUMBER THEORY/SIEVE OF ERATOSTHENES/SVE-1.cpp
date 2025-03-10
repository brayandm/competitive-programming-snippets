// TAB_TRIGGER "__SIEVE_OF_ERATOSTHENES"

struct SIEVE_OF_ERATOSTHENES
{
    vector<int> primes;
    vector<int> least;
    vector<int> cnt;
    vector<int> pw;
    vector<int> phi;
    vector<int> sigma;
    vector<int> mu;
    SIEVE_OF_ERATOSTHENES(int N)
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
        for(int i = 4 ; i <= N ; i+=2)least[i] = 2;
        for(int i = 3 ; i*i <= N ; i+=2)
        {
            if(least[i] == 0)
            {
                for(int j = i*i ; j <= N ; j+=i*2)
                {
                    if(least[j] == 0)least[j] = i;
                }
            }
        }
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
            else
            {
                int x = i/least[i];
                if(least[i] == least[x])cnt[i] = cnt[x]*least[i], pw[i] = pw[x]+1;
                else cnt[i] = least[i], pw[i] = 1;
                if(i == cnt[i])
                {
                    phi[i] = cnt[i]-cnt[i]/least[i];
                    sigma[i] = (cnt[i]*least[i]-1)/(least[i]-1);
                    mu[i] = 0;
                }
                else
                {
                    phi[i] = phi[i/cnt[i]]*phi[cnt[i]];
                    sigma[i] = sigma[i/cnt[i]]*sigma[cnt[i]];
                    mu[i] = mu[i/cnt[i]]*mu[cnt[i]];
                }
            }
        }
    }
};