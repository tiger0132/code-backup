#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

const int N = 5e5 + 55;

int n, a[N], b[N], res[N], l[N], h[N], top;
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i);
	int ans = 0, mi, siz = 0;
	for (int i = 1; i <= n; i++) {
		int cl = 1;
		while (h[top] >= a[i]) {
			siz -= l[top] * h[top];
			cl += l[top--];
		}
		h[++top] = a[i], l[top] = cl;
		res[i] = siz += cl * a[i];
	}
	siz = 0, top = 0;
	ans = res[n], mi = n;
	for (int i = n; i >= 1; i--) {
		int cl = 1;
		while (h[top] >= a[i]) {
			siz -= l[top] * h[top];
			cl += l[top--];
		}
		h[++top] = a[i], l[top] = cl;
		siz += cl * a[i];
		if (siz + res[i - 1] > ans) ans = siz + res[i - 1], mi = i - 1;
	}
	b[mi] = a[mi];
	for (int j = mi - 1, c = a[mi]; j >= 1; j--) b[j] = c = std::min(c, a[j]);
	for (int j = mi + 1, c = a[mi]; j <= n; j++) b[j] = c = std::min(c, a[j]);
	for (int i = 1; i <= n; i++) printf("%lld ", b[i]);
}