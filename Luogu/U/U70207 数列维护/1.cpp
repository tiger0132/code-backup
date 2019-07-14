// 这份代码不需要特殊性质，但是它是两个 log 的

#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51;

template <int T>
int $() {
	static int cnt = 0;
	return ++cnt;
}
extern struct inner __[];
struct inner {
	int ch[2], tag, mask;
	inner() { mask = 1 << 30; }
	void put(int x) {
		tag ^= x;
		if (x & mask) std::swap(ch[0], ch[1]);
	}
	void pd() { ch[0][__].put(tag), ch[1][__].put(tag), tag = 0; }
	void ins(int x) {
		if (!mask) return;
		pd();
		int &id = ch[!!(x & mask)];
		if (!id) id = $<0>();
		__[id].mask = mask / 2, __[id].ins(x);
	}
	int max() {
		if (!mask) return 0;
		pd();
		return ch[1] ? mask | ch[1][__].max() : ch[0][__].max();
	}
	int min() {
		if (!mask) return 0;
		pd();
		return ch[0] ? ch[0][__].min() : mask | ch[1][__].min();
	}
} __[N * 128];
extern struct node _[];
struct node {
	int lc, rc, min, max;
	inner &in;
	node() : in(__[$<0>()]){};
	void up() {
		min = std::min(_[lc].min, _[rc].min);
		max = std::max(_[lc].max, _[rc].max);
	}
	void build(int l, int r, int *a) {
		for (int i = l; i <= r; i++) in.ins(a[i]);
		int mid = (l + r) / 2;
		if (l == r) return (void)(min = in.min(), max = in.max());
		build(l, mid, a), build(mid + 1, r, a), up();
	}
	void update(int l, int r, int L, int R, int x) {
		int mid = (l + r) / 2;
		if (L <= l && r <= R) return (void)(in.put(x), min = in.min(), max = in.max());
		if (L <= mid) _[lc].update(l, mid, L, R, x);
		if (mid < R) _[rc].update(mid + 1, r, L, R, x);
		up();
	}
	int update(int l, int r, int L, int R, int x) {
		int mid = (l + r) / 2;
		if (L <= l && r <= R) return (void)(in.put(x), min = in.min(), max = in.max());
		if (L <= mid) _[lc].update(l, mid, L, R, x);
		if (mid < R) _[rc].update(mid + 1, r, L, R, x);
	}
} _[N * 4];
int rt;

int n, m, a[N], x, y;
char op[2];
int main() {
	_[0].min = 1e9;
	scanf("%*d%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", i + a);
	_[rt = $<1>()].build(1, n, a);
	for (scanf("%*d", &n); n--;) {
		scanf("%s%d%d", op, &x, &y);
		if (*op == '_') printf("%d\n", _[rt].);
	}
}