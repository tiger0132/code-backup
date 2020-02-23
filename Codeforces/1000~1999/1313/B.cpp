#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

int n, x, y;

int main() {
	for (scanf("%*d"); ~scanf("%d%d%d", &n, &x, &y);) {
		printf("%d %d\n", std::min(n, std::max(1, x + y - n + 1)),
			   std::min(x + y - 1, n));
	}
}