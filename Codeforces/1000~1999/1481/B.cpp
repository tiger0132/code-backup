#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e2 + 21;

int n, h[N], mx[N];
int calc(int l, int r, int k) {
	mx[r] = h[r];
	for (int i = r - 1; i >= l; i--) mx[i] = std::max(mx[i + 1], h[i]);
	for (int i = l, cnt = 0, last = i; i <= r; i++) {
		cnt += mx[i] - h[i];
		if (mx[i] == h[i]) {
			if (k <= cnt) return calc(last, i - 1, k);
			k -= cnt;
			last = i + 1;
			cnt = 0;
		}
	}
	if (l == 1 && r == n) return -1;
	for (int i = r, cur = 0; i >= l; i--)
		if (h[i] > cur) {
			int dh = h[i] - cur, dl = r - i;
			if (k <= dh * dl) return r - (k - 1) % dl;
			k -= dh * dl;
			cur = h[i];
		}
	return r - (k - 1) % (r - l + 1);
}

int k;
int main() {
	for (scanf("%*d"); ~scanf("%d%d", &n, &k);) {
		mx[n + 1] = 0;
		for (int i = 1; i <= n; i++) scanf("%d", h + i);
		printf("%d\n", calc(1, n, k));
	}
}