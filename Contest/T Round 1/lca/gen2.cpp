#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int N = 3e3 + 33;

char in[233], path[2333];
int n, rt, a[N];
int main(int argc, char **argv) {
	srand((unsigned long long)new char);
	if (argc != 3) return puts("ERR"), 0;
	sprintf(path, "data/lca2-%s.in", argv[1]);
	freopen(path, "w", stdout);

	sscanf(argv[2], "%d", &n);
	rt = rand() % n + 1;

	printf("%d %d\n", n, rt);
	for (int i = 1; i <= n; i++)
		if (i != rt) printf("%d %d\n", rt, i);
}