#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>
#define int long long

const int N = 7e3 + 37;
int n, a[N], b[N], ans;
std::multiset<int> s;
bool v[N];
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i), s.insert(a[i]);
	for (int i = 1; i <= n; i++) scanf("%lld", b + i);
	for (int i = 1; i <= n; i++)
		if (s.count(a[i]) > 1)
			for (int j = 1; j <= n; j++)
				if (!v[j] && ((a[i] | a[j]) == a[i])) v[j] = true, ans += b[j];
	printf("%lld", ans);
}