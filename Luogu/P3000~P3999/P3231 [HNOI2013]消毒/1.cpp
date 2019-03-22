#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#define L(x) ((x)*2 + 1)
#define R(x) ((x)*2 + 2)

const int N = 5e3 + 35, M = 5e4 + 45, INF = 0x3f3f3f3f;
struct edge {
	int to, next, w;
} e[M << 1];
int head[N], cnt = 1;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, head[x], z}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y], 0}, head[y] = cnt;
}

int lv[N];
bool bfs(int s, int t) {
	memset(lv, 0, sizeof lv);
	std::queue<int> q;
	lv[s] = 1;
	for (q.push(s); !q.empty(); q.pop()) {
		int x = q.front();
		for (int i = head[x]; i; i = e[i].next) {
			int nx = e[i].to;
			if (!e[i].w || lv[nx]) continue;
			lv[nx] = lv[x] + 1;
			if (nx == t) return 1;
			q.push(nx);
		}
	}
	return 0;
}
int dfs(int s, int t, int f) {
	if (s == t || !f) return f;
	int r = 0;
	for (int i = head[s]; f && i; i = e[i].next) {
		int nx = e[i].to;
		if (!e[i].w || lv[nx] != lv[s] + 1) continue;
		int tmp = dfs(nx, t, std::min(f, e[i].w));
		e[i].w -= tmp, e[i ^ 1].w += tmp;
		f -= tmp, r += tmp;
	}
	if (f) lv[s] = -1;
	return r;
}

struct node {
	int z, x, y;
};

int _, a, b, c, x, pos, ans;
std::vector<node> v;
int main() {
	for (scanf("%d", &_); _--;) {
		ans = INF, v.clear();
		scanf("%d%d%d", &a, &b, &c), pos = 3;
		if (a < b && a < c) pos = 1;
		if (b < a && b < c) pos = 2;
		for (int i = 1; i <= a; i++) {
			for (int j = 1; j <= b; j++) {
				for (int k = 1; k <= c; k++) {
					scanf("%d", &x);
					if (!x) continue;
					int i$ = i, j$ = j, k$ = k;
					if (pos == 2) std::swap(i$, j$);
					if (pos == 3) std::swap(i$, k$);
					v.push_back((node){i$, j$, k$});
				}
			}
		}
		if (pos == 2) std::swap(a, b);
		if (pos == 3) std::swap(a, c);
		for (int i = 0; i < (1 << a); i++) {
			memset(head, 0, sizeof head), cnt = 1;
			int lans = a - __builtin_popcount(i), mx = 0;
			for (node j : v) {
				mx = std::max(mx, std::max(j.x, j.y));
				if ((i >> (j.z - 1)) & 1) addedge(L(j.x), R(j.y), 1);
			}
			for (int j = 1; j <= mx; j++) {
				addedge(1, L(j), 1);
				addedge(R(j), 2, 1);
			}
			while (bfs(1, 2) && lans < ans) lans += dfs(1, 2, INF);
			ans = std::min(ans, lans);
		}
		printf("%d\n", ans);
	}
}