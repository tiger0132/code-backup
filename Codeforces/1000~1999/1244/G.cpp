#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 1e6 + 61;

int n, l, r, a[N];
ll k, c;
int main() {
	scanf("%d%lld", &n, &k);
	if ((c = n * (n + 1ll) / 2) > k) return puts("-1"), 0;
	for (int i = 1; i <= n; i++) a[i] = i;
	l = 1, r = n;
	for (; l < r && c < k; l++, r--) {
		int rb = std::min((ll)r - l, k - c);
		std::swap(a[l], a[l + rb]), c += rb;
	}
	printf("%lld\n", c);
	for (int i = 1; i <= n; i++) printf("%d%c", i, " \n"[i == n]);
	for (int i = 1; i <= n; i++) printf("%d ", a[i]);
}