#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
#define L (x << 1)
#define R ((x << 1) | 1)
#define mid (l + r) / 2

const int N = 2e5 + 52;

struct rec {
	int *p, v;
};
std::stack<rec> st;
void set(int& x, int y) { st.push({&x, x}), x = y; }

int n, p[N], d[N];
int f(int x) { return x[p] ? f(x[p]) : x; }
void mg(int x, int y) {
	if ((x = f(x)) != (y = f(y))) {
		if (x[d] > y[d]) std::swap(x, y);
		set(x[p], y), set(y[d], y[d] + (x[d] == y[d]));
	}
}

std::vector<int> opr[N << 2];
int u[N], v[N], ql, qr;
void ins(int x, int l, int r, int v) {
	if (ql <= l && r <= qr) return x[opr].push_back(v);
	if (ql <= mid) ins(L, l, mid, v);
	if (mid < qr) ins(R, mid + 1, r, v);
}
void dfs(int x, int l, int r) {
	bool fl = true;
	int sz = st.size();
	for (int i : x[opr]) {
		int p = u[i], q = v[i];
		if (f(p) == f(q)) {
			for (int j = l; j <= r; j++) puts("No");
			goto end;
		}
		mg(p, q + n), mg(q, p + n);
	}
	if (l == r) return puts("Yes"), void();
	dfs(L, l, mid), dfs(R, mid + 1, r);
end:
	for (; st.size() > sz; st.pop()) *st.top().p = st.top().v;
}

int m, k, x, y;
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d%d", u + i, v + i, &x, &y);
		ql = x + 1, qr = y, ins(1, 1, k, i);
	}
	dfs(1, 1, k);
}