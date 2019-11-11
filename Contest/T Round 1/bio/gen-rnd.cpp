#include <algorithm>
#include <cstdio>
#include <cstring>
#define int unsigned

const int N = 7e6 + 67;

int cnt1[256], cnt2[256], cnt3[256], cnt4[256];
void sort(int n, int *a, int *b) {
	memset(cnt1, 0, sizeof cnt1);
	memset(cnt2, 0, sizeof cnt2);
	memset(cnt3, 0, sizeof cnt3);
	memset(cnt4, 0, sizeof cnt4);
	for (register int i = 1; i <= n; i++) {
		cnt1[(a[i]) & 255]++;
		cnt2[(a[i] >> 8) & 255]++;
		cnt3[(a[i] >> 16) & 255]++;
		cnt4[(a[i] >> 24) & 255]++;
	}
	for (register int i = 1; i < 256; i++) {
		cnt1[i] += cnt1[i - 1];
		cnt2[i] += cnt2[i - 1];
		cnt3[i] += cnt3[i - 1];
		cnt4[i] += cnt4[i - 1];
	}
	for (register int i = n; i; i--) b[cnt1[(a[i]) & 255]--] = a[i];
	for (register int i = n; i; i--) a[cnt2[(b[i] >> 8) & 255]--] = b[i];
	for (register int i = n; i; i--) b[cnt3[(a[i] >> 16) & 255]--] = a[i];
	for (register int i = n; i; i--) a[cnt4[(b[i] >> 24) & 255]--] = b[i];
}

int n, m, a0[N], a[N], b0[N], b[N], K;
char in[233], out[233];
long long ans;
signed main(int argc, char **argv) {
	if (argc != 5) return puts("ERR"), 0;
	sprintf(in, "data/bio%s.in", argv[1]);
	sprintf(out, "data/bio%s.out", argv[1]);

	freopen(in, "w", stdout);
	sscanf(argv[2], "%u", &n);
	sscanf(argv[3], "%u", &m);
	sscanf(argv[4], "%u", &K);
	srand((unsigned long long)new char);
	printf("%u %u\n", n, m);
	for (int i = 1; i <= n; i++) a0[i] = rand() % K;
	for (int i = 1; i <= m; i++) b0[i] = rand() % K;
	fputs("Rand finished.\n", stderr);
	sort(n, a0, a);
	fputs("a[] sorted.\n", stderr);
	sort(m, b0, b);
	fputs("b[] sorted.\n", stderr);
	for (int i = 1; i <= n; i++) printf("%u%c", a[i], " \n"[i == n]);
	for (int i = 1; i <= m; i++) printf("%u%c", b[i], " \n"[i == m]);
	fputs("*.in generated.\n", stderr);

	freopen(out, "w", stdout);
	for (int i = 1, p = 0; i <= m; i++) {
		for (; a[p] <= b[i] && p <= n;) p++;
		ans += n - p + 1;
	}
	printf("%lld", ans);
}