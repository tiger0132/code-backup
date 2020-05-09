#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <set>
#include <utility>
#include <vector>

typedef std::pair<int, int> pii;
const int N = 4e5 + 54;

int n, l, r, a[N], b[N], flag;
std::vector<pii> v[N];
std::set<pii> s;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &l, &r);
		l[v].push_back({r, i});
	}
	for (int i = 1; i <= n; i++, s.erase(s.begin())) {
		for (pii& j : i[v]) s.insert(j);
		a[s.begin()->second] = i;
	}
	for (int i = 1; i <= n; i++, s.erase(s.begin())) {
		for (pii& j : i[v]) s.insert(j);
		if (s.size() > 1 && a[(++s.begin())->second] <= s.begin()->first) {
			memcpy(b, a, sizeof a), flag = 1;
			std::swap(b[s.begin()->second], b[(++s.begin())->second]);
			break;
		}
	}
	puts(flag ? "NO" : "YES");
	for (int i = 1; i <= n; i++) printf("%d%c", a[i], " \n"[i == n]);
	if (flag)
		for (int i = 1; i <= n; i++) printf("%d%c", b[i], " \n"[i == n]);
}