#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#define INIT(x, l0, r0, h0, t0, msk0, pre0, nxt0)                             \
	x[l] = l0, x[r] = r0, x[h] = h0, x[t] = t0, x[msk] = msk0, x[pre] = pre0, \
	x[nxt] = nxt0

const int N = 6e5 + 56;
int p[N];
int f(int x) { return x[p] ? x[p] = f(x[p]) : x; }

int l[N], r[N], h[N], t[N], msk[N], pre[N], nxt[N];
std::vector<int> v[N][4];
int cnt[N][4], T, m, nc;
inline int curH(int x) { return x[h] + cnt[T][x[msk]] - cnt[x[t]][x[msk]]; }
inline void updMsk(int x) {
	x[msk] =
		(x[pre] && curH(x[pre]) > curH(x)) | ((x[nxt] && curH(x) < curH(x[nxt])) << 1);
}
void calc(int x) {
	int dt = abs(curH(x) - curH(x[nxt])), state = x[msk] ^ x[nxt][msk];
	if (state && dt && cnt[T][state] + dt <= m) v[cnt[T][state] + dt][state].push_back(x);
}
void merge(int x) {
	int cur_h = curH(x = f(x));
	if (!x || !x[nxt]) return;
	if (curH(x[nxt]) != cur_h) return;
	int node = ++nc, y = x[nxt];
	f(y)[p] = f(x)[p] = node;
	INIT(node, x[l], y[r], cur_h, T, 0, x[pre], y[nxt]);
	if (x[pre]) x[pre][nxt] = node;
	if (y[nxt]) y[nxt][pre] = node;
	updMsk(node);
	if (node[pre]) calc(node[pre]);
	if (node[nxt]) calc(node);
}

char s[N];
int n;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, x; i <= n; i++) {
		scanf("%d", &x);
		if (nc[h] == x) {
			nc[r] = i;
			continue;
		}
		if (nc) nc[nxt] = nc + 1;
		nc++;
		INIT(nc, i, i, x, 0, 0, nc - 1, 0);
	}
	for (int i = 1; i <= nc; i++) updMsk(i);
	for (int i = 1; i < nc; i++) calc(i);
	scanf("%s", s + 1);
	for (T = 1; T <= m; T++) {
		cnt[T][1] = cnt[T - 1][1] + (s[T] == 'A');
		cnt[T][2] = cnt[T - 1][2] + (s[T] == 'B');
		cnt[T][3] = cnt[T - 1][3] + 1;
		for (int i = 1; i <= 3; i++)
			for (int j : v[cnt[T][i]][i]) merge(j);
	}
	T = m;
	for (int i = f(1); i; i = i[nxt])
		for (int j = i[l]; j <= i[r]; j++) printf("%d ", curH(i), " \n"[j == n]);
}