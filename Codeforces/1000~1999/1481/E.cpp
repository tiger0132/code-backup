#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 5e5 + 55;

int n, a[N], cnt[N], l[N], r[N], f[N], mx, ans;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) l[i] = 1e9, r[i] = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		l[a[i]] = std::min(l[a[i]], i);
		r[a[i]] = std::max(r[a[i]], i);
		cnt[a[i]]++;
	}
	for (int i = 1; i <= n; i++) {
		f[i] = f[i - 1];
		if (i == r[a[i]]) f[i] = std::max(f[i], f[l[a[i]] - 1] + cnt[a[i]]);
	}
	for (int i = 1; i <= n; i++) cnt[i] = 0;
	for (int i = n; i >= 1; i--) {
		ans = std::max(ans, f[i] + mx);
		mx = std::max(mx, ++cnt[a[i]]);
	}
	printf("%d\n", n - std::max(ans, mx));
}