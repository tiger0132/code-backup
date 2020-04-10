#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <vector>

#pragma region IO
namespace IO {
#ifdef __unix__
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

struct in_t {
#ifdef LOCAL_QWQ
	inline in_t() {}
	inline in_t(const char *path) { freopen(path, "r", stdin); }
	inline char gc() { return getchar(); }
#elif __unix__
	struct stat st;
	char *ptr;
	int fd;
	inline in_t() {
		fd = fileno(stdin), fstat(fd, &st),
		ptr = (char *)mmap(0, st.st_size, 1, 2, fd, 0);
	}
	inline in_t(const char *path) {
		fd = open(path, O_RDONLY), fstat(fd, &st),
		ptr = (char *)mmap(0, st.st_size, 1, 2, fd, 0);
	}
	inline char gc() { return *ptr++; }
#else
	static const int SZ = 1 << 20;
	char buf[SZ], *s, *t;
	inline in_t() {}
	inline in_t(const char *path) { freopen(path, "r", stdin); }
	inline char gc() {
		if (s == t) t = (s = buf) + fread(buf, 1, SZ, stdin);
		return s == t ? ' ' : *s++;
	}
#endif
	template <typename T>
	void readU(T &x) {
		x = 0;
		char c = gc();
		while (c < '0') c = gc();
		for (; c >= '0'; c = gc()) x = x * 10 + (c & 15);
	}
	template <typename T>
	void readI(T &x) {
		x = 0;
		bool f = 0;
		char c = gc();
		for (; c < '0'; c = gc())
			if (c == '-') f = 1;
		for (; c >= '0'; c = gc()) x = x * 10 + (c & 15);
		if (f) x = -x;
	}
	template <typename T>
	void readF(T &x) {
		T tmp = 1;
		bool f = 0;
		char c = gc();
		x = 0;
		for (; c < '0'; c = gc())
			if (c == '-') f = 1;
		for (; c >= '0'; c = gc()) x = x * 10 + (c & 15);
		if (c == '.')
			for (c = gc(); c >= '0'; c = gc()) tmp /= 10, x += tmp * (c & 15);
		if (f) x = -x;
	}

#define READ_DEF(type, func) \
	in_t &operator>>(type &x) { return func(x), *this; };
#ifdef __x86_64__
#define READ_DEF_X64(type, func) READ_DEF(type, func)
#else
#define READ_DEF_X64(type, func)
#endif

	READ_DEF(signed short, readI);
	READ_DEF(signed int, readI);
	READ_DEF(signed long, readI);
	READ_DEF(signed long long, readI);
	READ_DEF_X64(signed __int128, readI);

	READ_DEF(unsigned short, readU);
	READ_DEF(unsigned int, readU);
	READ_DEF(unsigned long, readU);
	READ_DEF(unsigned long long, readU);
	READ_DEF_X64(unsigned __int128, readU);

	READ_DEF(float, readF);
	READ_DEF(double, readF);
	READ_DEF(__float128, readF);

	in_t &operator>>(char &c) {
		for (c = gc(); c <= ' ';) c = gc();
		return *this;
	}
	in_t &operator>>(char *s) {
		char c;
		for (c = gc(); c <= ' ';) c = gc();
		for (; c > ' '; c = gc()) *s++ = c;
		return *s = 0, *this;
	}
#ifdef _STRINGFWD_H
	in_t &operator>>(std::string &s) {
		char c;
		s.clear();
		for (c = gc(); c <= ' ';) c = gc();
		for (; c > ' '; c = gc()) s += c;
		return *this;
	}
#endif
};

struct out_t {
#ifdef LOCAL_QWQ
	inline out_t() { setvbuf(stdout, 0, _IONBF, 0); }
	inline out_t(const char *path) {
		freopen(path, "w", stdout);
		setvbuf(stdout, 0, _IONBF, 0);
	}
	inline void flush() {}
	inline void pc(char c) { putchar(c); }
#else
	static const int SZ = 1 << 20;
	char buf[SZ], *s = buf, *t = buf + SZ;
	inline out_t() { setvbuf(stdout, 0, _IONBF, 0); }
	inline out_t(const char *path) {
		freopen(path, "w", stdout);
		setvbuf(stdout, 0, _IONBF, 0);
	}
	inline void flush() { fwrite(buf, 1, s - buf, stdout); }
	inline void pc(char c) {
		if (s == t) flush(), s = buf;
		*s++ = c;
	}
	inline ~out_t() { flush(); }
#endif
	template <typename T>
	void outU(const T &x) {
		if (x > 9) outU(x / 10);
		pc(x % 10 + '0');
	}
	template <typename T>
	void outI(const T &x) {
		if (x < 0) pc('-');
		outU(x);
	}

#define OUT_DEF(type, func) \
	out_t &operator<<(type x) { return func(x), *this; };
#ifdef __x86_64__
#define OUT_DEF_X64(type, func) OUT_DEF(type, func)
#else
#define OUT_DEF_X64(type, func)
#endif

	OUT_DEF(signed short, outI);
	OUT_DEF(signed int, outI);
	OUT_DEF(signed long, outI);
	OUT_DEF(signed long long, outI);
	OUT_DEF_X64(signed __int128, outI);

	OUT_DEF(unsigned short, outU);
	OUT_DEF(unsigned int, outU);
	OUT_DEF(unsigned long, outU);
	OUT_DEF(unsigned long long, outU);
	OUT_DEF_X64(unsigned __int128, outU);

	out_t &operator<<(char c) { return pc(c), *this; }
	out_t &operator<<(char *s) {
		while (*s) pc(*s++);
		return *this;
	}
};
}  // namespace IO
using namespace IO;
#pragma endregion

in_t in;
out_t out;

typedef long long ll;
const int N = 4e5 + 54;

int cnt[1000];
inline void call(int line) {
	if (++line[cnt] > 2e8) printf("line %d executed more than 6e7 times.", line), exit(1);
}
// #define $ call(__LINE__)
#define $ void()

struct SGT {
	static const int M = 2e6 + 62;
#define L ch][0
#define R ch][1
#define mid (l + r) / 2
	int n, w[M], ch[M][2], t[M], nc;
	ll s[M];
	SGT() { nc = 1; }
	void up(int x) { x[s] = x[L][s] + x[R][s]; }
	void put(int x, ll y) { x[t] += y, x[s] += x[w] * y; }
	void pd(int x) { put(x[L], x[t]), put(x[R], x[t]), x[t] = 0; }
	void build(int x, int l, int r, int *a) {
		if (l == r) return x[w] = a[l], void();
		$, build(x[L] = ++nc, l, mid, a), build(x[R] = ++nc, mid + 1, r, a);
		x[w] = x[L][w] + x[R][w];
	}
	void upd(int x, int l, int r, int ql, int qr, int v) {
		$;
		if (ql <= l && r <= qr) return put(x, v);
		if (pd(x), ql <= mid) upd(x[L], l, mid, ql, qr, v);
		if (mid < qr) upd(x[R], mid + 1, r, ql, qr, v);
		up(x);
	}
	ll qry(int x, int l, int r, int ql, int qr) {
		$;
		if (ql <= l && r <= qr) return x[s];
		if (pd(x), qr <= mid) return qry(x[L], l, mid, ql, qr);
		if (mid < ql) return qry(x[R], mid + 1, r, ql, qr);
		return qry(x[L], l, mid, ql, qr) + qry(x[R], mid + 1, r, ql, qr);
	}
};
struct HLD {
	std::vector<int> g[N];
	void operator()(int x, int y) { x[g].push_back(y); }

	int n, dep[N], dfn[N], par[N], son[N], sz[N], top[N], w[N];
	SGT sgt;
	void build(int *_w, int nn) {
		int idx = 0;
		n = nn;
		std::function<void(int)> dfs1 = [&](int x) {
			$;
			int mx = 0;
			x[sz] = 1;
			for (int nx : x[g]) {
				nx[dep] = x[dep] + 1, nx[par] = x, dfs1(nx), x[sz] += nx[sz];
				if (nx[sz] > mx) mx = nx[sz], x[son] = nx;
			}
		};
		std::function<void(int, int)> dfs2 = [&](int x, int t) {
			$, x[top] = t, x[dfn] = ++idx, idx[w] = x[_w] - x[par][_w];
			if (!x[son]) return;
			dfs2(x[son], t);
			for (int nx : x[g])
				if (nx != x[son]) dfs2(nx, nx);
		};
		dfs1(1), dfs2(1, 1);
		sgt.build(1, 1, n, w);
	}
	void upd(int x, int v) {
		for (; x[top] != 1; x = x[top][par]) $, sgt.upd(1, 1, n, x[top][dfn], x[dfn], v);
		sgt.upd(1, 1, n, 1, x[dfn], v);
	}
	ll qry(int x) {
		ll r = 0;
		for (; x[top] != 1; x = x[top][par])
			$, r += sgt.qry(1, 1, n, x[top][dfn], x[dfn]);
		return r + sgt.qry(1, 1, n, 1, x[dfn]);
	}
	int lca(int x, int y) {
		for (; top[x] != top[y]; x = par[top[x]])
			if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
		return dep[x] < dep[y] ? x : y;
	}
};
struct SAM {
	int len[N], link[N], tr[N][26], suf[N], nc, last;
	SAM() { nc = last = 1; }
	void ins(int c) {
		$;
		int cur = ++nc, p = last, q, cl;
		cur[len] = p[len] + 1;
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
		last = cur;
	}
	void operator+=(char *s) {
		int n = strlen(s);
		for (int i = 0; i < n; i++) ins(s[i] - 97), suf[n - i - 1] = last;
	}
	void build(HLD &hld) {
		for (int i = 2; i <= nc; i++) hld(i[link], i);
		hld.build(len, nc);
	}
} sam;
HLD hld;

int n, q, u, v, x, y, a[N];
char s[N];
ll ans;
int main() {
	in >> n >> q >> s;
	std::reverse(s, s + n), sam += s;
	sam.build(hld);
	while (q--) {
		ans = 0;
		in >> u >> v;
		for (int i = 1; i <= u; i++) in >> a[i], hld.upd((--a[i])[sam.suf], 1);
		for (int i = 1; i <= v; i++) in >> x, ans += hld.qry((x - 1)[sam.suf]);
		for (int i = 1; i <= u; i++) hld.upd(a[i][sam.suf], -1);
		out << ans << '\n';
	}
}