#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51, K = 255;

int nxt[N][26], dp[K][K][K], c[4];
char s[N], t[4][N];

int n, q, x, u, v, pt[4];
char op[2], y[2];
int main() {
	scanf("%d%d%s", &n, &q, s + 1);
	for (int i = 0; i < 26; i++) nxt[n + 1][i] = nxt[n + 2][i] = n + 1;
	for (int i = n; i >= 1; i--) {
		for (int j = 0; j < 26; j++) nxt[i][j] = nxt[i + 1][j];
		nxt[i][s[i] -= 'a'] = i;
	}
	while (q--) {
		scanf("%s%d", op, &x);
		if (*op == '+') {
			scanf("%s", y);
			t[x][pt[x] = ++c[x]] = *y - 'a';
			if (x == 1) u = 2, v = 3;
			if (x == 2) u = 1, v = 3;
			if (x == 3) u = 1, v = 2;
			for (pt[u] = 0; pt[u] <= c[u]; pt[u]++)
				for (pt[v] = 0; pt[v] <= c[v]; pt[v]++) {
#define p1 pt[1]
#define p2 pt[2]
#define p3 pt[3]
#define upd(x) dp[p1][p2][p3] = std::min(dp[p1][p2][p3], x)
					dp[p1][p2][p3] = n + 1;
					if (p1) upd(nxt[dp[p1 - 1][p2][p3] + 1][t[1][p1]]);
					if (p2) upd(nxt[dp[p1][p2 - 1][p3] + 1][t[2][p2]]);
					if (p3) upd(nxt[dp[p1][p2][p3 - 1] + 1][t[3][p3]]);
				}
		} else
			c[x]--;
		puts(dp[c[1]][c[2]][c[3]] <= n ? "YES" : "NO");
	}
}