#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <map>

std::map<int, int> mp;
int n, s, x, r, k, ans;
int a[444444];
int main() {
	scanf("%d%d", &n, &s);
	for (int i = 1; i <= n; i++) scanf("%d", &x), mp[x]++;
	for (auto i : mp) a[r + 1] = i.second + a[r], r++;
	for (k = 0; (k + 1) * n <= s * 8;) k++;
	n = r;
	ans = 1e9;
	k = std::min(k, 30);
	k = 1 << k;
	if (k > n) return puts("0"), 0;
	for (int i = 1; i <= n - k + 1; i++)
		ans = std::min(ans, a[n] - a[i + k - 1] + a[i - 1]);
	printf("%d", ans);
}