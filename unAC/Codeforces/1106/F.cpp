#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e2 + 21, P = 998244353;
typedef long long ll;

struct mat {
	int n, a[N][N];
	inline mat() { memset(a, 0, sizeof a); }
	inline mat(const mat& x) { n = x.n, memcpy(a, x.a, sizeof a); }
	inline void operator*=(const mat& rhs) {
		static int buf[N][N];
		memset(buf, 0, sizeof buf);
		ll t;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				t = 0;
				for (int k = 1; k <= n; k++) {
					t += 1ll * a[i][k] * rhs.a[k][j];
				}
				buf[i][j] = t % P;
			}
		}
		memcpy(a, buf, sizeof a);
	}
} a, b;

int n, m, exp$, f;
int main() {
	scanf("%d", &n);
	a.n = b.n = n;
	for (int i = n; i >= 1; i--) {
		scanf("%d", a.a[1] + i);
		if (i < n) a.a[i + 1][i] = 1;
		b.a[i][i] = 1;
	}
	scanf("%d%d", &m, &f);
	exp$ = m - 3;
	for (; exp$; exp$ >>= 1, (a *= a))
		if (exp$ & 1) b *= a;
	printf("%d", b.a[1][n]);
}