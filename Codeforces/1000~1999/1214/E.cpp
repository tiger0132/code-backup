#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <vector>

const int N = 2e5 + 52;

struct node {
	int i, d;
	bool operator>(const node& rhs) const { return d > rhs.d; }
} a[N];

std::vector<int> v[N];
int n;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i].d), a[i].i = i;
	std::sort(a + 1, a + n + 1, std::greater<node>());
	for (int i = 1; i <= n; i++) v[i].push_back(2 * a[i].i - 1);
	for (int i = 1; i <= n; i++) v[i + a[i].d].push_back(2 * a[i].i);
	for (int i = 2; !v[i].empty(); i++) {
		printf("%d %d\n", v[i - 1].front(), v[i].front());
		for (int j = 1; j < v[i].size(); j++)
			printf("%d %d\n", v[i - 1].front(), v[i][j]);
	}
}