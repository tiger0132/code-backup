#include <algorithm>
#include <cctype>
#include <cstdio>

typedef unsigned long long u;
const int N = 1e5 + 51;

// clang-format off
char B[1<<21],*S=B,*T=B;
inline char getcharx(){return S==T&&(T=(S=B)+fread(B,1,1<<15,stdin),S==T)?0:*S++;}
template<class T>inline void get(T&val){static char ch;val=0;while(!isdigit(ch=getcharx()));do val=val*10+ch-48;while(isdigit(ch=getcharx()));}
char oB[1<<24],*oS=oB;void prt(const u&v){if(v>9)prt(v/10);*oS++=v%10+48;}

struct _{u x,y;inline _ operator+(const _&r)const{return{(x&r.y)|(~x&r.x),(y&r.y)|(~y&r.x)};}};
inline _ $(int op,u x){return op==1?_{0,x}:op==2?_{x,-1ull}:_{x,~x};}

struct edg{int to,next;}e[N<<1];int head[N],cnt;inline void ad(int x,int y){e[++cnt]={y,head[x]},head[x]=cnt,e[++cnt]={x,head[y]},head[y]=cnt;}

#define L ch][0
#define R ch][1
int p[N], ch[N][2], r[N], st[N], top; _ sf[N], sb[N], so[N];
inline void up(int x) {
	x[sf] = x[sb] = x[so];
	if (x[L]) x[sf] = x[L][sf] + x[sf], x[sb] = x[sb] + x[L][sb];
	if (x[R]) x[sf] = x[sf] + x[R][sf], x[sb] = x[R][sb] + x[sb];
}
inline bool c(int x) { return x[p][R] == x; }
inline bool nr(int x) { return x[p][L] == x || x[p][R] == x; }
inline void rv(int x) { std::swap(x[L], x[R]), std::swap(x[sf], x[sb]), x[r] ^= 1; }
inline void pd(int x) { r[x] && (rv(x[L]), rv(x[R]), r[x] = 0); }
inline void rt(int x) {
	int y = x[p], z = y[p], k = c(x), w = x[ch][!k];
	(nr(y) && (z[ch][c(y)] = x)), p[p[p[ch[x[ch][!k] = y][k] = w] = y] = x] = z, up(y), up(x);
}
inline void sp(int x) {
	for (int i = st[top = 1] = x; nr(i); i = i[p]) st[++top] = i[p];
	while (top) pd(st[top--]);
	for (int y = x[p]; nr(x); rt(x), y = x[p]) nr(y) && (rt(c(x) ^ c(y) ? x : y), 0);
}
inline void ac(int x) { for (int i = 0; x; x = (i = x)[p]) sp(x), x[R] = i, up(x); }
inline void mr(int x) { ac(x), sp(x), rv(x); }
inline void spl(int x, int y) { mr(x), ac(y), sp(y); }
// clang-format on

u k;
inline u calc(u t0, u t1, u m) {
	u ans = 0;
	for (u i = k; i; i >>= 1) {
		if (!(t0 & i) && (t1 & i) && m >= i) ans |= i, m ^= i;
		if (t0 & i) ans |= i;
	}
	return ans;
}
void dfs(int x) {
	for (int i = head[x], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[p]) nx[p] = x, dfs(nx);
}

int n, m, op;
u x, y, z;
signed main() {
	get(n), get(m), get(k);
	k = 1ull << (k - 1);
	for (int i = 1; i <= n; i++) get(op), get(x), i[sf] = i[sb] = i[so] = $(op, x);
	for (int i = 1; i < n; i++) get(x), get(y), ad(x, y);
	dfs(1);
	while (m--) {
		get(op), get(x), get(y), get(z);
		if (op == 1)
			spl(x, y), prt(calc(y[sf].x, y[sf].y, z)), *oS++ = '\n';
		else
			sp(x), x[sf] = x[sb] = x[so] = $(y, z);
	}
	fwrite(oB, oS - oB, 1, stdout);
}