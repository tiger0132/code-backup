#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 1e5 + 51;

int n, l, r, ans;
ll k, t, a[N];
int main() {
	scanf("%d%lld", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i);
	std::sort(a + 1, a + n + 1);
	l = 1, r = n, ans = a[n] - a[1];
	do
		if (l < n - r + 1)
			t = std::min(a[l + 1] - a[l], k / l), k -= t * l++;
		else
			t = std::min(a[r] - a[r - 1], k / (n - r + 1)), k -= t * (n - --r);
	while (ans -= t, l < r && k);
	printf("%d", ans);
}