#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <set>
#include <utility>
#define x first
#define y second

const int N = 2e5 + 52, M = 2e5;

struct line {
	int l, r, id;
	bool operator<(const line& rhs) const { return r < rhs.r; }
};

int n, k, l, r, out[N], top;
std::multiset<line> s;
line a[N];
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d%d", &l, &r), a[i] = {l, r, i};
	std::sort(a + 1, a + n + 1, [](const line& x, const line& y) { return x.l < y.l; });
	for (int i = 1, j = 1; i <= M; i++) {
		while (a[j].l == i && j <= n) s.insert(a[j++]);
		while (!s.empty() && s.begin()->r < i) s.erase(s.begin());
		while (s.size() > k) {
			out[++top] = s.rbegin()->id;
			s.erase(--s.end());
		}
	}
	printf("%d\n", top);
	while (top) printf("%d ", out[top--]);
}