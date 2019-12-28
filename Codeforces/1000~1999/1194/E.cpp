#include <algorithm>
#include <bitset>
#include <cstdio>
#include <vector>

typedef long long ll;
const int N = 5e3 + 35;

int n, n1, n2, x1[2][N], y1[2][N], x2[2][N], y2[2][N], p[2 * N], fl[N];
std::bitset<N> s[N];  // 不想手写 bitset 了
ll ans;

int main() {
	scanf("%d", &n);
	for (int i = 1, a, b, c, d; i <= n; i++) {
		scanf("%d%d%d%d", &a, &b, &c, &d);
		if (a > c) std::swap(a, c);
		if (b > d) std::swap(b, d);
		if (a == c) x1[0][++n1] = a, y1[0][n1] = b, x2[0][n1] = c, y2[0][n1] = d;
		if (b == d) x1[1][++n2] = a, y1[1][n2] = b, x2[1][n2] = c, y2[1][n2] = d;
	}
#define P(nn1, exp)                                                      \
	do {                                                                 \
		for (int i = 1; i <= n2; i++)                                    \
			for (int j = 1; j <= n1; j++)                                \
				if (x1[1][i] <= x1[0][j] && x2[1][i] >= x1[0][j] &&      \
					y1[0][j] <= y1[1][i] && y2[0][j] >= y2[1][i])        \
					exp = 1;                                             \
		for (int i = 1; i < nn1; i++)                                    \
			for (int j = i + 1, t; j <= nn1; j++)                        \
				t = (s[i] & s[j]).count(), ans += 1ll * t * (t - 1) / 2; \
	} while (0)
	if (n1 < n2)
		P(n1, s[j][i]);
	else
		P(n2, s[i][j]);
	printf("%lld", ans);
}