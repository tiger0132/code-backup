#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>

const int N = 1e5 + 51;

std::map<int, int> mp;
long long ans;
int n, c, a[N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		++mp[a[i]];
		if (mp[a[i]] > 2 || mp[0] >= 2) return puts("cslnb"), 0;
		c += mp[a[i]] == 2;
	}
	std::sort(a + 1, a + n + 1);
	if (c > 1) return puts("cslnb"), 0;
	for (int i = 1; i <= n - 2; i++)
		if (a[i] + 1 == a[i + 1] && a[i + 1] == a[i + 2]) return puts("cslnb"), 0;
	for (int i = 1; i <= n; i++) (ans += a[i] - i + 1) %= 2;
	puts(ans % 2 ? "sjfnb" : "cslnb");
}