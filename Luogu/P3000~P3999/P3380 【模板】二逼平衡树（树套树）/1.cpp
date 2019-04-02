// 表白 lambda function!
// 太太太好用啦

#include <algorithm>
#include <cstdio>

const int N = 1e5 + 51;
int newNode(int, int, int);
extern struct node _[];
struct node {
	int lc, rc, v;
	int insert(int l, int r, int x, int o) {
		int mid = (l + r) / 2;
		if (l == r) return newNode(0, 0, v + o);
		if (x <= mid) return newNode(_[lc].insert(l, mid, x, o), rc, v + o);
		return newNode(lc, _[rc].insert(mid + 1, r, x, o), v + o);
	}
} _[N * 220];
inline int newNode(int lc, int rc, int v) {
	static int ptr = 1;
	_[ptr].lc = lc, _[ptr].rc = rc, _[ptr].v = v;
	return ptr++;
}

static int L[N], R[N], rt[N];
static int n, m, cl, cr, n$, i, j;
inline int lowbit(int x) { return x & -x; }
int querykth(int x, int l = 1, int r = n$) {
	if (l == r) return l;
	int sum = 0, mid = (l + r) / 2;
	for (i = 1; i <= cr; i++) sum += _[_[R[i]].lc].v;
	for (i = 1; i <= cl; i++) sum -= _[_[L[i]].lc].v;
	if (x <= sum) {
		for (i = 1; i <= cl; i++) L[i] = _[L[i]].lc;
		for (i = 1; i <= cr; i++) R[i] = _[R[i]].lc;
		return querykth(x, l, mid);
	} else {
		for (i = 1; i <= cl; i++) L[i] = _[L[i]].rc;
		for (i = 1; i <= cr; i++) R[i] = _[R[i]].rc;
		return querykth(x - sum, mid + 1, r);
	}
}
int queryrk(int x, int l = 1, int r = n$) {
	if (l == r) return 1;
	int sum = 0, mid = (l + r) / 2;
	for (i = 1; i <= cr; i++) sum += _[_[R[i]].lc].v;
	for (i = 1; i <= cl; i++) sum -= _[_[L[i]].lc].v;
	if (x <= mid) {
		for (i = 1; i <= cl; i++) L[i] = _[L[i]].lc;
		for (i = 1; i <= cr; i++) R[i] = _[R[i]].lc;
		return queryrk(x, l, mid);
	} else {
		for (i = 1; i <= cl; i++) L[i] = _[L[i]].rc;
		for (i = 1; i <= cr; i++) R[i] = _[R[i]].rc;
		return queryrk(x, mid + 1, r) + sum;
	}
}
int querysz(int x, int l = 1, int r = n$) {
	int sum = 0;
	for (i = 1; i <= cr; i++) sum += _[R[i]].v;
	for (i = 1; i <= cl; i++) sum -= _[L[i]].v;
	if (l == r) return sum;
	int mid = (l + r) / 2;
	if (x <= mid) {
		for (i = 1; i <= cl; i++) L[i] = _[L[i]].lc;
		for (i = 1; i <= cr; i++) R[i] = _[R[i]].lc;
		return querysz(x, l, mid);
	} else {
		for (i = 1; i <= cl; i++) L[i] = _[L[i]].rc;
		for (i = 1; i <= cr; i++) R[i] = _[R[i]].rc;
		return querysz(x, mid + 1, r);
	}
}
inline void add(int x, int y, int o) {
	for (i = x; i <= n; i += lowbit(i)) rt[i] = _[rt[i]].insert(1, n$, y, o);
}
template <typename F>
inline int $(F f, int l, int r, int x) {
	cl = cr = 0;
	for (j = l - 1; j; j -= lowbit(j)) L[++cl] = rt[j];
	for (j = r; j; j -= lowbit(j)) R[++cr] = rt[j];
	return f(x);
}

static int src[N], op[N], a[N], b[N], c[N], t[N], cnt[N], tmprk;
int main() {
	register int i;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; i++) scanf("%d", src + i), t[++n$] = src[i];
	for (i = 1; i <= m; i++) {
		scanf("%d%d%d", op + i, a + i, b + i);
		if (op[i] != 3) {
			scanf("%d", c + i);
			if (op[i] != 2) t[++n$] = c[i];
		} else
			t[++n$] = b[i];
	}
	std::sort(t + 1, t + n$ + 1);
	n$ = std::unique(t + 1, t + n$ + 1) - t - 1;
	for (i = 1; i <= m; i++) {
		if (op[i] == 3)
			b[i] = std::lower_bound(t + 1, t + n$ + 1, b[i]) - t;
		else if (op[i] != 2)
			c[i] = std::lower_bound(t + 1, t + n$ + 1, c[i]) - t;
	}
	for (i = 1; i <= n; i++) add(i, src[i] = std::lower_bound(t + 1, t + n$ + 1, src[i]) - t, 1), cnt[src[i]]++;
	for (i = 1; i <= m; i++) {
		switch (op[i]) {
			case 1:
				printf("%d\n", $([](int x) { return queryrk(x); }, a[i], b[i], c[i]));
				break;
			case 2:
				printf("%d\n", t[$([](int x) { return querykth(x); }, a[i], b[i], c[i])]);
				break;
			case 3:
				cnt[src[a[i]]]--;
				cnt[b[i]]++;
				add(a[i], src[a[i]], -1);
				add(a[i], src[a[i]] = b[i], 1);
				break;
			case 4:
				tmprk = $([](int x) { return queryrk(x); }, a[i], b[i], c[i]) - 1;
				if (tmprk < 1) {
					puts("-2147483647");
					break;
				}
				printf("%d\n", t[$([](int x) { return querykth(x); }, a[i], b[i], tmprk)]);
				break;
			case 5:
				tmprk = $([](int x) { return queryrk(x); }, a[i], b[i], c[i]) +
						$([](int x) { return querysz(x); }, a[i], b[i], c[i]);
				if (tmprk > b[i] - a[i] + 1) {
					puts("2147483647");
					break;
				}
				printf("%d\n", t[$([](int x) { return querykth(x); }, a[i], b[i], tmprk)]);
				break;
		}
	}
}