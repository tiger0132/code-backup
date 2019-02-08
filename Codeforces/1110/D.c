// clang-format off
#define F(x)for(x=0;x<3;x++)
C[1<<20],D[1<<20][3][3];main(n,x,i,j,k,t){for(scanf("%*d%d",&n);~scanf("%d",&x);C[x]++);for(x=1;x<=n;x++)F(i)F(j)F(k)i+j+k<=C[x]&&D[x][j][k]<(t=D[x-1][i][j]+(C[x]-i-j-k)/3+k)&&(D[x][j][k]=t);printf("%d",**D[n]);}