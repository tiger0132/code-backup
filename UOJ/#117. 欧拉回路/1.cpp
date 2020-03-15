#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>

const int N = 2e5 + 52;
struct edge {
	int to, next;
} e[N << 1];
int head[N], ind[N], oud[N], cnt = 1;
void addedge(int x, int y) { e[++cnt] = (edge){y, x[head]}, x[head] = cnt; }

std::stack<int> st;
int vis[N];
void dfs1(int x) {
	for (int &i = x[head], t; i; i = e[i].next)
		if (!(i / 2)[vis])
			(i / 2)[vis] = 1, dfs1(e[t = i].to), st.push(t & 1 ? -t / 2 : t / 2);
}
void dfs2(int x) {
	for (int &i = x[head], t; i; i = e[i].next)
		if (!i[vis]) i[vis] = 1, dfs2(e[t = i].to), st.push(t - 1);
}

int t, n, m, x, y;
int main() {
	for (scanf("%d%d%d", &t, &n, &m); ~scanf("%d%d", &x, &y);) {
		addedge(x, y);
		y[ind]++, x[oud]++;
		if (t == 1) y[oud]++, addedge(y, x);
	}
	if (t == 1) {
		for (int i = 1; i <= n; i++)
			if (i[oud] % 2) return puts("NO"), 0;
	} else
		for (int i = 1; i <= n; i++)
			if (i[oud] != i[ind]) return puts("NO"), 0;
	(t == 1 ? dfs1 : dfs2)(x);
	if (st.size() != m) return puts("NO"), 0;
	for (puts("YES"); !st.empty(); st.pop()) printf("%d ", st.top());
}