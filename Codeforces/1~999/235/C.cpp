#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e6 + 62;

struct graph {
	struct edge {
		int to, next;
	} e[N];
	int head[N], cnt;
	void operator()(int x, int y) { e[++cnt] = (edge){y, x[head]}, x[head] = cnt; }
};
struct SAM {
	int len[N], tr[N][26], link[N], cnt[N], nc, last;
	void ins(int c) {
		int cur = ++nc;
		cur[len] = last[len] + 1;
		int p = last, q, cl;
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
		cur[cnt] = 1, last = cur;
	}
	void operator+=(char c) { ins(c - 97); }
	void operator+=(char *s) {
		while (*s) ins(*s++ - 97);
	}
	SAM() { nc = last = 1; }

	graph g;
	void dfs(int x) {
		for (int i = x[g.head], nx; i; i = g.e[i].next)
			dfs(nx = g.e[i].to), x[cnt] += nx[cnt];
	}
	void build() {
		for (int i = 2; i <= nc; i++) g(i[link], i);
		dfs(1);
	}

	int vis[N];
	int calc(char *s) {
		static int tm = 1;
		int n = strlen(s), x = 1, l = 0, ans = 0;
		tm++;
		for (int i = 0; i < n; i++) {
			int nx = s[i] - 'a';
			while (x && !x[tr][nx]) l = len[x = x[link]];
			if (x[tr][nx]) l++, x = x[tr][nx];
		}
		if (l == n && x[vis] < tm) x[vis] = tm, ans += x[cnt];
		for (int i = 0; i < n - 1; i++) {
			int nx = s[i] - 'a';
			while (x && !x[tr][nx]) l = len[x = x[link]];
			if (x[tr][nx]) l++, x = x[tr][nx];

			if (l > n && --l == x[link][len]) x = x[link];
			if (l >= n && x[vis] < tm) x[vis] = tm, ans += x[cnt];
		}
		return ans;
	}
} sam;

char s[N];
int main() {
	scanf("%s", s);
	sam += s;
	sam.build();
	for (scanf("%*d"); ~scanf("%s", s);) printf("%d\n", sam.calc(s));
}