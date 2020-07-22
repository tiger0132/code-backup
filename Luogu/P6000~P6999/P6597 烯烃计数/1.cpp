#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <vector>
#define int unsigned

typedef unsigned long long L;
const int N = 5.3e5 + 535, P = 998244353, G = 3;

struct io_t {
	struct stat st;
	char* ptr;
	int fd;
	io_t() {
		fd = fileno(stdin), fstat(fd, &st), ptr = (char*)mmap(0, st.st_size, 1, 2, fd, 0);
	}
	inline io_t& operator>>(int& x) {
#ifdef LOCAL
		scanf("%d", &x);
#else
		x = 0;
		while (*ptr < '0') ++ptr;
		while (*ptr >= '0') x = x * 10 + *ptr++ - 48;
#endif
		return *this;
	}
} io;

int _inv[N];
void init() {
	_inv[1] = 1;
	for (int i = 2; i < N; i++) _inv[i] = L(P - P / i) * _inv[P % i] % P;
}
int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = (L)x * x % P)
		if (y & 1) r = (L)r * x % P;
	return r;
}
inline void md(int& x) {
	if (x >= P) x -= P;
}

struct poly {
	std::vector<int> v;

	inline poly() {}
	inline poly(int n) : v(n) {}
	inline poly(const poly& rhs) : v(rhs.v) {}
	inline poly(const std::vector<int>& rhs) : v(rhs) {}

	inline poly& operator=(const poly& rhs) { return v = rhs.v, *this; }

	inline size_t size() { return v.size(); }
	inline bool empty() { return v.empty(); }
	inline void resize(int n) { v.resize(n); }
	inline void clear() { v.clear(); }
	inline void shl() { v.insert(v.begin(), 0); }
	inline void shrink() {
		while (!v.empty() && !v.back()) v.pop_back();
	}

	inline static int len(int n) { return 1 << (32 - __builtin_clz(n - 1)); }

	inline int& operator[](int i) { return v[i]; }
	inline void operator*=(const poly& rhs) { mul(rhs); }

	inline void dft(int n) {
		static L tmp[N];
		resize(n);
		if (n <= 1) return;
		for (int i = 0, ri = 0; i < n; i++) {
			tmp[i] = v[ri];
			for (int k = n >> 1; (ri ^= k) < k;) k >>= 1;
		}
		for (int i = 1; i < n; i *= 2) {
			int wn = pw(G, (P - 1) / (i * 2));
			for (int j = 0; j < n; j += i * 2) {
				L *a = tmp + j, *b = tmp + j + i;
				for (int k = 0, w = 1; k < i; k++, w = (L)w * wn % P) {
					int y = b[k] * w % P;
					b[k] = a[k] + P - y, a[k] += y;
				}
			}
		}
		for (int i = 0; i < n; i++) v[i] = tmp[i] % P;
	}
	inline void idft(int n) {
		dft(n);
		if (n <= 1) return;
		std::reverse(v.begin() + 1, v.end());
		int tmp = P - (P - 1) / n;
		for (int& i : v) i = (L)i * tmp % P;
	}
	inline void mul(
		poly rhs,
		std::function<int(int, int)> f = [](int x, int y) { return (L)x * y % P; }) {
		int n = len(size() + rhs.size() - 1);
		dft(n), rhs.dft(n);
		for (int i = 0; i < n; i++) v[i] = f(v[i], rhs[i]);
		idft(n);
	}
	inline void inv() {
		std::vector<int> va{pw(v[0], P - 2)};
		poly a;
		int n = size(), m = len(n);
		v.resize(m), v.swap(va);
		for (int i = 2; i <= m; i *= 2) {
			a.resize(i);
			for (int j = 0; j < i; j++) a[j] = va[j];
			mul(a, [](int x, int y) { return x * (2 + P - (L)x * y % P) % P; });
			resize(i);
		}
		resize(n);
	}
} a;

inline void calc(poly& f, int n) {	// loj6538
	int m = poly::len(n);
	f.resize(1), f[0] = 1;
	poly f1, f2, f3, fx2, fx3, p, q;
	for (int i = 2; i <= m; i *= 2) {
		int l = i * 2;
		f1 = f, f1.dft(l);
		fx2.clear(), fx3.clear();
		f2.resize(l), f3.resize(l), fx2.resize(i), fx3.resize(i);
		for (int j = 0; j < l; j++) f2[j] = (L)f1[j] * f1[j] % P;
		for (int j = 0; j < l; j++) f3[j] = (L)f2[j] * f1[j] % P;
		for (int j = 0; j < i; j += 2) fx2[j] = f[j / 2];
		for (int j = 0; j < i; j += 3) fx3[j] = f[j / 3];
		f2.idft(l), f3.idft(l), f2.resize(i);
		q.resize(i);
		for (int j = 0; j < i; j++) q[j] = 3ull * (f2[j] + fx2[j]) % P;
		q.shl(), q[0] = P - 6;
		q.resize(i);
		fx2.dft(l);
		for (int j = 0; j < l; j++) fx2[j] = (L)fx2[j] * f1[j] % P;
		fx2.idft(l), f1.idft(l), fx2.resize(i);
		p.resize(i);
		for (int j = 0; j < i; j++) p[j] = (f3[j] + 3ull * fx2[j] + 2ull * fx3[j]) % P;
		p.shl(), p[0] = 6;
		for (int j = 0; j < i; j++) md(p[j] += P - 6ull * f1[j] % P);
		p.resize(i);
		q.inv();
		p.mul(q);
		f.resize(i);
		for (int j = 0; j < i; j++) md(f[j] += P - p[j]);
	}
	f.resize(n);
}
inline void calc2(poly& f) {
	poly fx2, fx22, fx4, f2, f4;
	int n = f.size();
	fx2.resize(n), fx4.resize(n);
	for (int i = 0; i < n; i += 2) fx2[i] = f[i / 2];
	for (int i = 0; i < n; i += 4) fx4[i] = f[i / 4];
	fx22 = fx2, fx22.mul(fx22);
	f2 = f, f2.mul(f2);
	f4 = f2, f4.mul(f4);
	f2.mul(fx2);  // F(x)^2 F(x^2)
	for (int i = 0; i < n; i++)
		f[i] = (f4[i] + 2ll * f2[i] + 3ll * fx22[i] + 2ll * fx4[i]) % P * 873463809 % P;
}

int n;
signed main() {
	io >> n;
	calc(a, n - 1);
	calc2(a);
	for (int i : a.v) printf("%u\n", i);
}