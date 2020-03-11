#include <algorithm>
#include <cstring>
#include <cstdio>
#include <map>

typedef long long ll;

const int N = 1e5 + 51;

std::map<ll, int> mp, res;
ll x, ans;
int n;
int main() {
	for (scanf("%*d"); ~scanf("%d", &n);) {
		ans = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%lld", &x);
			ans = std::max(ans, x);
			res.clear();
			res[x] = i;
			for (std::map<ll, int>::iterator it = mp.begin(); it != mp.end(); it++) {
				int id = it->second;
				ll v = std::__gcd(it->first, x);
				ans = std::max(ans, v * (i - id + 1));
				if (res.count(v))
					res[v] = std::min(res[v], id);
				else
					res[v] = id;
			}
			mp.swap(res);
		}
		printf("%lld\n", ans);
	}
}