#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <stack>
#include <vector>

typedef std::pair<int, int> pii;
const int N = 1e6 + 61;

struct rec {
	int *p, v;
};
std::stack<rec> st;
void set(int& x, int y) { st.push({&x, x}), x = y; }

int p[N], d[N];
int f(int x) { return x[p] ? f(x[p]) : x; }
void mg(int x, int y) {
	if ((x = f(x)) != (y = f(y))) {
		if (x[d] > y[d]) std::swap(x, y);
		set(x[p], y), set(y[d], y[d] + (x[d] == y[d]));
	}
}

std::map<pii, std::vector<pii>> mp;
int n, m, k, a[N], c[N], fl[N], sb;
long long ans;
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), c[a[i]]++;
	ans = k * (k - 1ll) / 2;
	sb = k - 1;
	for (int i = 1, x, y; i <= m; i++) {
		scanf("%d%d", &x, &y);
		if (a[x] > a[y]) std::swap(x, y);
		if (a[x] == a[y]) {
			if (fl[a[x]]) continue;
			if (f(x) == f(y)) {
				fl[a[x]] = 1;
				ans -= sb--;
			}
			mg(x + n, y), mg(x, y + n);
		} else
			mp[pii(a[x], a[y])].emplace_back(x, y);
	}
	for (auto [a, b] : mp)
		if (!fl[a.first] && !fl[a.second]) {
			int sz = st.size();
			for (auto [u, v] : b) {
				if (f(u) == f(v)) {
					ans--;
					break;
				}
				mg(u + n, v);
				mg(u, v + n);
			}
			while (st.size() > sz) *st.top().p = st.top().v, st.pop();
		}
	printf("%lld\n", ans);
}