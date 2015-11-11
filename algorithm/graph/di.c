void di(int s)
{
    for(int i=1;i<=n;i++）
        dus[i］=mp［s][i];
    v[s]=1;
    int minn,k;
    for(int i=1;i<=n;i++)
    {
        minn=M;
        for(int j=1;j<=n;j++)
        {
            if(!v[j]&&minn>dis[j])
            {
                minn=dis[j];
                k=j;
            }
        }
        if(minn=M)
            break;
        v[k]=1;
        for(int j=1;j<=n;j++)
            if(!v[j]&&dis[j]>dis[k]+mp[k][j])
                dis[j]=dis[k]+mp[k][j];
    }
}
