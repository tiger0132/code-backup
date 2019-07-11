#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>

const int N = 1e5 + 51;

// clang-format off
#define M1(a,b)a
#define L ch][0
#define R ch][1
int p[N], ch[N][2], r[N], t[N], v[N], s[N], st[N], top;
void up(int x) { x[s] = x[L][s] + x[R][s] + x[v]; }
bool c(int x) { return x[p][R] == x; }
bool nr(int x) { return x[p][L] == x || x[p][R] == x; }
void rv(int x) { std::swap(x[L], x[R]), x[r] ^= 1; }
void set(int x) { x[s] = x[v] = 0, t[x] = 1; }
void pd(int x) { x[r] && (rv(x[L]), rv(x[R]), x[r] = 0), x[t] && (set(x[L]), set(x[R]), x[t] = 0); }
void rt(int x) {
	int y = x[p], z = y[p], k = c(x), w = x[ch][!k];
	(nr(y) && (z[ch][c(y)] = x)), p[p[p[ch[ch[x][!k] = y][k] = w] = y] = x] = z, up(y), up(x);
}
void sp(int x) {
	for (int i = st[top = 1] = x; i; i = i[p]) st[++top] = i[p];
	while (top) pd(st[top--]);
	for (int y = x[p]; nr(x); rt(x), y = x[p]) nr(y) && (rt(c(x) ^ c(y) ? x : y), 0);
}
void ac(int x) { for (int i = 0; x; x = (i = x)[p]) sp(x), x[R] = i, up(x); }
void mr(int x) { ac(x), sp(x), rv(x); }
void spl(int x, int y) { mr(x), ac(y), sp(y); }
void lnk(int x, int y) { mr(x), x[p] = y, up(y); }
int _[N];int f(int x){return _[x]?_[x]=f(_[x]):x;}void $(int x,int y){(x=f(x))^(y=f(y))&&(_[x]=y);}
// clang-format on

struct edge {
	int x, y;
	bool f;
} e[N];
struct query {
	int op, x, y, ans;
} q[N];

int n;
int id(int x, int y) { return (x - 1) * n + y; }
void go(int x, int y) {
	static int ec = 5e4;
	if (f(x) ^ f(y))
		ec[v] = ec[s] = 1, lnk(x, ec), lnk(ec, y), $(x, y), ec++;
	else
		spl(x, y), set(y);
}

std::map<int, int> mp;
int m, cnt, op, x, y;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d%d", &x, &y), e[i] = {x, y, true}, mp[id(x, y)] = i;
	while (scanf("%d%d%d", &op, &x, &y) == 3) {
		q[++cnt] = {op, x, y};
		if (!op) e[mp[id(x, y)]].f = false;
	}
	for (int i = 1; i <= m; i++)
		if (e[i].f) go(e[i].x, e[i].y);
	for (int i = cnt; i >= 1; i--) {
		op = q[i].op, x = q[i].x, y = q[i].y;
		if (op)
			spl(x, y), q[i].ans = y[s];
		else
			go(x, y);
	}
	for (int i = 1; i <= cnt; i++)
		if (q[i].op) printf("%d\n", q[i].ans);
}