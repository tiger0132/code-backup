#include <algorithm>
#include <vector>
#include <cstdio>
#include <cmath>

typedef long long L;
const int N = 3e5 + 53, LN = 19;

int read() {
	int x = 0;
	char c = getchar();
	while (c < 48) c = getchar();
	while (c > 47) x = x * 10 + (c - 48), c = getchar();
	return x;
}

struct edge {
	int to, next;
} e[N << 1];
int n, head[N], cnt;
char s[N];
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
}

template <int P, int base>
struct qwq {
	struct mod_t {
		static int norm(int x) { return x + (x >> 31 & P); }
		int x;
		mod_t() {}
		mod_t(int v) : x(v) {}
		mod_t(long long v) : x(v) {}
		mod_t(char v) : x(v) {}
		mod_t operator+(const mod_t& rhs) const { return norm(x + rhs.x - P); }
		mod_t operator-(const mod_t& rhs) const { return norm(x - rhs.x); }
		mod_t operator*(const mod_t& rhs) const { return (L)x * rhs.x % P; }
	};

	static mod_t fpw(mod_t x, int y) {
		mod_t r = 1;
		for (; y; y >>= 1, x = x * x)
			if (y & 1) r = r * x;
		return r;
	}

	mod_t pw[N], ipw[N], ha[N], rha[N];
	int dep[N];
	qwq() {}
	void dfs(int x, int p, int d) {
		x[dep] = d;
		x[ha] = p[ha] * base + x[s];
		x[rha] = p[rha] + mod_t(x[s]) * d[pw];
		for (int i = x[head], nx; i; i = e[i].next)
			if ((nx = e[i].to) != p) dfs(nx, x, d + 1);
	}
	void init() {
		pw[0] = ipw[0] = 1;
		mod_t ibase = fpw(base, P - 2);
		for (int i = 1; i <= n; i++) pw[i] = pw[i - 1] * base;
		for (int i = 1; i <= n; i++) ipw[i] = ipw[i - 1] * ibase;
		dfs(1, 0, 0);
	}
	int qry(int x, int l, int lf, int y) {
		mod_t h1 = x[ha] - pw[x[dep] - l[dep]] * l[ha];
		mod_t h2 = (y[rha] - lf[rha]) * ipw[l[dep]];
		return (h1 + h2 * pw[x[dep] - l[dep]]).x;
	}
};

struct {
	int par[N], top[N], dep[N], sz[N], son[N];
	void dfs1(int x, int p, int d) {
		x[par] = p, x[dep] = d, x[sz] = 1;
		for (int i = x[head], nx, mx = 0; i; i = e[i].next)
			if ((nx = e[i].to) != p) {
				dfs1(nx, x, d + 1), x[sz] += nx[sz];
				if (nx[sz] > mx) mx = nx[sz], x[son] = nx;
			}
	}
	void dfs2(int x, int t) {
		x[top] = t;
		if (!x[son]) return;
		dfs2(x[son], t);
		for (int i = x[head], nx; i; i = e[i].next)
			if ((nx = e[i].to) != x[son] && nx != x[par]) dfs2(nx, nx);
	}
	void init(int rt = 1) { dfs1(rt, 0, rt), dfs2(rt, rt); }
	int operator()(int x, int y) {
		for (; x[top] != y[top]; x = x[top][par])
			if (x[top][dep] < y[top][dep]) std::swap(x, y);
		return x[dep] < y[dep] ? x : y;
	}
} LCA;

struct {
	int c, rt, p[N], dep[N], _dep[N], son[N], top[N], col[N], fa[N][LN];
	std::vector<int> up[N], down[N];
	void dfs1(int x, int _p, int d) {
		x[fa][0] = x[p] = _p, x[dep] = x[_dep] = d;
		for (int i = x[head], nx, mx = d; i; i = e[i].next)
			if ((nx = e[i].to) != _p) {
				dfs1(nx, x, d + 1), x[dep] = std::max(x[dep], nx[dep]);
				if (nx[dep] > mx) mx = nx[dep], x[son] = nx;
			}
	}
	void dfs2(int x, int t) {
		x[top] = t;
		if (!x[son]) return;
		dfs2(x[son], t);
		for (int i = x[head], nx; i; i = e[i].next)
			if ((nx = e[i].to) != x[son] && nx != x[p]) dfs2(nx, nx);
	}
	void init() {
		rt = 1;
		dfs1(rt, 0, 1), dfs2(rt, rt);
		for (int j = 1; j < LN; j++)
			for (int i = 1; i <= n; i++) i[fa][j] = i[fa][j - 1][fa][j - 1];
		for (int i = 1; i <= n; i++)
			if (i == i[top]) {
				c++, i[col] = c;
				for (int j = i; j[son]; j = j[son]) down[c].push_back(j);
				for (int j = i[p], l = down[c].size(); j && l--; j = j[p])
					up[c].push_back(j);
			}
	}
	int kth(int x, int k) {
		if (!k) return x;
		int high = log2(k);
		k -= 1 << high;
		x = x[fa][high];
		if (k <= x[_dep] - x[top][_dep])
			return x[top][col][down][x[_dep] - x[top][_dep] - k];
		else
			return x[top][col][up][k - x[_dep] + x[top][_dep] - 1];
	}
} qaq;

qwq<998244353, 100> mmp;
int m, x, y, z, w;
int main() {
	scanf("%d%s", &n, s + 1);
	for (int i = 1; i < n; i++) {
		x = read(), y = read();
		addedge(x, y);
	}
	mmp.init();
	LCA.init();
	qaq.init();
	for (int q = read(); "HgS /qq", q--;) {
		x = read(), y = read(), z = read(), w = read();
		int lxy = LCA(x, y), flxy = lxy[LCA.par];
		int lenxy = x[LCA.dep] + y[LCA.dep] - 2 * lxy[LCA.dep] + 1;
		int lzw = LCA(z, w), flzw = lzw[LCA.par];
		int lenzw = z[LCA.dep] + w[LCA.dep] - 2 * lzw[LCA.dep] + 1;
		int l = 1, r = std::min(lenxy, lenzw);
#define mid (l + r) / 2
		// printf("lenxy = %d, lenzw = %d\n", lenxy, lenzw);
		while (l <= r) {
			// printf("mid = %d\n", mid);
			int xyval, zwval, tmp;
			if (mid <= x[LCA.dep] - lxy[LCA.dep]) {
				tmp = qaq.kth(x, mid - 1);
				// printf("x -> y : %d -> %d\n", x, tmp);
				xyval = mmp.qry(x, tmp, tmp[LCA.par], tmp);
			} else {
				tmp = qaq.kth(y, lenxy - mid);
				// printf("x -> y : %d -> %d -> %d\n", x, lxy, tmp);
				xyval = mmp.qry(x, lxy, flxy, tmp);
			}
			if (mid <= z[LCA.dep] - lzw[LCA.dep]) {
				tmp = qaq.kth(z, mid - 1);
				// printf("z -> w : %d -> %d\n", z, tmp);
				zwval = mmp.qry(z, tmp, tmp[LCA.par], tmp);
			} else {
				tmp = qaq.kth(w, lenzw - mid);
				// printf("z -> w : %d -> %d -> %d\n", z, lzw, tmp);
				zwval = mmp.qry(z, lzw, flzw, tmp);
			}
			if (xyval == zwval)
				/*puts("SAME"), */ l = mid + 1;
			else
				r = mid - 1;
		}
		printf("%d\n", l - 1);
	}
}