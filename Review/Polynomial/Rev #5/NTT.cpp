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
#define int unsigned  // who needs signed int?

typedef unsigned long long ul;
const int N = 2.7e6 + 672, P = 998244353, G = 3, Gi = 332748118;

struct io_t {
	struct stat st;
	char* ptr;
	int fd;
	io_t() {
		fd = fileno(stdin), fstat(fd, &st), ptr = (char*)mmap(0, st.st_size, 1, 2, fd, 0);
	}
	inline io_t& operator>>(int& x) {
		x = 0;
		while (*ptr < '0') ++ptr;
		while (*ptr >= '0') x = x * 10 + *ptr++ - 48;
		return *this;
	}
} io;

int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = (ul)x * x % P)
		if (y & 1) r = (ul)r * x % P;
	return r;
}
int md(int x) { return x >= P ? x - P : x; }
struct inv_t {
	const int LIMIT = 3e6;
	std::vector<int> v;
	inv_t() : v{0, 1} {}
	int _get(int x) {
		int n = v.size();
		if (x < n) return v[x];
		v.resize(x + 1);
		for (int i = n; i <= x; ++i) v[i] = (ul)(P - P / i) * v[P % i] % P;
		return v[x];
	}
	int operator[](int x) { return _get(x); }
	int operator()(int x) {
		if (x <= LIMIT) return _get(x);
		return pw(x, P - 2);
	}
} inv;

struct poly {
	std::vector<int> v;
	poly() {}
	poly(size_t n) : v(n) {}
	poly(const poly& rhs) : v(rhs.v) {}
	poly(const std::vector<int>& rhs) : v(rhs) {}

	size_t size() { return v.size(); }
	void swap(poly& rhs) { v.swap(rhs.v); }
	bool empty() { return v.empty(); }
	void shl() { v.insert(v.begin(), 0); }
	void shrink() {
		while (!v.empty() && !v.back()) v.pop_back();
	}

	void deriv() {
		shrink();
		for (int i = 1; i < v.size(); i++) v[i - 1] = (ul)i * v[i] % P;
		if (!v.empty()) v.pop_back();
	}
	void intg() {
		shrink(), shl();
		for (int i = 1; i < v.size(); i++) v[i] = (ul)v[i] * inv[i] % P;
	}
	// int len(int n) { return n > 1 ? 1u << (32 - __builtin_clz(n - 1)) : 1; }
	int len(int n) { return 1u << (32 - __builtin_clz(n - 1)); }

	void ntt(int n, signed op) {  // naive DIT NTT impl
		v.resize(n);
		if (n <= 1) return;
		for (int i = 0, ri = 0; i < n; i++) {
			if (i < ri) std::swap(v[i], v[ri]);
			for (int k = n >> 1; (ri ^= k) < k;) k >>= 1;
		}
		for (int i = 0; i < n; i += 2) {
			int x = v[i], y = v[i + 1];
			v[i] = md(x + y), v[i + 1] = md(x - y + P);
		}
		std::vector<int> w(n / 2);
		w[0] = 1;
		// todo 预处理单位根
		for (int i = 2; i < n; i *= 2) {
			w[1] = pw(op == 1 ? G : Gi, (P - 1) / (i * 2));
			for (int j = 2; j < i; j++) w[j] = (ul)w[j - 1] * w[1] % P;
			for (int j = 0; j < n; j += i * 2) {
				int *a = &v[0] + j, *b = &v[0] + j + i;
				for (int k = 0; k < i; k++) {
					int y = (ul)b[k] * w[k] % P;
					b[k] = md(a[k] - y + P);
					a[k] = md(a[k] + y);
				}
			}
		}
	}
	void dft(int n) { ntt(n, 1); }
	void idft() {
		int n = size();
		if (n <= 1) return;
		ntt(n, -1);
		ul x = P - (P - 1) / n;
		for (int i = 0; i < n; ++i) v[i] = (ul)v[i] * x % P;
	}
	void mul(poly& rhs) {
		shrink(), rhs.shrink();
		int n = len(size() + rhs.size() - 1);
		dft(n), rhs.dft(n);
		for (int i = 0; i < n; i++) v[i] = (ul)v[i] * rhs.v[i] % P;
		idft(), shrink();
	}
};

poly a, b;
int n, m;
signed main() {
	io >> n >> m;
	a = poly(n + 1), b = poly(m + 1);
	for (int i = 0; i <= n; i++) io >> a.v[i];
	for (int i = 0; i <= m; i++) io >> b.v[i];
	a.mul(b);
	for (int i = 0; i <= n + m; i++) printf("%u ", a.v[i]);
}