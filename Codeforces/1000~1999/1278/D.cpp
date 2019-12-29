#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>
#include <utility>

typedef std::pair<int, int> pii;
const int N = 1e6 + 61;

int p[N];
int f(int x) { return x[p] ? x[p] = f(x[p]) : x; }

int n, m, x, y, l[N], r[N], id[N], cnt;
std::multiset<pii> s;
pii intv[N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", l + i, r + i);
		i[l][id] = i[r][id] = i;
		i[intv] = {i[r], i};
	}
	for (int i = 1; i <= 2 * n; i++) {
		if (s.count(i[intv]))
			s.erase(i[intv]);
		else {
			for (const pii& j : s) {
				if (j.first > y[r]) break;
				int s, t;
				if ((s = f(y)) == (t = f(j.second))) return puts("NO"), 0;
				if (++cnt >= n) return puts("NO"), 0;
				s[p] = t;
			}
			s.insert(i[intv]);
		}
	}
	puts(cnt == n - 1 ? "YES" : "NO");
}