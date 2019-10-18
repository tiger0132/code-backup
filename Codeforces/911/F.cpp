#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>

typedef long long ll;
const int N = 2e5 + 52;
struct node {
	int x, y, z;
};
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
}

std::queue<int> ord;
std::stack<int> st;
int mx, mi, v[N];
void dfs(int x, int p, int d, int *dep) {
	if ((x[dep] = d) > mx) mx = d, mi = x;
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) dfs(nx, x, d + 1, dep);
}
bool dfs2(int x, int p, int dest) {
	if (x == dest) return x[v] = true;
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p && dfs2(nx, x, dest)) return st.push(x), x[v] = true;
	return false;
}
void dfs3(int x, int p) {
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) dfs3(nx, x);
	ord.push(x);
}

int p, q, n, x, y, d0[N], d1[N];
std::queue<node> out;
ll ans;
int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) scanf("%d%d", &x, &y), addedge(x, y);
	dfs(1, 0, 0, d0), p = mi, mx = mi = 0;
	dfs(p, 0, 0, d0), q = mi;
	dfs(q, 0, 0, d1);
	dfs2(p, 0, q), dfs3(p, 0);
	for (int i; !ord.empty(); ord.pop())
		if (!(i = ord.front())[v])
			out.push({i, i[d0] < i[d1] ? q : p, i}), ans += std::max(i[d0], i[d1]);
	for (; !st.empty(); st.pop()) {
		out.push({st.top(), q, st.top()});
		ans += st.size();
	}
	printf("%lld\n", ans);
	for (; !out.empty(); out.pop())
		printf("%d %d %d\n", out.front().x, out.front().y, out.front().z);
}