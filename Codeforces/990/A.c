// clang-format off
long long n,m,a,b,x,y;main(){scanf("%lld%lld%lld%lld",&n,&m,&a,&b);x=n%m*b,y=(m-n%m)*a;printf("%lld",x<y?x:y);}