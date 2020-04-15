#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize( \
	"inline,-fgcse,-fgcse-lm,-fipa-sra,-ftree-pre,-ftree-vrp,-fpeephole2,-ffast-math,-fsched-spec,unroll-loops,-falign-jumps,-falign-loops,-falign-labels,-fdevirtualize,-fcaller-saves,-fcrossjumping,-fthread-jumps,-funroll-loops,-freorder-blocks,-fschedule-insns,inline-functions,-ftree-tail-merge,-fschedule-insns2,-fstrict-aliasing,-fstrict-overflow,-falign-functions,-fcse-follow-jumps,-fsched-interblock,-fpartial-inlining,no-stack-protector,-freorder-functions,-findirect-inlining,-fhoist-adjacent-loads,-frerun-cse-after-loop,inline-small-functions,-finline-small-functions,-ftree-switch-conversion,-foptimize-sibling-calls,-fexpensive-optimizations,inline-functions-called-once,-fdelete-null-pointer-checks")

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

typedef unsigned long long L;
const int N = 5.3e5 + 535, P = 998244353, G = 114514;

int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = (L)x * x % P)
		if (y & 1) r = (L)r * x % P;
	return r;
}

int lim, rev[N], w[N];
void init(int n) {
	int l = 32 - __builtin_clz(n - 1);
	lim = 1 << l;
	for (int i = 0, ri = 0; i < lim; ++i) {
		rev[i] = ri;
		for (int k = lim >> 1; (ri ^= k) < k;) k >>= 1;
	}
	int wn = pw(G, (P - 1) >> l);
	w[lim >> 1] = 1;
	for (int i = (lim >> 1) + 1; i < lim; ++i) w[i] = (L)w[i - 1] * wn % P;
	for (int i = (lim >> 1) - 1; i; --i) w[i] = w[i << 1];
	lim = l;
}

struct poly {
	std::vector<int> v;

	inline poly() {}
	inline poly(int n) : v(n) {}
	inline poly(const poly &rhs) : v(rhs.v) {}
	inline poly(const std::vector<int> &rhs) : v(rhs) {}

	inline size_t size() { return v.size(); }
	inline bool empty() { return v.empty(); }
	inline void resize(int n) { v.resize(n); }
	inline void shl() { v.insert(v.begin(), 0); }
	inline void clear() { v.clear(); }
	void shrink() {
		while (!v.empty() && !v.back()) v.pop_back();
	}

	inline static int len(int n) { return 1 << (32 - __builtin_clz(n - 1)); }

	inline int &operator[](int i) { return v[i]; }
	inline void operator*=(const poly &rhs) { mul(rhs); }

	void dft(int n) {
		static L tmp[N];
		int ofs = lim - __builtin_ctz(n);
		resize(n);
		if (n <= 1) return;
		for (int i = 0; i < n; ++i) tmp[rev[i] >> ofs] = v[i];
		for (int i = 0; i < n; i += 2) {
			int x = tmp[i], y = tmp[i + 1];
			tmp[i] = x + y, tmp[i + 1] = x + P - y;
		}
		for (int i = 2; i < n; i <<= 1)
			for (int j = 0; j < n; j += i << 1)
				for (int k = 0; k < i; ++k) {
					int y = (L)tmp[j + i + k] * w[i + k] % P;
					tmp[j + i + k] = tmp[j + k] + P - y, tmp[j + k] += y;
				}
		for (int i = 0; i < n; ++i) v[i] = tmp[i] % P;
	}
	void idft(int n) {
		dft(n);
		if (n <= 1) return;
		std::reverse(v.begin() + 1, v.end());
		int tmp = P - (P - 1) / n;
		for (int &i : v) i = (L)i * tmp % P;
	}
	void mul(poly rhs) {
		int n = len(size() + rhs.size() - 1);
		dft(n), rhs.dft(n);
		for (int i = 0; i < n; ++i) v[i] = (L)v[i] * rhs[i] % P;
		idft(n);
	}
} f[5], g;

struct comb {
	int fac[N], ifac[N];
	void init(int n) {
		0 [fac] = 1;
		for (int i = 1; i <= n; i++) i[fac] = (L)(i - 1)[fac] * i % P;
		n[ifac] = pw(n[fac], P - 2);
		for (int i = n - 1; i >= 0; i--) i[ifac] = (L)(i + 1)[ifac] * (i + 1) % P;
	}
	int operator()(int n, int m) { return (L)n[fac] * m[ifac] % P * (n - m)[ifac] % P; }
} C;

int n, q, k, x, v[5], a[N], b[N];
std::set<int> uniq, mult;
int main() {
	in >> n >> k;
	init(n);
	C.init(n);
	for (int i = 1; i <= n; i++) {
		in >> x;
		if (mult.count(x)) continue;
		if (!uniq.insert(x).second) uniq.erase(x), mult.insert(x);
	}
	for (int i = 0; i < k; i++) {
		in >> x;
		v[i] = x;
		int nn = 0, mm = 0;
		for (int j : uniq) nn += (j < x);
		for (int j : mult) mm += 2 * (j < x);
		f[i].clear(), g.clear();
		f[i].resize(nn + 1), g.resize(mm + 1);
		for (int j = 0, pw2 = 1; j <= nn; j++, pw2 = (pw2 << 1) % P) {
			f[i][j] = (L)C(nn, j) * pw2 % P;
		}
		for (int j = 0; j <= mm; j++) g[j] = C(mm, j);
		f[i].mul(g);
	}
	for (in >> q; q--;) {
		in >> x;
		int ans = 0;
		for (int i = 0; i < k; i++) {
			int p = (x - 2 * v[i]) / 2 - 1;
			if (0 <= p && p < f[i].size()) ans = (ans + f[i][p]) % P;
		}
		out << ans << '\n';
	}
}