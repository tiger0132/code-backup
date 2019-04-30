#include <algorithm>
#include <cstdio>
#define $(n, m) solve((n) / k, (m) / k)

const int N = 5e4 + 45;
int mu[N];
int solve(int n, int m) {
	int ret = 0;
	for (int l = 1, r; l <= std::min(n, m); l = r + 1) {
		r = std::min(n / (n / l), m / (m / l));
		ret += (mu[r] - mu[l - 1]) * (n / l) * (m / l);
	}
	return ret;
}

int n, a, b, k, p[N], cnt;
bool f[N];
int main() {
	mu[1] = 1;
	for (int i = 2; i < N; i++) {
		if (!f[i]) p[++cnt] = i, mu[i] = -1;
		for (int j = 1; j <= cnt && i * p[j] < N; j++) {
			f[i * p[j]] = true;
			if (i % p[j])
				mu[i * p[j]] = -mu[i];
			else {
				mu[i * p[j]] = 0;
				break;
			}
		}
	}
	for (int i = 1; i < N; i++) mu[i] += mu[i - 1];
	for (scanf("%d", &n); n--;) {
		scanf("%d%d%d", &a, &b, &k);
		printf("%d\n", $(a, b));
	}
}