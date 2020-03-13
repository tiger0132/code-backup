#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>

typedef unsigned long long L;
const int N = 2.7e5 + 572, P = 998244353, G = 3;

struct io_t {
	struct stat st;
	char* ptr;
	int fd;
	inline io_t() {
		fd = fileno(stdin), fstat(fd, &st), ptr = (char*)mmap(0, st.st_size, 1, 2, fd, 0);
	}
	io_t& operator>>(int& x) {
#ifdef LOCAL
		scanf("%d", &x);
#else
		x = 0;
		while (*ptr < '0') ++ptr;
		while (*ptr >= '0') x = x * 10 + (*ptr++ ^ 48);
#endif
		return *this;
	}
} io;

int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = (L)x * x % P)
		if (y & 1) r = (L)r * x % P;
	return r;
}

void butterfly(int& x, int& y) {
	int x0 = x, y0 = y;
	x += y;
	if (x >= P) x -= P;
	int t = x - y;
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
	inline poly(const poly& rhs) : v(rhs.v) {}
	inline poly(const std::vector<int>& rhs) : v(rhs) {}

	inline size_t size() { return v.size(); }
	inline bool empty() { return v.empty(); }
	inline void resize(int n) { v.resize(n); }
	inline void shl() { v.insert(v.begin(), 0); }
	void shrink() {
		while (!v.empty() && !v.back()) v.pop_back();
	}

	inline static int len(int n) { return 1 << (32 - __builtin_clz(n - 1)); }

	inline int& operator[](int i) { return v[i]; }
	inline void operator*=(const poly& rhs) { mul(rhs); }

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
			for (int j = 0; j < n; j += i << 1) {
				L *a = tmp + j, *b = tmp + j + i;
				int* ww = w + i;
				for (int k = 0; k < i; ++k) {
					int y = (L)b[k] * ww[k] % P;
					b[k] = a[k] + P - y, a[k] += y;
				}
			}
		for (int i = 0; i < n; ++i) v[i] = tmp[i] % P;
	}
	void idft(int n) {
		dft(n);
		if (n <= 1) return;
		std::reverse(v.begin() + 1, v.end());
		int tmp = P - (P - 1) / n;
		for (int& i : v) i = (L)i * tmp % P;
	}
	void mul(poly rhs) {
		int n = len(size() + rhs.size() - 1);
		dft(n), rhs.dft(n);
		for (int i = 0; i < n; ++i) v[i] = (L)v[i] * rhs[i] % P;
		idft(n);
	}
} a, b;

int n, m;
signed main() {
	io >> n >> m;
	++n, ++m;
	init(n + m - 1);
	a.resize(n), b.resize(m);
	for (int i = 0; i < n; ++i) io >> a[i];
	for (int i = 0; i < m; ++i) io >> b[i];
	a *= b;
	for (int i = 0; i < n + m - 1; ++i) printf("%d ", a[i]);
}