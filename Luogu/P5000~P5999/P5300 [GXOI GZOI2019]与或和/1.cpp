#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 1e3 + 31, P = 1e9 + 7;

int n, a[N][N], f[N][N], h[N], w[N], top, ans, lans, sum, ans2, c;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) scanf("%d", a[i] + j);
	c = 1ll * n * n * (n + 1) * (n + 1) / 4 % P;
#define CALC(op, ans, ofs)                                     \
	for (int k = 1;; k <<= 1) {                                \
		memset(f, 0, sizeof f);                                \
		for (int i = 1; i <= n; i++)                           \
			for (int j = 1; j <= n; j++)                       \
				if (op a[i][j] & k) f[i][j] = f[i - 1][j] + 1; \
		for (int i = 1; i <= n; i++) {                         \
			for (int j = 1; j <= n; j++) {                     \
				int nw = 1;                                    \
				for (; top && f[i][j] <= h[top]; top--) {      \
					nw += w[top];                              \
					sum -= w[top] * h[top];                    \
				}                                              \
				w[++top] = nw, h[top] = f[i][j];               \
				sum += w[top] * h[top];                        \
				lans = (lans + sum) % P;                       \
			}                                                  \
			top = 0, sum = 0;                                  \
		}                                                      \
		ans = (ans + 1ll * (ofs lans)*k % P) % P, lans = 0;    \
		if (k == 1073741824) break;                            \
	}
	CALC(, ans, )
	CALC(~, ans2, c -)
	printf("%d %d\n", ans, (ans2 + P) % P);
}