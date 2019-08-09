#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

typedef long long ll;
const int N = 2.7e5, M = 19;
int P;

struct comp {
	int x, y;
};
inline comp mul(comp a, comp b, int w) {
	return {(1ll * a.x * b.x % P + 1ll * w * a.y % P * b.y % P) % P,
			(1ll * a.x * b.y % P + 1ll * a.y * b.x % P) % P};
}
int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = ll(x) * x % P)
		if (y & 1) r = ll(r) * x % P;
	return r;
}
inline int pw(comp x, int y, int w) {
	comp r = {1, 0};
	for (; y; y >>= 1, x = mul(x, x, w))
		if (y & 1) r = mul(r, x, w);
	return std::min(r.x, P - r.x);
}
inline int cipolla(int x) {
	if (pw(x, (P - 1) / 2) == P - 1) return -1;
	while (1) {
		int a = rand(), w = (1ll * a * a - x + P) % P;
		if (pw(w, (P - 1) / 2) == P - 1) return pw({a, 1}, (P + 1) / 2, w);
	}
}

int t, x, a;
int main() {
	srand(time(0));
	for (scanf("%d", &t); t--;) {
		scanf("%d%d", &x, &P);
		if (!x)
			puts("0");
		else if (pw(x, (P - 1) / 2) == P - 1)
			puts("Hola!");
		else {
			a = cipolla(x);
			a = std::min(a, P - a);
			if (a != P - a) printf("%d ", a);
			printf("%d\n", P - a);
		}
	}
}