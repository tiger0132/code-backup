#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <unordered_map>
#define int long long

const int N = 2e6 + 62;

std::unordered_map<int, int> mp;
int P, div2, div6;

inline int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = x * x % P)
		if (y & 1) r = r * x % P;
	return r;
}
inline int sum(int x) {
	x %= P;
	return x * (x + 1) % P * div2 % P;
}
inline int sum2(int x) {
	x %= P;
	return x * (x + 1) % P * (2 * x + 1) % P * div6 % P;
}
inline int sum3(int x) { return sum(x) * sum(x) % P; }

int phi[N];
int S(int n) {
	if (n < N) return phi[n];
	if (mp[n]) return mp[n];
	int ret = sum3(n);
	for (int l = 2, r; l <= n; l = r + 1) {
		r = n / (n / l);
		ret = (ret - S(n / l) * (sum2(r) - sum2(l - 1)) % P) % P;
	}
	return mp[n] = (ret + P) % P;
}

int p[N], cnt, t, n, ans;
bool f[N];
signed main() {
	scanf("%lld%lld", &P, &n);
	f[1] = true, phi[1] = 1;
	for (int i = 2; i < N; i++) {
		if (!f[i]) p[++cnt] = i, phi[i] = i - 1;
		for (int j = 1; j <= cnt && i * p[j] < N; j++) {
			f[i * p[j]] = true;
			if (i % p[j])
				phi[i * p[j]] = phi[i] * (p[j] - 1);
			else {
				phi[i * p[j]] = phi[i] * p[j];
				break;
			}
		}
	}
	for (int i = 1; i < N; i++) phi[i] = (i * i % P * phi[i] % P + phi[i - 1]) % P;
	div2 = pw(2, P - 2), div6 = pw(6, P - 2);
	for (int l = 1, r; l <= n; l = r + 1) {
		r = n / (n / l);
		ans = (ans + sum3(n / l) * (S(r) - S(l - 1)) % P) % P;
	}
	printf("%lld", (ans + P) % P);
}