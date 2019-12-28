#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51;

// a: >0
// b: =0
// c: =-1
// d: <-1
int n, a[N], sgn = 1, A, B, C, D, mn, mi, pos;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		if (!a[i]) pos = i, B++;
		if (a[i] == -1) pos = i, C++;
		if (a[i] > 0) A++;
		if (a[i] < -1) D++;
		if (a[i] >= 0) a[i] = -a[i] - 1;
		if (a[i] < 0 && mn < -a[i]) mn = -a[i], mi = i;
		sgn *= a[i] < 0 ? -1 : 1;
	}
	if (sgn < 0 && (A || D))
		a[mi] = -a[mi] - 1;
	else if (sgn < 0 && (B || C))
		a[pos] = 0;
	for (int i = 1; i <= n; i++) printf("%d ", a[i]);
}