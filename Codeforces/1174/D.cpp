#include <algorithm>
#include <cmath>
#include <cstdio>

const int N = 3e6 + 63;
int n, x, l, t, a[N];
int main() {
	scanf("%d%d", &n, &x);
	if (x > (1 << n))
		x = 0;
	else
		x = x & -x;
	for (int i = 1; i < (1 << n); i++) {
		if (x & i) continue;
		a[++t] = i ^ l, l = i;
	}
	printf("%d\n", t);
	// for (int i = 1; i <= t; i++) printf("%d ", a[i]);
}