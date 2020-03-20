#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 1e6 + 61;

struct graph {
	struct edge {
		int to, next;
	} e[N];
	int head[N], cnt;
	void operator()(int x, int y) { e[++cnt] = (edge){y, x[head]}, x[head] = cnt; }
};

int fl;
struct SAM {
	int len[N], tr[N][27], link[N], cnt[N][3], nc, last;
	void ins(int c) {
		int cur = ++nc, p = last, q, cl;
		cur[len] = last[len] + 1;
		for (; p && !(q = p[tr][c]); p = p[link]) p[tr][c] = cur;
		if (!p)
			cur[link] = 1;
		else if (p[len] + 1 == q[len])
			cur[link] = q;
		else {
			cl = ++nc;
			cl[len] = p[len] + 1, cl[link] = q[link];
			memcpy(cl[tr], q[tr], sizeof *tr);
			for (; p && p[tr][c] == q; p = p[link]) p[tr][c] = cl;
			q[link] = cur[link] = cl;
		}
		cur[cnt][fl] = 1, last = cur;
	}
	void operator+=(char c) { ins(c - 97); }
	void operator+=(char *s) {
		while (*s) ins(*s++ - 97);
	}
	SAM() { nc = last = 1; }

	graph g;
	ll ans;
	void dfs(int x) {
		for (int i = x[g.head], nx; i; i = g.e[i].next)
			dfs(nx = g.e[i].to), x[cnt][1] += nx[cnt][1], x[cnt][2] += nx[cnt][2];
		if (x > 1) ans += 1ll * x[cnt][1] * x[cnt][2] * (x[len] - x[link][len]);
	}
	void solve() {
		for (int i = 2; i <= nc; i++) g(i[link], i);
		dfs(1);
		printf("%lld\n", ans);
	}
} sam;

char s[N];
int main() {
	scanf("%s", s), std::reverse(s, s + strlen(s)), fl = 1, sam += s;
	fl = 0, sam += '{';
	scanf("%s", s), std::reverse(s, s + strlen(s)), fl = 2, sam += s;
	sam.solve();
}