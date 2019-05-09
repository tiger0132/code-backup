// solution MODIFIED from stdcpp@darkbzoj (myself)

#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51;
int sz;
struct node {
	int op, l, r, x, *ans;
	bool operator<(const node& rhs) const { return l / sz == rhs.l / sz ? r < rhs.r : l < rhs.l; }
} q[N], q2[N];

int n, m1, m2, m, lim, mx, ans[N];
int a[N], cnt[N], lnk[N];
std::bitset<N> p, px;
inline void add(int x) { cnt[x]++ || (p[x] = px[N - x] = 1); }
inline void del(int x) { --cnt[x] || (p[x] = px[N - x] = 0); }

int rec[N];
inline void $(int i, int x) {
	for (; i <= n; i += i & -i) rec[i] = std::min(rec[i], x);
}
inline int $(int i) {
	int r = N;
	for (; i; i -= i & -i) r = std::min(r, rec[i]);
	return r;
}
int main() {
	scanf("%d%d", &n, &m);
	sz = ceil(sqrt(n));
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	lim = sqrt(mx = *std::max_element(a + 1, a + n + 1));
	for (int i = 1; i <= m; i++) {
		m1++;
		scanf("%d%d%d%d", &q[m1].op, &q[m1].l, &q[m1].r, &q[m1].x), q[m1].ans = ans + i;
		if (q[i].op == 4 && q[i].x < lim && q[i].x) q2[++m2] = q[m1--];
	}
	std::sort(q + 1, q + m1 + 1);
	for (int l = 1, r = 0, i = 1; i <= m1; i++) {
		while (l < q[i].l) del(a[l++]);
		while (l > q[i].l) add(a[--l]);
		while (r < q[i].r) add(a[++r]);
		while (r > q[i].r) del(a[r--]);
		switch (q[i].op) {
			case 1:
				*q[i].ans = (p & (p << q[i].x)).any();
				break;
			case 2:
				*q[i].ans = (p & (px >> (N - q[i].x))).any();
				break;
			case 3:
				for (int j = 1; j * j <= q[i].x; j++)
					if (q[i].x % j == 0 && p[j] && p[q[i].x / j]) {
						*q[i].ans = 1;
						break;
					}
				break;
			case 4:
				if (q[i].x)
					for (int j = q[i].x, k = 1; j <= mx; j += q[i].x, k++) {
						if (cnt[j] && cnt[k]) {
							*q[i].ans = 1;
							break;
						}
					}
				else
					*q[i].ans = cnt[0] && cnt[0] <= q[i].r - q[i].l;
		}
	}
	std::sort(q2 + 1, q2 + m2 + 1, [](const node& x, const node& y) { return x.x < y.x || (x.x == y.x && x.l < y.l); });
	for (int l = 1, r, rb; l <= m2; l = r + 1) {
		memset(rec, 0x3f, sizeof rec), memset(lnk, 0x3f, sizeof lnk), rb = q2[l].r;
		for (r = l; q2[r + 1].x == q2[l].x;) rb = std::max(rb, q2[++r].r);
		for (int j = l, k = rb; j <= r; j++) {
			while (k >= q2[j].l) {
				lnk[a[k]] = k;
				if (1ll * a[k] * q2[l].x <= mx) $(k, lnk[a[k] * q2[l].x]);
				if (a[k] % q2[l].x == 0) $(k, lnk[a[k] / q2[l].x]);
				k--;
			}
			if (q2[j].l > q2[j].r)
				*q2[j].ans = 0;
			else
				*q2[j].ans = $(q2[j].r) <= q2[j].r;
		}
	}
	for (int i = 1; i <= m; i++) puts(ans[i] ? "yuno" : "yumi");
}