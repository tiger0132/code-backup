#include <algorithm>
#include <cstdio>
#include <cstring>

#define L ch][0
#define R ch][1
#define mid (l + r) / 2
const int N = 4e5 + 54;
int ch[N][2], ans[N], nc;
double mx[N];
void up(int x) { x[mx] = std::max(x[L][mx], x[R][mx]); }
int up2(int x, int y, int l, int r) {
	if (l == r) return x[mx] < y[mx];
	return x[mx] < y[L][mx] ? up2(x, y[L], l, mid) + y[ans] - y[L][ans]
							: up2(x, y[R], mid + 1, r);
}
void build(int x, int l, int r) {
	if (l == r) return;
	build(x[L] = ++nc, l, mid), build(x[R] = ++nc, mid + 1, r), up(x);
}
void upd(int x, int l, int r, int y, double z) {
	if (l == r) return (void)(x[mx] = z, x[ans] = 1);
	y <= mid ? upd(x[L], l, mid, y, z) : upd(x[R], mid + 1, r, y, z);
	up(x), x[ans] = x[L][ans] + up2(x[L], x[R], mid + 1, r);
}

int n, x, y;
int main() {
	scanf("%d%*d", &n);
	for (build(nc = 1, 1, n); ~scanf("%d%d", &x, &y);) {
		upd(1, 1, n, x, 1. * y / x);
		printf("%d\n", 1 [ans]);
	}
}