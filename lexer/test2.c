int judge(long long a);

int main()
{
    int n,x;
    int num[11]={0};
    scanf("%d",&n);
    long long a;
    for(x=0;x<n;x++)
    {
        scanf("%lld",&a);
        num[judge(a)]++;
    }
    for(x=1;x<11;x++)
        printf("%d\n",num[x]);
    return 0;
}

int judge(long long a)
{
    if(a<10)
        return 1;
    else
        return (1+judge(a/10));
}