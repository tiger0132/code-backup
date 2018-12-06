#include <algorithm>
#include <cstdio>
#include <ctime>
#define int unsigned
#define rand rand_xorshift

const int N = 1e4;

int seed;

int rand_xorshift() {
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}

int t;

signed main() {
	seed = (unsigned long long)new char;
	freopen("in.in", "w", stdout);
	t = 1;
	for (printf("%u\n", t); t--; ) {
		printf("%u\n", N);
		for (int i = 1; i < N; i++) {
			int z = rand() % (int)1e8;
			printf("%u %u %u\n", i, i+1, z);
		}
		for (int i = 1; i <= N; i++) {
			int op = rand()%2, x = rand()%N + 1, y = rand()%N + 1;
			if (!op) y = x;
			/*while (!op && x == y) {
				x = rand()%N + 1;
				y = rand()%N + 1;
			}*/
			if (op == 1 && rand() % 2) std::swap(x, y);
			if (op == 1) {
				x = std::min(x, N-1);
				y = std::min(y, N-1);
			}
			printf("%s %u %u\n", op ? "QUERY" : "CHANGE", x, y);
		}
		puts("DONE");
	}
}