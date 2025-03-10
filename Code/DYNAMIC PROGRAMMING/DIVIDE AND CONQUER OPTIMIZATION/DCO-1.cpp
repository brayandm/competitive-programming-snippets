// TAB_TRIGGER "__DIVIDE_AND_CONQUER_OPTIMIZATION"

void DIVIDE_AND_CONQUER(int k, int L, int R, int optL, int optR)
{
    if(L > R)return;
    int m = (L+R)/2, opt = -1;
    dp[m][k] = oo;
    for(int i = optL ; i <= min(m,optR) ; i++)
    {
        ll t = dp[i-1][k-1] + w(i,m);
        if(dp[m][k] > t)dp[m][k] = t, opt = i;
    }
    DIVIDE_AND_CONQUER(k,L,m-1,optL,opt);
    DIVIDE_AND_CONQUER(k,m+1,R,opt,optR);
}