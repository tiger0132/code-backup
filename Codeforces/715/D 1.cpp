#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#define A C1(m - 1, m + 1, m, m + 1)
#define B C1(m - 1, m + 2, m, m + 2)
#define C C1(m + 1, m - 1, m + 1, m)
#define D C1(m + 2, m - 1, m + 2, m)
#define X C2(m - 1, m, m - 1, m + 1)
#define Y C2(m - 2, m, m - 2, m + 1)
#define Z C2(m - 2, m + 1, m - 2, m + 2), C2(m - 3, m + 1, m - 3, m + 2)

typedef long long l;
const int N = 3e2 + 23;
struct {
	int a, b, c, d;
} a[N];
int n, m2, b[N], c;
l tt;

void C1(int x, int y, int z, int w) {
	if (1 <= std::min({x, y, z, w}) && std::max({x, y, z, w}) <= n) a[++m2] = {x, y, z, w};
}
void C2(int x, int y, int z, int w) { C1(x, y, z, w), C1(y, x, w, z); }
int main() {
	scanf("%lld", &tt);
	for (; tt; tt /= 6) b[++c] = tt % 6;
	n = 2 * c + 2;
	printf("%d %d\n", n, n);
	C1(2, 1, 2, 2), C2(3, 1, 3, 2), C2(4, 1, 4, 2);
	if (b[c]) {
		if (b[c] <= 3) C1(2, 2, 3, 2);
		if (b[c] != 3) C1(2, 3, 2, 4);
		if (b[c] == 1) C1(3, 3, 3, 4);
		if (b[c] == 4) C1(3, 2, 4, 2);
	}
	for (int m = 4, i = c - 1; i >= 1; i--, m += 2) {
		A, X, Y, Z;
		if (b[i] == 0) B, C, D;
		if (b[i] == 1) B, C;
		if (b[i] == 2) C;
		if (b[i] == 3) B, D;
		if (b[i] == 4) B;
	}
	printf("%d\n", m2);
	for (int i = 1; i <= m2; i++) printf("%d %d %d %d\n", a[i].a, a[i].b, a[i].c, a[i].d);
}