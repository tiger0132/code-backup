#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

// clang-format off
#define L ch][0
#define R ch][1
const int N = 1e6 + 61;
int p[N], ch[N][2], v[N], la[N], ra[N], gss[N], s[N], sz[N], set[N], r[N], nc, root;
std::queue<int> q;
int alloc(int y) {
	int x; if (q.empty()) x = ++nc; else x = q.front(), q.pop();
	return x[L] = x[R] = x[p] = 0, x[v] = x[s] = x[gss] = y, x[la] = x[ra] = std::max(0, y), x[set] = x[r] = 0, x[sz] = 1, x;
}
void up(int x) {
	x[sz] = x[L][sz] + x[R][sz] + 1, x[s] = x[L][s] + x[R][s] + x[v];
	x[la] = std::max(x[L][la], x[L][s] + x[v] + x[R][la]);
	x[ra] = std::max(x[L][ra] + x[v] + x[R][s], x[R][ra]);
	x[gss] = std::max(std::max(x[L][gss], x[R][gss]), x[L][ra] + x[v] + x[R][la]);
}
bool c(int x) { return x[p][R] == x; }
void put(int x, int y) {
	if (x) x[v] = y, x[set] = 1, x[la] = x[ra] = std::max(0, x[s] = x[sz] * y), x[gss] = x[v] < 0 ? x[v] : x[s];
}
void rv(int x) { std::swap(x[L], x[R]), std::swap(x[la], x[ra]), x[r] ^= 1; }
void pd(int x) {
	if (x[set]) put(x[L], x[v]), put(x[R], x[v]), x[set] = x[r] = 0; if (x[r]) rv(x[L]), rv(x[R]), x[r] = 0;
}
void rt(int x) {
	int y = x[p], z = y[p], k = c(x), w = ch[x][!k];
	ch[z][c(y)] = x, p[p[p[ch[ch[x][!k] = y][k] = w] = y] = x] = z, up(y), up(x);
}
void sp(int x, int g = 0) {
	for (int y = x[p]; x[p] != g; rt(x), y = x[p]) y[p] != g && (rt(c(x) == c(y) ? y : x), 0); g || (root = x);
}
int kth(int x, int k) {
	if (pd(x), (x[L] && k <= x[L][sz])) return kth(x[L], k);
	return k == x[L][sz] + 1 ? x : kth(x[R], k - x[L][sz] - 1);
}
int spl(int ql, int qr) { int pp = kth(root, ql), qq = kth(root, qr + 2); return sp(pp), sp(qq, pp), qq; }
void ins(int x, int y) { int qq = spl(x + 1, x); qq[L] = y, y[p] = qq, up(qq), up(root); }
int build(int ql, int qr, int *ar) {
	if (ql > qr) return 0;
	int m = (ql + qr) / 2, x = alloc(ar[m]);
	if (ql == qr) return x;
	if (x[L] = build(ql, m - 1, ar)) x[L][p] = x;
	if (x[R] = build(m + 1, qr, ar)) x[R][p] = x;
	return up(x), x;
}
void rm(int x) { if (x) rm(x[L]), rm(x[R]), q.push(x); }
// clang-format on

int n, m, x, y, z, qq, a[N];
char op[11];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 2; i <= n + 1; i++) scanf("%d", i + a);
	0 [a] = 0 [gss] = 1 [a] = (n += 2)[a] = -1e9;
	root = build(1, n, a);
	while (~scanf("%s", op))
		if (op[2] == 'X')
			printf("%d\n", root[gss]);
		else {
			scanf("%d%d", &x, &y);
			if (op[2] == 'S') {
				memset(a, 0, sizeof a);
				for (int i = 1; i <= y; i++) scanf("%d", a + i);
				ins(x, build(1, y, a));
			} else {
				qq = spl(x, x + y - 1);
				if (op[2] == 'T')
					printf("%d\n", qq[L][s]);
				else if (op[2] == 'V')
					rv(qq[L]), up(qq), up(root);
				else if (op[2] == 'K')
					scanf("%d", &z), put(qq[L], z), up(qq), up(root);
				else
					rm(qq[L]), qq[L] = 0, up(qq), up(root);
			}
		}
}