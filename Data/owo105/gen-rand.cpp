#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e6 + 62;

int rnd(int l, int r) { return rand() % (r - l + 1) + l; }

int n, k, p[N], z[N], id[N], d[N], vis[N][26];
int main(int argc, char **argv) {
	srand((unsigned long long)new char);
	sscanf(argv[2], "%d", &n);
	sscanf(argv[3], "%d", &k);
	freopen(argv[1], "w", stdout);
	printf("%d\n", n);
	for (int i = 1; i <= n; i++) i[id] = i;
	for (int i = 2; i <= n; i++) {
		do
			i[p] = rnd(1, i - 1);
		while (i[p][d] == k);
		do
			i[z] = rnd(0, k - 1);
		while (i[p][vis][i[z]]);
		i[p][d]++;
		i[p][vis][i[z]] = 1;
	}
	std::random_shuffle(id + 2, id + n + 1);
	for (int i = 2; i <= n; i++) {
		printf("%d %d %c\n", i[p][id], i[id], i[z] + 'a');
	}
}