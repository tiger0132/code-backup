// clang-format off
main(a,n,k){for(scanf("%d%d",&n,&k),printf("%d\n",(6*n-1)*k);n--;a+=6)printf("%d %d %d %d\n",a*k,(a+1)*k,(a+2)*k,(a+4)*k);}