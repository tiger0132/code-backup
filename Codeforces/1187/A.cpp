#include <algorithm>
#include <cmath>
#include <cstdio>

int n, a, b, x;
int main() {
	for (scanf("%*d"); ~scanf("%d%d%d", &n, &a, &b);) {
		printf("%d\n", n + 1 - std::min(a, b));
	}
}