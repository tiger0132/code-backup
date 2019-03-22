#include <algorithm>
#include <cstdio>

typedef long long ll;
const int N = 1e2+21;

ll a[N];
void insert(ll x) {
	for (int i = 50; i >= 0; i--) {
		if (1 & ~(x >> (ll)i)) continue;
		if (!a[i]) { a[i] = x; return; }
		x ^= a[i]; 
	}
}
ll x, ans;
int n;
int main() {
	for (scanf("%d", &n); n--; insert(x)) scanf("%lld", &x);
	for (int i = 50; i >= 0; i--) {
		ans = std::max(ans, ans ^ a[i]);
	}
	printf("%lld", ans);
}