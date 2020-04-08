// **

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>
#define int long long

const int N = 5e5 + 55;

int n, v[N], p[N], mx[N], cnt;
std::multiset<int> s;
signed main() {
	scanf("%lld", &n);
	v[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!v[i]) p[++cnt] = i;
		for (int j = 1; j <= cnt && i * p[j] <= n; j++) {
			v[i * p[j]] = 1, s.insert(i);
			if (i % p[j] == 0) break;
		}
	}
	for (int i = 1; i <= cnt; i++) printf("1 ");
	for (int i : s) printf("%lld ", i);
}