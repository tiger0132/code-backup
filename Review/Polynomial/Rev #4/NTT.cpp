// Modified from f321dd's template

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

typedef unsigned u;
typedef unsigned long long ul;
const int N = 2.7e5, P = 998244353, G = 3, GInv = 332748118;

u md(u x) { return x < P ? x : x - P; }
u pw(u x, u y) {
	u r = 1;
	for (; y; y >>= 1, x = (ul)x * x % P)
		if (y & 1) r = (ul)r * x % P;
	return r;
}
struct inv_t {
	std::vector<u> v;
	inv_t() : v{0, 1} {}
	u operator[](u x) {
		u n = v.size();
		if (x < n) return v[x];
		v.resize(x + 1);
		for (u i = n; i <= x; ++i) v[i] = (ul)(P - P / i) * v[P % i] % P;
		return v[x];
	}
	u operator()(u x) const { return pw(x, P - 2); }
} inv;

struct poly {
	std::vector<u> v;
	poly() {}
	poly(int n) : v(n) {}
	u& operator[](int i) { return v[i]; }
	int size() const { return v.size(); }
	void swap(poly& x) { v.swap(x.v); }
	bool empty() const { return v.empty(); }
	void shl() { v.insert(v.begin(), 0); }
	void shrink() {
		while (size() && !v.back()) v.pop_back();
	}
	void deriv() {
		shrink();
		for (int i = 1; i < size(); ++i) v[i - 1] = (ul)i * v[i] % P;
		if (size()) v.pop_back();
	}
	void intg() {
		shrink(), shl();
		for (int i = size() - 1; i > 0; --i) v[i] = (ul)v[i] * inv[i] % P;
	}
	static int len(int n) {
		while (n != (n & -n)) n += n & -n;
		return n;
	}
	void ntt(int n, bool op) {
		v.resize(n);
		if (n <= 1) return;
		for (int i = 0, ri = 0; i < n; ++i) {
			if (i < ri) std::swap(v[i], v[ri]);
			for (int k = n >> 1; (ri ^= k) < k;) k >>= 1;
		}
		std::vector<u> w(n / 2);
		w[0] = 1;
		for (int i = 1; i < n; i <<= 1) {
			for (int j = i / 2 - 1; j >= 0; --j) w[j * 2] = w[j];
			ul wn = pw(op ? GInv : G, (P - 1) / (2 * i));
			for (int j = 1; j < i; j += 2) w[j] = wn * w[j - 1] % P;
			for (int j = 0; j < n; j += 2 * i) {
				u *b = &v[0] + j, *c = b + i;
				for (int k = 0; k < i; ++k) {
					u y = (ul)w[k] * c[k] % P;
					c[k] = md(b[k] + P - y), b[k] = md(b[k] + y);
				}
			}
		}
	}
	void dft(int n) { ntt(n, 0); }
	void idft() {
		int n = size();
		ntt(n, 1);
		ul x = inv(n);
		for (int i = 0; i < n; ++i) v[i] = v[i] * x % P;
	}
	void mul(poly r) {  // 注意，处理完后 r 将会保留 dft 状态
		shrink(), r.shrink();
		int n = len(size() + r.size() - 1);
		dft(n), r.dft(n);
		for (int i = 0; i < n; ++i) v[i] = (ul)v[i] * r.v[i] % P;
		idft(), shrink();
	}
};

poly a, b;
int n, m;
int main() {
	scanf("%d%d", &n, &m);
	a = poly(n + 1), b = poly(m + 1);
	for (int i = 0; i <= n; ++i) scanf("%u", &a[i]);
	for (int i = 0; i <= m; ++i) scanf("%u", &b[i]);
	a.mul(b);
	for (int i = 0; i <= n + m; ++i) printf("%u ", a[i]);
}

/*
i=2
(998244353-998244353/2)*v[1]%998244353
*/