#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>

const int N = 2e5 + 52;

int n, m, x, ans[N], top;
std::set<int> s;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		if (!s.count(x)) {
			s.insert(x);
			ans[++top] = x;
			if (top > m) s.erase(ans[top - m]);
		}
	}
	printf("%d\n", std::min(m, top));
	for (int i = top; i >= std::max(1, top - m + 1); i--) printf("%d ", ans[i]);
}