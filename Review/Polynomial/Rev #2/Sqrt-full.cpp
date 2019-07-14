#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize( \
	"inline,-fgcse,-fgcse-lm,-fipa-sra,-ftree-pre,-ftree-vrp,-fpeephole2,-ffast-math,-fsched-spec,unroll-loops,-falign-jumps,-falign-loops,-falign-labels,-fdevirtualize,-fcaller-saves,-fcrossjumping,-fthread-jumps,-funroll-loops,-freorder-blocks,-fschedule-insns,inline-functions,-ftree-tail-merge,-fschedule-insns2,-fstrict-aliasing,-fstrict-overflow,-falign-functions,-fcse-follow-jumps,-fsched-interblock,-fpartial-inlining,no-stack-protector,-freorder-functions,-findirect-inlining,-fhoist-adjacent-loads,-frerun-cse-after-loop,inline-small-functions,-finline-small-functions,-ftree-switch-conversion,-foptimize-sibling-calls,-fexpensive-optimizations,inline-functions-called-once,-fdelete-null-pointer-checks")
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#define I(x) p(x, P - 2)
#define F_M [](int x, int y) { return 1ll * x * y % P; }
#define C(x) memset(x + n, 0, (lim - n) * 4)
#define M0(x) memset(x, 0, sizeof x)

//////////////////////////////// 鸣谢 LK ////////////////////////////////
namespace io {
const int SIZE = (1 << 21) + 1;
char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr;
// getchar
#define gc() (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++)
// print the remaining part
inline void flush() {
	fwrite(obuf, 1, oS - obuf, stdout);
	oS = obuf;
}
// putchar
inline void putc(char x) {
	*oS++ = x;
	if (oS == oT) flush();
}
// input a signed integer
inline bool read(signed &x) {
	for (f = 1, c = gc(); c < '0' || c > '9'; c = gc())
		if (c == '-')
			f = -1;
		else if (c == EOF)
			return 0;
	for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15);
	x *= f;
	return 1;
}

inline bool read(long long &x) {
	for (f = 1, c = gc(); c < '0' || c > '9'; c = gc())
		if (c == '-')
			f = -1;
		else if (c == EOF)
			return 0;
	for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15);
	x *= f;
	return 1;
}
inline bool read(char &x) {
	x = gc();
	return x != EOF;
}
inline bool read(char *x) {
	while ((*x = gc()) == '\n' || *x == ' ' || *x == '\r')
		if (*x == EOF) return 0;
	while (!(*x == '\n' || *x == ' ' || *x == '\r')) *(++x) = gc();
	*x = 0;
	return 1;
}
template <typename A, typename... B>
inline bool read(A &x, B &... y) {
	return read(x) && read(y...);
}
// print a signed integer
inline bool write(signed x) {
	if (!x) putc('0');
	if (x < 0) putc('-'), x = -x;
	while (x) qu[++qr] = x % 10 + '0', x /= 10;
	while (qr) putc(qu[qr--]);
	return 0;
}

inline bool write(long long x) {
	if (!x) putc('0');
	if (x < 0) putc('-'), x = -x;
	while (x) qu[++qr] = x % 10 + '0', x /= 10;
	while (qr) putc(qu[qr--]);
	return 0;
}
inline bool write(char x) {
	putc(x);
	return 0;
}
inline bool write(const char *x) {
	while (*x) {
		putc(*x);
		++x;
	}
	return 0;
}
inline bool write(char *x) {
	while (*x) {
		putc(*x);
		++x;
	}
	return 0;
}
template <typename A, typename... B>
inline bool write(A x, B... y) {
	return write(x) || write(y...);
}
// no need to call flush at the end manually!
struct Flusher_ {
	~Flusher_() { flush(); }
} io_flusher_;
}  // namespace io
using io::putc;
using io::read;
using io::write;
//////////////////////////////// 鸣谢 LK ////////////////////////////////

const int LGN = 22, N = 6e5 + 56, P = 998244353, G = 3, Gi = 332748118;
struct comp {
	int x, y;
};
inline comp mul(comp a, comp b, int w) {
	return {(1ll * a.x * b.x % P + 1ll * w * a.y % P * b.y % P) % P, (1ll * a.x * b.y % P + 1ll * a.y * b.x % P) % P};
}
inline int p(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = 1ll * x * x % P)
		if (y & 1) r = 1ll * r * x % P;
	return r;
}
inline int p(comp x, int y, int w) {
	comp r = {1, 0};
	for (; y; y >>= 1, x = mul(x, x, w))
		if (y & 1) r = mul(r, x, w);
	return std::min(r.x, P - r.x);
}
inline int cipolla(int x) {
	if (p(x, (P - 1) / 2) == P - 1) return -1;
	while (1) {
		int a = rand(), w = (1ll * a * a - x + P) % P;
		if (p(w, (P - 1) / 2) == P - 1) return p({a, 1}, (P + 1) / 2, w);
	}
}

int u1[LGN], u2[LGN], invp[N] = {0, 1};
static struct _init {
	inline _init() {
		for (int i = 1; i < LGN; i++) u1[i] = p(G, (P - 1) / (1 << i)), u2[i] = p(Gi, (P - 1) / (1 << i));
		for (int i = 2; i < N; i++) invp[i] = 1ll * (P - P / i) * invp[P % i] % P;
	}
} __init;

int r[N], lim, l;
inline void ntt(int *a, int op) {
	for (int i = 0; i < lim; i++)
		if (i < r[i]) std::swap(a[i], a[r[i]]);
	for (int i = 1, lgi = 1; i < lim; i *= 2, lgi++) {
		int wn = (op == 1 ? u1 : u2)[lgi];
		for (int j = 0; j < lim; j += i * 2) {
			int w = 1;
			for (int k = 0; k < i; k++, w = 1ll * w * wn % P) {
				int x = a[j + k], y = 1ll * w * a[j + k + i] % P;
				a[j + k] = (x + y) % P, a[j + k + i] = (x - y + P) % P;
			}
		}
	}
	if (op == -1)
		for (int i = 0; i < lim; i++) a[i] = 1ll * a[i] * invp[lim] % P;
}
inline void init(int n) {
	for (lim = 1, l = 0; lim <= n;) lim *= 2, l++;
	for (int i = 1; i < lim; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
}
template <typename F>
inline void mul(int *a, int *b, int *ans, const F &f) {
	static int c[N], d[N];
	memcpy(c, a, lim * 4), memcpy(d, b, lim * 4), ntt(c, 1), ntt(d, 1);
	for (int i = 0; i < lim; i++) ans[i] = f(c[i], d[i]);
	ntt(ans, -1);
}
inline void inv(int n, int *a, int *ans) {  // LIMITATION: a != ans
	static int b[N];
	if (n == 1) return void(*ans = I(*a));
	inv((n + 1) / 2, a, ans), init(n * 2);
	memcpy(b, a, n * 4), C(b);
	mul(b, ans, ans, [](int x, int y) { return (2 - 1ll * x * y % P + P) % P * y % P; }), C(ans);
}
inline void intg(int n, int *a, int *ans) {
	for (int i = 1; i < n; i++) ans[i] = 1ll * a[i - 1] * invp[i] % P;
	*ans = 0;
}
inline void derv(int n, int *a, int *ans) {
	for (int i = 1; i < n; i++) ans[i - 1] = 1ll * i * a[i] % P;
	ans[n - 1] = 0;
}
inline void ln(int n, int *a, int *ans) {
	static int b[N], c[N];
	M0(b), M0(c), derv(n, a, b), inv(n, a, c), mul(b, c, c, F_M), intg(n, c, ans);
}
inline void exp(int n, int *a, int *ans) {  // LIMITATION: n = 2^d
	static int b[N];
	if (n == 1) return;
	exp(n >> 1, a, ans), ln(n, ans, b), C(b);
	for (int i = 0; i < n; i++) b[i] = (!i + a[i] - b[i] + P) % P;
	mul(ans, b, ans, F_M), C(ans);
}
inline void pow(int n, int k, int *a, int *ans) {
	static int b[N];
	ln(n, a, b);
	for (int i = 0; i < n; i++) b[i] = 1ll * b[i] * k % P;
	exp(n, b, ans);
}
inline void sqrt(int n, int *a, int *ans) {
	static int b[N];
	ln(n, a, b);
	for (int i = 0; i < n; i++) b[i] = b[i] * 499122177ll % P;
	*ans = cipolla(*a), exp(n, b, ans);
}

int n, k, m = 1, a[N], b[N];
char c;
int main() {
	srand(time(0));
	read(n);
	for (int i = 0; i < n; i++) read(a[i]);
	while (m < n) m <<= 1;
	sqrt(m, a, b);
	for (int i = 0; i < n; i++) printf("%d ", b[i]);
}