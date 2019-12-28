#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>

const int N = 1e3 + 31;

std::map<int, int> mp;
int n, ans, a[N];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			mp[a[i] + a[j]]++;
		}
	}
	for (auto i : mp) ans = std::max(ans, i.second);
	printf("%d", ans);
}