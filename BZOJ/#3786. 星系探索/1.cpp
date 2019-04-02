#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

const int N = 2e5 + 52;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt2;
void addedge(int x, int y) {
	e[++cnt2] = (edge){y, head[x]}, head[x] = cnt2;
	e[++cnt2] = (edge){x, head[y]}, head[y] = cnt2;
}

// clang-format off
#define L(x) ch[x][0]
#define R(x) ch[x][1]
int ch[N][2], p[N], v[N], cnt[N], sgn[N], sum[N], tag[N], root;
int $(int id, int x, int y) {
	v[id] = sum[id] = x, sgn[id] = cnt[id] = y;
	return id;
}
int c(int x) { return R(p[x]) == x; }
void up(int x) {
	sum[x] = sum[L(x)] + sum[R(x)] + v[x];
	cnt[x] = cnt[L(x)] + cnt[R(x)] + sgn[x];
}
void set(int x, int y) { tag[x] += y, sum[x] += cnt[x] * y, v[x] += sgn[x] * y; }
void down(int x) { set(L(x), tag[x]), set(R(x), tag[x]), tag[x] = 0; }
void rt(int x) {
	int y = p[x], z = p[y], k = c(x), w = ch[x][!k];
	down(y), down(x), ch[y][k] = w, p[w] = y, ch[z][c(y)] = x, p[x] = z, ch[x][!k] = y, p[y] = x, up(y), up(x);
}
void sp(int x, int g = 0) {
	for (int y = p[x]; y != g; rt(x), y = p[x]) if (p[y] != g) rt(c(x) == c(y) ? y : x); if (!g) root = x;
}
int build(int l, int r, int *a, int *b) {
	if (l > r) return 0;
	int mid = (l + r) / 2, cur = $(mid, a[mid], b[mid]);
	if (l == r) return cur;
	if (L(cur) = build(l, mid - 1, a, b)) p[L(cur)] = cur;
	if (R(cur) = build(mid + 1, r, a, b)) p[R(cur)] = cur;
	return up(cur), cur;
}
int pre(int x, int f) { for (sp(x), x = ch[x][f]; ch[x][!f];) x = ch[x][!f]; return x; }
int query(int x) { sp(x); return sum[L(x)] + v[x]; }
// clang-format on

int src[N], a[N], b[N], l[N], r[N], idx;
void dfs(int x, int p) {
	a[l[x] = ++idx] = src[x], b[idx] = 1;
	for (int i = head[x], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) dfs(nx, x);
	a[r[x] = ++idx] = -src[x], b[idx] = -1;
}
int move(int L, int R) {
	int x, y, z;
	x = pre(l[L], 0), y = pre(r[L], 1), sp(x), sp(y, x), z = L(y);
	L(y) = 0, up(y), up(x);
	x = l[R], y = pre(l[R], 1), sp(x), sp(y, x);
	L(y) = z, p[z] = y, up(y), up(x);
}
void add(int L, int R, int w) {
	int x = pre(L, 0), y = pre(R, 1);
	sp(x), sp(y, x), set(L(y), w), up(y), up(x);
}

int n, m, x, y;
char op[2];
signed main() {
	// freopen("1.in", "r", stdin);
	// freopen("1.out", "w", stdout);
	scanf("%lld", &n);
	for (int i = 2; i <= n; i++) scanf("%lld", &x), addedge(i, x);
	for (int i = 1; i <= n; i++) scanf("%lld", src + i);
	idx++, dfs(1, 0), idx++;
	root = build(1, idx, a, b);
	for (scanf("%lld", &m); m--;) {
		scanf("%s%lld", op, &x);
		switch (*op) {
			case 'Q':
				printf("%lld\n", query(l[x]));
				break;
			case 'C':
				scanf("%lld", &y);
				move(x, y);
				break;
			case 'F':
				scanf("%lld", &y);
				add(l[x], r[x], y);
				break;
		}
	}
}