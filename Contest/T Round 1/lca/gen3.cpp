#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int N = 3e3 + 33;

char in[233], path[2333];
int n, a[N];
int main(int argc, char **argv) {
	srand((unsigned long long)new char);
	if (argc != 3) return puts("ERR"), 0;
	sprintf(path, "data/lca3-%s.in", argv[1]);
	freopen(path, "w", stdout);

	sscanf(argv[2], "%d", &n);
	for (int i = 1; i <= n; i++) a[i] = i;
	std::random_shuffle(a + 1, a + n + 1);

	printf("%d %d\n", n, a[1]);
	for (int i = 2; i <= n; i++) printf("%d %d\n", a[i / 2], a[i]);
}