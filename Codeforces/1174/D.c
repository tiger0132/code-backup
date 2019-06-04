// clang-format off
l;main(n,x,i){scanf("%d%d",&n,&x);x=(x<1<<n)*(x&-x);printf("%d ",(1<<n-!!x)-1);for(;++i<1<<n;)x&i||(printf("%d ",i^l),l=i);}
main(n,q,k,i){scanf("%d%d",&n,&k),n=1<<n,printf("%d ",(n>>(k<n))-1),q=i=0;while(++i<n)if(i<(i^k))printf("%d ",i^q),q=i;} // Orz PinkRabbit