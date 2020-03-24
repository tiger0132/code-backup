#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>

typedef std::pair<int, int> pii;
const int N = 1e5 + 51, LN = 20;

struct G {
	struct edge {
		int to, next;
	} e[N << 1];
	int head[N], cnt, idx;
	void clear() { memset(head, 0, sizeof head), cnt = idx = 0; }
	void operator()(int x, int y) { e[++cnt] = (edge){y, x[head]}, x[head] = cnt; }

	int occ[N << 1];
	pii st[N << 1][LN];
	void dfs(int x, int p = 0, int d = 0) {
		st[x[occ] = ++idx][0] = {d, x};
		for (int i = x[head], nx; i; i = e[i].next)
			if ((nx = e[i].to) != p) dfs(nx, x, d + 1), st[++idx][0] = {d, x};
	}
	void init() {
		dfs(1);
		for (int j = 1; (1 << j) <= idx; j++)
			for (int i = 1; i + (1 << j) - 1 <= idx; i++)
				st[i][j] = std::min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
	}
	int lca(int x, int y) {
		int l = x[occ], r = y[occ];
		if (l > r) std::swap(l, r);
		int k = 31 - __builtin_clz(r - l + 1);
		return std::min(st[l][k], st[r - (1 << k) + 1][k]).second;
	}
};

struct SAM {
	int len[N], tr[N][27], link[N], pre[N], nc, ll, last;
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
		pre[ll++] = last = cur;
	}
	void clear() {
		memset(len, 0, sizeof len);
		memset(tr, 0, sizeof tr);
		memset(link, 0, sizeof link);
		memset(pre, 0, sizeof pre);
		nc = last = 1, ll = 0;
	}
	void operator=(char* s) {
		for (clear(); *s;) ins(*s++ - 97);
	}
	void build(G& g) {
		for (int i = 2; i <= nc; i++) g(i[link], i);
		g.init();
	}
} sam, samr;

int _, n, A[N], B[N];
long long ans;
char s[N];
G g, gr;
int main() {
	for (scanf("%d", &_); _--; ans = 0) {
		scanf("%s", s), n = strlen(s);
		sam = s, sam.build(g);
		std::reverse(s, s + n);
		samr = s, samr.build(gr);
		for (int i = 1; i <= n / 2; i++)
			for (int j = 0; j + i < n; j += i) {
				int k = j + i, lp = 1e9, rp = -1e9;
				if (j >= 0)
					lp = std::max(k - g.lca(sam.pre[j], sam.pre[k])[sam.len] + 1, j + 1);
				if (k < n)
					rp = std::min(
						j + gr.lca(samr.pre[n - j - 1], samr.pre[n - k - 1])[samr.len],
						k);
				if (lp <= rp) {
					A[lp + i - 1]++, A[rp + i]--;
					B[lp - i]++, B[rp - i + 1]--;
				}
			}
		for (int i = 1; i < n; i++) A[i] += A[i - 1], B[i] += B[i - 1];
		for (int i = 0; i < n - 1; i++) ans += 1ll * A[i] * B[i + 1];
		printf("%lld\n", ans);
		memset(A, 0, sizeof A);
		memset(B, 0, sizeof B);
		g.clear(), gr.clear();
	}
}