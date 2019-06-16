#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>

typedef unsigned u;
const u N = 5e6 + 65, P = 1e9 + 7;

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

inline u pw(u x, u y) {
	if (!y) return 1;
	for (; ~y & 1; y >>= 1) x = 1ll * x * x % P;
	u r = x;
	for (y >>= 1; y; y >>= 1) x = 1ll * x * x % P, (y & 1) && (r = 1ll * r * x % P);
	return r;
}

static u a[N], b[N], c[N];
int main() {
	register u n, k, *p1, *p2, t, ans;
	n = $, *(p2 = b) = 1;
	for (p1 = a + 1; p1 <= a + n; ++p2) *(p2 + 1) = 1ll * (*p1++ = $) * *p2 % P;
	for (*(p2 = c + n + 1) = 1; p2 > c; --p2) *(p2 - 1) = 1ll * *--p1 * *p2 % P;
	t = pw(*++p2, P - 2);
	for (k = 1, p1 = b + n - 1, p2 = c + n + 1; p1 >= b; k = k * 998244353ll % P)
		ans = (ans + 1ll * t * *p1-- % P * *p2-- % P * k % P) % P;
	printf("%u", ans);
}