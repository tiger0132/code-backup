#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
ll a, b, ans;
int main() {
	scanf("%lld%lld", &a, &b);
	if (a == b) return puts("0"), 0;
	if (a > b) std::swap(a, b);
	for (ll k = 1ll << 62; k; k >>= 1)
		if ((a & k) != (b & k) || a + k <= b) ans += k;
	printf("%lld", ans);
}