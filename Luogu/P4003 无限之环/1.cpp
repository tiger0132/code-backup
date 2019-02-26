#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#define U b + 0
#define R b + 1
#define D b + 2
#define L b + 3
#define $(x, y, c) addedge(x, y, 1, c, s)

const int N = 4e4 + 44, M = 1e5 + 51, INF = 0x3f3f3f3f;

struct edge {
	int to, next, w, c;
} e[M << 1];
static int head[N], cnt = 1;
inline void addedge(int x, int y, int z, int w, int rev) {
	if (rev == 2) std::swap(x, y);
	e[++cnt] = (edge){y, head[x], z, w}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y], 0, -w}, head[y] = cnt;
}
int i, j;
inline void ek(int s, int t, int& n, int& m) {
	static int dis[N], vis[N], pre[N], flow[N];
	std::queue<int> q;
	n = m = 0;
	while ("https://ac.tiger0132.tk") {
		memset(dis, 0x3f, sizeof dis);
		flow[s] = INF, dis[s] = 0;
		for (q.push(s); !q.empty(); q.pop()) {
			int x = q.front();
			vis[x] = 0;
			for (i = head[x]; i; i = e[i].next) {
				int nx = e[i].to;
				if (e[i].w && dis[nx] > dis[x] + e[i].c) {
					flow[nx] = std::min(flow[x], e[i].w);
					dis[nx] = dis[x] + e[i].c;
					pre[nx] = i;
					if (!vis[nx]) q.push(nx), vis[nx] = 1;
				}
			}
		}
		if (dis[t] == INF) return;
		for (i = pre[t]; i; i = pre[e[i ^ 1].to]) {
			e[i].w -= flow[t];
			e[i ^ 1].w += flow[t];
		}
		n += flow[t];
		m += flow[t] * dis[t];
	}
}

int n, m;
inline int id(int x, int y) { return ((x - 1) * m + y) * 4; }
int x, s, b, c$;
int main() {
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			scanf("%d", &x);
			s = (i + j + 1) % 2 + 1;
			b = id(i, j);

			if ((i + j) & 1) {
				if (i + 1 <= n) addedge(id(i + 1, j) + 0, D, 1, 0, 3 - s);  // U YOU
				if (j - 1 >= 1) addedge(id(i, j - 1) + 1, L, 1, 0, 3 - s);  // R ARE
				if (i - 1 >= 1) addedge(id(i - 1, j) + 2, U, 1, 0, 3 - s);  // D DU
				if (j + 1 <= m) addedge(id(i, j + 1) + 3, R, 1, 0, 3 - s);  // L LIU
			}

			c$ += __builtin_popcount(x);
			if (x & 1) $(s, U, 0);
			if (x & 2) $(s, R, 0);
			if (x & 4) $(s, D, 0);
			if (x & 8) $(s, L, 0);
			// clang-format off
            switch (x) {
                case 1:  $(U, L, 1); $(U, R, 1); $(U, D, 2); break;  // ↑
                case 2:  $(R, U, 1); $(R, D, 1); $(R, L, 2); break;  // →
                case 4:  $(D, L, 1); $(D, R, 1); $(D, U, 2); break;  // ↓
                case 8:  $(L, U, 1); $(L, D, 1); $(L, R, 2); break;  // ←

                case 3:  $(U, D, 1); $(R, L, 1); break;  // └
                case 6:  $(D, U, 1); $(R, L, 1); break;  // ┌
                case 9:	 $(U, D, 1); $(L, R, 1); break;  // ┘
                case 12: $(D, U, 1); $(L, R, 1); break;  // ┐

                case 7:  $(U, L, 1); $(D, L, 1); $(R, L, 2); break;  // ├
                case 11: $(L, D, 1); $(R, D, 1); $(U, D, 2); break;  // ┴
                case 13: $(U, R, 1); $(D, R, 1); $(L, R, 2); break;  // ┤
                case 14: $(L, U, 1); $(R, U, 1); $(D, U, 2); break;  // ┬
            }
			// clang-format on
		}
	}
	ek(1, 2, s, b);
	printf("%d", 2 * s == c$ ? b : -1);
}