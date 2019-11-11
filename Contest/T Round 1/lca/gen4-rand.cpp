// 先写个随机的，敢利用这个性质的话，来一个卡一个

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
	sprintf(path, "data/lca4r-%s.in", argv[1]);
	freopen(path, "w", stdout);

	sscanf(argv[2], "%d", &n);

	printf("%d %d\n", n, rand() % n + 1);
	for (int i = 1; i < n; i++) printf("%d %d\n", rand() % i + 1, i + 1);
}