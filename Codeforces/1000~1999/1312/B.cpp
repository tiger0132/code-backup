#include <algorithm>
#include <cstring>
#include <cstdio>
#include <functional>

const int N = 1e2 + 21;

int n, a[N];
int main() {
	for (scanf("%*d"); ~scanf("%d", &n);) {
		for (int i = 1; i <= n; i++) scanf("%d", a + i);
		std::sort(a + 1, a + n + 1, std::greater<int>());
		for (int i = 1; i <= n; i++) printf("%d%c", a[i], " \n"[i == n]);
	}
}