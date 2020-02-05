#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 55;

int top, sum, lans, h[N], w[N];
int n, m, q, x, y, z, k;
char s[N][N], f[N][N];
int main() {
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
	while (q--) {
		scanf("%d%d%d%d", &x, &z, &y, &k);
		memset(f, 0, sizeof f);
		for (int i = x; i <= y; i++)
			for (int j = z; j <= k; j++)
				if (s[i][j] == '0') f[i][j] = f[i - 1][j] + 1;
		for (int i = x; i <= y; i++) {
			for (int j = z; j <= k; j++) {
				int nw = 1;
				for (; top && f[i][j] <= h[top]; top--) {
					nw += w[top];
					sum -= w[top] * h[top];
				}
				w[++top] = nw, h[top] = f[i][j];
				sum += w[top] * h[top];
				lans += sum;
			}
			top = 0, sum = 0;
		}
		printf("%d\n", lans), lans = 0;
	}
}