#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e6, P = 998244353;

int p[N + 5], mu[N + 5], xmu[N + 5], cnt;
bool f[N + 5];

void init() {
	f[1] = true, mu[1] = 1;
	for (int i = 2; i <= N; i++) {
		if (!f[i]) p[++cnt] = i, mu[i] = -1;
		for (int j = 1; j <= cnt && i * p[j] <= N; j++) {
			f[i * p[j]] = true;
			if (i % p[j])
				mu[i * p[j]] = -mu[i];
			else {
				mu[i * p[j]] = 0;
				break;
			}
		}
	}
	for (int i = 1; i <= N; i++)
		for (int j = i; j <= N; j += i) xmu[j] = (xmu[j] + i * mu[i] + P) % P;
}

int n, x, ans, c[N + 5];
int main() {
	init();
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &x), c[x]++, ans = (ans + P - x) % P;
	for (int T = 1; T <= N; T++) {
		int la = 0;
		for (int i = 1; i <= N / T; i++) la = (la + 1ll * c[i * T] * i) % P;
		la = 1ll * la * la % P;
		ans = (ans + 1ll * la * T % P * xmu[T]) % P;
	}
	printf("%d\n", ((ans + P) * 499122177ll) % P);
}