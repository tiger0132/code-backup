#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long L;
const int N = 55;
int P;
int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = (L)x * x % P)
		if (y & 1) r = (L)r * x % P;
	return r;
}
int inv[N], fac[N], ifac[N];
void init() {
	1 [inv] = 0 [fac] = 1 [fac] = 0 [ifac] = 1 [ifac] = 1;
	for (int i = 2; i < N; i++) {
		i[inv] = (L)(P - P / i) * (P % i)[inv] % P;
		i[fac] = (L)(i - 1)[fac] * i % P;
		i[ifac] = (L)(i - 1)[ifac] * i[inv] % P;
	}
}

int m, ans, b[N], top;
void dfs(int cur, int mn, int c, int coef, int exp) {
	if (!cur) {
		ans = (ans + (L)coef * pw(m, exp)) % P;
		return;
	}
	for (int i = 1; i <= mn; i++) {
		int nexp = exp + i / 2;
		for (int j = 1; j <= top; j++) nexp += std::__gcd(b[j], i);
		int ncoef = (L)coef * i[inv] % P, nc = 1;
		if (i == b[top]) ncoef = (L)ncoef * c[fac] % P * (c + 1)[ifac] % P, nc = c + 1;
		b[++top] = i;
		dfs(cur - i, std::min(i, cur - i), nc, ncoef, nexp);
		top--;
	}
}

int n;
int main() {
	scanf("%d%d%d", &n, &m, &P);
	init();
	dfs(n, n, 0, 1, 0);
	printf("%d\n", ans);
}