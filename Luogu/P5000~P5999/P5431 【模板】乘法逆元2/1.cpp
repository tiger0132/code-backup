#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>

typedef unsigned u;
const u N = 5e6 + 65;

// clang-format off
char B[1 << 15], *S = B, *T = B;
inline char getcharx() { return S == T && (T = (S = B) + fread(B, 1, 1 << 15, stdin), S == T) ? 0 : *S++; }
inline u get() {
	register u val = 0;
	static char ch;
	while (!isdigit(ch = getcharx()));
	do val = val * 10 + ch - 48; while (isdigit(ch = getcharx()));
	return val;
}
#define $ get()
// clang-format on

static u p;
inline u pw(u x, u y) {
	if (!y) return 1;
	for (; ~y & 1; y >>= 1) x = 1ll * x * x % p;
	u r = x;
	for (y >>= 1; y; y >>= 1) x = 1ll * x * x % p, (y & 1) && (r = 1ll * r * x % p);
	return r;
}

static u a[N], b[N], c[N];
int main() {
	register u n, k0, k, *p1, *p2, t, ans;
	n = $, p = $, k0 = $, *(p2 = b) = 1;
	for (p1 = a + 1; p1 <= a + n; ++p2) *(p2 + 1) = 1ll * (*p1++ = $) * *p2 % p;
	for (*(p2 = c + n + 1) = 1; p2 > c; --p2) *(p2 - 1) = 1ll * *--p1 * *p2 % p;
	t = pw(*++p2, p - 2);
	for (k = k0, p1 = b, p2 = c + 2; p1 < b + n; k = 1ll * k * k0 % p) ans = (ans + 1ll * t * *p1++ % p * *p2++ % p * k % p) % p;
	printf("%u", ans);
}