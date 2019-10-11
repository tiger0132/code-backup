#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define L ch][0
#define R ch][1
const int N = 5e5 + 55;
int ch[N][2], sz[N], v[N], pri[N], rt, nc;
void up(int x) { x[sz] = x[L][sz] + x[R][sz] + 1; }
int alloc(int x) { return (++nc)[sz] = 1, nc[v] = x, nc[pri] = rand(), nc; }
void spl(int id, int k, int& x, int& y) {
	if (!id) return void(x = y = 0);
	if (id[v] <= k) return x = id, spl(id[R], k, x[R], y), up(x);
	y = id, spl(id[L], k, x, y[L]), up(y);
}
int u(int x, int y) {
	if (!x || !y) return x | y;
	if (x[pri] < y[pri]) return x[R] = u(x[R], y), up(x), x;
	return y[L] = u(x, y[L]), up(y), y;
}
int kth(int x, int k) {
	if (k <= x[L][sz]) return kth(x[L], k);
	return (k -= x[L][sz] + 1) <= 0 ? x : kth(x[R], k);
}

int t, op, a, x, y, z;
int main() {
	scanf("%d", &t);
	srand((unsigned long long)new char);
	while (t--) {
		scanf("%d%d", &op, &a);
		if (op == 1) {
			spl(rt, a, x, y);
			rt = u(u(x, alloc(a)), y);
		} else if (op == 2) {
			spl(rt, a, x, z);
			spl(x, a - 1, x, y);
			y = u(y[L], y[R]);  // 注意，可能有多个权值相同的点
			rt = u(u(x, y), z);
		} else if (op == 3) {
			spl(rt, a - 1, x, y);
			printf("%d\n", x[sz] + 1);
			rt = u(x, y);
		} else if (op == 4)
			printf("%d\n", kth(rt, a)[v]);
		else if (op == 5) {
			spl(rt, a - 1, x, y);
			printf("%d\n", kth(x, x[sz])[v]);
			rt = u(x, y);
		} else {
			spl(rt, a, x, y);
			printf("%d\n", kth(y, 1)[v]);
			rt = u(x, y);
		}
	}
}