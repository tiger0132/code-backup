#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e6 + 61;

int n, s, a[N];
int main() {
	scanf("%d%d", &n, &s);
	if (s < 2 * n) return puts("NO"), 0;
	puts("YES");
	for (int i = 1; i < n; i++) printf("2 ");
	printf("%d\n1", s - 2 * n + 2);
}