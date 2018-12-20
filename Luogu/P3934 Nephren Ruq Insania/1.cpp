#include <cstdio>

const int N = 1e7+71;

int p[N], np[N], phi[N], cnt;
int n, m, x;

int main() {
	phi[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!np[i]) {
			p[++cnt] = i;
			phi[i] = i-1;
		}
		for (int j = 1, k; j <= cnt && (k = i * p[j]) <= n; j++) {
			np[k] = 1;
			if (i % p[j]) {
				phi[k] = phi[i] * phi[p[j]];
			} else {
				phi[k] = phi[i] * p[j];
				break;
			}
		}
	}
	for (scanf("%d", &m); m--; ) {
		scanf("%d", &x);
		puts(np[x] ? "No" : "Yes");
	}
}