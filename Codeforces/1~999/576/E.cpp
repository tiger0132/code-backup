#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
#define L ((x) << 1)
#define R (((x) << 1) | 1)
#define mid (l + r) / 2

const int N = 1e6 + 61, K = 55;

struct rec {
	int &p, v;
};
std::stack<rec> st;
void set(int& x, int y) { st.push({x, x}), x = y; }

struct __dsu {
	int p[N], d[N];
	int f(int x) { return x[p] ? f(x[p]) : x; }
	__dsu& mg(int x, int y) {
		if ((x = f(x)) != (y = f(y))) {
			if (x[d] > y[d]) std::swap(x, y);
			set(x[p], y), set(y[d], y[d] + (x[d] == y[d]));
		}
		return *this;
	}
	bool con(int x, int y) { return f(x) == f(y); }
} dsu[K];

int u[N], v[N], ed[N], col[N], cur[N];
std::vector<int> opr[N << 2];
int n, ql, qr;

void ins(int x, int l, int r, int y) {
	if (ql <= l && r <= qr) return x[opr].push_back(y);
	if (ql <= mid) ins(L, l, mid, y);
	if (mid < qr) ins(R, mid + 1, r, y);
}
void dfs(int x, int l, int r) {
	int sz = st.size();
	for (int i : x[opr]) {
		int p = u[ed[i]], q = v[ed[i]];
		dsu[col[i]].mg(p, q + n).mg(p + n, q);
	}
	if (l == r)
		if (dsu[col[l]].con(u[ed[l]], v[ed[l]]))
			puts("NO"), col[l] = cur[ed[l]];
		else
			puts("YES"), cur[ed[l]] = col[l];
	else
		dfs(L, l, mid), dfs(R, mid + 1, r);
	for (; st.size() > sz; st.pop()) st.top().p = st.top().v;
}

int m, k, q, tmp[N];
int main() {
	scanf("%d%d%d%d", &n, &m, &k, &q);
	for (int i = 1; i <= m; i++) scanf("%d%d", u + i, v + i), i[tmp] = q + 1;
	for (int i = 1; i <= q; i++) scanf("%d%d", ed + i, col + i);
	for (int i = q; i >= 1; i--) {
		if (i < ed[i][tmp] - 1) ql = i + 1, qr = ed[i][tmp] - 1, ins(1, 1, q, i);
		ed[i][tmp] = i;
	}
	dfs(1, 1, q);
}