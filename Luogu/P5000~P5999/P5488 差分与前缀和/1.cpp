// 大象大象你的鼻子为什么那么长
// 神鱼神鱼你的组合为什么那么强

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

typedef unsigned u;
typedef unsigned long long ul;
const int N = 1.1e6, P = 1004535809, G = 3, GInv = 334845270, div2 = 502267905;

struct io_t {
#define $ (s == t && (t = (s = in) + fread(in, 1, SIZ, stdin), s == t) ? EOF : *s++)
	static const int SIZ = 1 << 25;
	char in[SIZ], out[SIZ], *s = in, *t = in, *o = out;
	u st[15], top;
	~io_t() { fwrite(out, o - out, 1, stdout); }
	inline u read() {
		u x = 0;
		char c = $;
		while (c < '0' || c > '9') c = $;
		while (c >= '0' && c <= '9') x = x * 10 + c - 48, c = $;
		return x;
	}
	void prt(u x) {
		if (x > 9) prt(x / 10);
		*o++ = 48 + x % 10;
	}
	operator u() { return read(); }
	io_t& operator<(u x) { return prt(x), *this; }
	io_t& operator<(char x) { return *o++ = x, *this; }
} io;
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
} iv;

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
				u *a = &v[0] + j, *b = a + i;
				for (int k = 0; k < i; ++k) {
					u y = (ul)w[k] * b[k] % P;
					b[k] = md(a[k] + P - y), a[k] = md(a[k] + y);
				}
			}
		}
	}
	void dft(int n) { ntt(n, 0); }
	void idft() {
		int n = size();
		if (n <= 1) return;
		ntt(n, 1);
		ul x = P - (P - 1) / n;
		for (int i = 0; i < n; ++i) v[i] = v[i] * x % P;
	}
	void mul(poly r) {  // 注意，处理完后 r 将会保留 dft 状态
		shrink(), r.shrink();
		int n = len(size() + r.size() - 1);
		dft(n), r.dft(n);
		for (int i = 0; i < n; ++i) v[i] = (ul)v[i] * r.v[i] % P;
		idft(), shrink();
	}
	void mod(int n) { v.resize(n); }
	// F: 原多项式, G: mod x^n 的答案, H: mod x^(n/2) 的答案
	void inv(int n) {  // G = H(2 - FH) (mod x^n)
		std::vector<u> f0{iv(v[0])};
		int m = len(n);
		mod(m), v.swap(f0);
		for (int i = 2; i <= m; i *= 2) {  // v: H
			int l = i * 2;
			poly f(l);  // F mod x^i
			for (int j = 0; j < i; ++j) f[j] = f0[j];
			f.dft(l), dft(l);
			for (int j = 0; j < l; ++j) v[j] = v[j] * (2 + P - (ul)f[j] * v[j] % P) % P;
			idft(), mod(i);
		}
		mod(n);
	}
};

u fac[N] = {1}, ifac[N] = {1};
u c(u n, u m) { return m > n ? 0 : (ul)fac[n] * ifac[m] % P * ifac[n - m] % P; }

u n, k, t;
poly f, g;
int main() {
	n = io, k = io, t = io;
	f.mod(n), g.mod(n), iv[N];
	for (int i = 1; i < N; ++i) {
		fac[i] = (ul)fac[i - 1] * i % P;
		ifac[i] = (ul)ifac[i - 1] * iv[i] % P;
	}
	for (int i = 0; i < n; ++i) f[i] = io;
	for (int i = 0; i <= std::min(n - 1, k); ++i)
		g[i] = md(i % 2 ? P - c(k, i) : c(k, i));
	if (!t) g.inv(n);
	f.mul(g);
	for (int i = 0; i < n; i++) io < f[i] < ' ';
}