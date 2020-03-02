#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;

const int K = 55;

ll p[K], p2[K];
int c, f0;
void ins(ll x) {
	for (int i = 51; ~i; i--)
		if ((x >> i) & 1) {
			if (!p[i]) return p[i] = x, void();
			x ^= p[i];
		}
	f0 = 1;
}
ll qry(ll x) {
	ll r = 0;
	for (; x; x ^= x & -x) r ^= p2[__builtin_ctzll(x)];
	return r;
}

int n;
ll x;
int main() {
	for (scanf("%d", &n); n--; ins(x)) scanf("%lld", &x);
	for (int i = 51; i; i--)
		for (int j = i - 1; ~j; j--)
			if ((p[i] >> j) & 1) p[i] ^= p[j];
	for (int i = 0; i <= 51; i++)
		if (p[i]) p2[c++] = p[i];
	for (scanf("%*d"); ~scanf("%lld", &x);) {
		if ((x -= f0) > (1ll << (ll)c) - !f0)
			puts("-1");
		else
			printf("%lld\n", qry(x));
	}
}