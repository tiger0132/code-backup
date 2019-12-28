#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>
#include <utility>
#define int long long
#define f second
#define ddl first
#define T(x) (p[x].f ? b : a)

typedef std::pair<int, int> pii;
const int N = 2e5 + 52;

int n, t, a, b, tm, acnt, bcnt, lans, ans;
pii p[N];
signed main() {
	for (scanf("%*d"); ~scanf("%lld%lld%lld%lld", &n, &t, &a, &b);) {
		tm = ans = acnt = bcnt = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%lld", &p[i].f);
			(p[i].f ? bcnt : acnt)++;
		}
		for (int i = 1; i <= n; i++) scanf("%lld", &p[i].ddl);
		p[n + 1] = {t + 1, 2};
		std::sort(p + 1, p + n + 1);
		for (int i = 0; i <= n; i++) {
			if (i) {
				tm += T(i);
				(p[i].f ? bcnt : acnt)--;
			}
			if (tm >= p[i + 1].ddl) continue;
			int gap = p[i + 1].ddl - tm - 1;
			lans = i;
			lans += std::min(acnt, gap / a);
			gap -= std::min(acnt, gap / a) * a;
			lans += std::min(bcnt, gap / b);
			gap -= std::min(acnt, gap / b) * b;
			ans = std::max(ans, lans);
		}
		printf("%lld\n", ans);
	}
}