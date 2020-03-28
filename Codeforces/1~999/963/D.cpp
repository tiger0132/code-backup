#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 2e5 + 52;

struct SAM {
	struct graph {
		struct edge {
			int to, next;
		} e[N << 1];
		int head[N], cnt;
		void operator()(int x, int y) { e[++cnt] = (edge){y, x[head]}, x[head] = cnt; }
	} g;

	int n, link[N], len[N], tr[N][26], ed[N], nc, last;
	SAM() { nc = last = 1; }
	void ins(int c) {
		int cur = ++nc, p = last, q, cl;
		cur[len] = last[len] + 1;
		for (; p && !(q = p[tr][c]); p = p[link]) p[tr][c] = cur;
		if (!p)
			cur[link] = 1;
		else if (p[len] + 1 == q[len])
			cur[link] = q;
		else {
			cl = ++nc, cl[len] = p[len] + 1, cl[link] = q[link];
			memcpy(cl[tr], q[tr], sizeof *tr);
			for (; p && p[tr][c] == q; p = p[link]) p[tr][c] = cl;
			q[link] = cur[link] = cl;
		}
		cur[ed] = ++n, last = cur;
	}
	void operator=(char *s) {
		while (*s) ins(*s++ - 97);
		for (int i = 2; i <= nc; i++) g(i[link], i);
	}
	void dfs(int x, std::vector<int> &v) {
		if (x[ed]) v.push_back(x[ed]);
		for (int i = x[g.head]; i; i = g.e[i].next) dfs(g.e[i].to, v);
	}
	int operator()(char *s, int k) {
		std::vector<int> v;
		int x = 1, ans = 1e9, l = 0;
		for (; *s; x = x[tr][*s++ - 97], l++)
			if (!x[tr][*s - 97]) return -1;
		dfs(x, v);
		if ((int)v.size() < k) return -1;
		std::sort(v.begin(), v.end());
		for (int i = k - 1; i < (int)v.size(); i++)
			ans = std::min(ans, v[i] - v[i - k + 1] + l);
		return ans;
	}
} sam;

int n, m, x;
char s[N];
int main() {
	scanf("%s", s), n = strlen(s), sam = s;
	for (scanf("%d", &m); m--;) {
		scanf("%d%s", &x, s);
		printf("%d\n", sam(s, x));
	}
}