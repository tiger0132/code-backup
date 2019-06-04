#include <algorithm>
#include <cstdio>
const int N = 2e5 + 52;
int n, a[N], b[2];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), b[a[i] % 2] = 1;
	if (!(b[0] && b[1]))
		for (int i = 1; i <= n; i++) printf("%d ", a[i]);
	else {
		std::sort(a + 1, a + n + 1);
		for (int i = 1; i <= n; i++) printf("%d ", a[i]);
	}
}