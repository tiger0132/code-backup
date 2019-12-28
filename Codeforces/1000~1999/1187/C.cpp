#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>

typedef std::pair<int, int> pii;
const int N = 1e3 + 31;

int n, m, op, x, y, lb;
std::vector<pii> v;
int ans[N];
bool f[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &op, &x, &y);
		if (op == 1)
			for (int j = x + 1; j <= y; j++) f[j] = true;
		else
			v.push_back({x, y});
	}
	for (auto i : v) {
		for (int j = i.first + 1; j <= i.second; j++)
			if (!f[j]) {
				ans[j] = -1;
				goto end;
			}
		return puts("NO"), 0;
	end:;
	}
	puts("YES");
	for (int i = 1; i <= n; i++) lb = std::min(lb, ans[i] += ans[i - 1]);
	for (int i = 1; i <= n; i++) printf("%d ", -lb + ans[i] + 1);
}