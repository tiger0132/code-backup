#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 4e5 + 54;

int n, a[N];
int main() {
	for (scanf("%*d"); ~scanf("%d", &n);) {
		for (int i = 1; i <= n * 2; i++) scanf("%d", a + i);
		std::sort(a + 1, a + 2 * n + 1);
		printf("%d\n", abs(a[n] - a[n + 1]));
	}
}