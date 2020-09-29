#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51;

int n, x;
int main() {
	for (scanf("%*d"); ~scanf("%d%d", &n, &x);) {
		if (n <= 2)
			puts("1");
		else
			printf("%d\n", (n - 3) / x + 2);
	}
}