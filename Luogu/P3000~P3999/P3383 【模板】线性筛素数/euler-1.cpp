#include <cstdio>

const int N = 1e7+71;

int p[N], np[N], cnt;
int n, m, x;

int main() {
	scanf("%d", &n); np[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!np[i]) p[++cnt] = i;
		for (int j = 1; j <= cnt && i * p[j] <= n; j++) {
			np[i * p[j]] = 1;
			if (i % p[j] == 0) break;
		}
	}
	for (scanf("%d", &m); m--; ) {
		scanf("%d", &x);
		puts(np[x] ? "No" : "Yes");
	}
}