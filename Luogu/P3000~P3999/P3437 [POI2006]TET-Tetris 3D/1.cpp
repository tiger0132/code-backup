#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e3 + 32;
#define L ch][0
#define R ch][1
#define mid (l + r) / 2

template <typename T>
struct SGT {
	int ch[N][2], nc;
	T t[N];
	template <typename... Args>
	void upd(int& x, int l, int r, int ql, int qr, Args... args) {
		if (!x) x = ++nc;
		x[t].put_ancestor(args...);
		if (ql <= l && r <= qr) return x[t].put_self(args...);
		if (ql <= mid) upd(x[L], l, mid, ql, qr, args...);
		if (mid < qr) upd(x[R], mid + 1, r, ql, qr, args...);
	}
	template <typename... Args>
	typename T::value_type qry(int x, int l, int r, int ql, int qr, Args... args) {
		if (!x) return T::I;
		if (ql <= l && r <= qr) return x[t].qry_ancestor(args...);
		int ret = x[t].qry_self(args...);
		if (ql <= mid) T::merge(ret, qry(x[L], l, mid, ql, qr, args...));
		if (mid < qr) T::merge(ret, qry(x[R], mid + 1, r, ql, qr, args...));
		return ret;
	}
};

int n, m;
struct inner {
	static const int I = 0;
	typedef int value_type;
	static void merge(int& x, int y) { x = std::max(x, y); }

	int tag, mx;
	void put_ancestor(int x) { mx = std::max(mx, x); };
	void put_self(int x) { tag = std::max(tag, x); };
	int qry_ancestor() { return mx; }
	int qry_self() { return tag; }
};
struct exterior {
	static const int I = 0;
	typedef int value_type;
	static void merge(int& x, int y) { x = std::max(x, y); }

	SGT<inner> tag, mx;
	int rt_tag, rt_mx;
	void put_ancestor(int l, int r, int x) { mx.upd(rt_mx, 1, m, l, r, x); }
	void put_self(int l, int r, int x) { tag.upd(rt_tag, 1, m, l, r, x); }
	int qry_ancestor(int l, int r) { return mx.qry(rt_mx, 1, m, l, r); }
	int qry_self(int l, int r) { return tag.qry(rt_tag, 1, m, l, r); }
};

int q, a, b, c, d, e, rt;
SGT<exterior> sgt;
int main() {
	for (scanf("%d%d%d", &n, &m, &q); q--;) {
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &e), d++, e++;
		int v = sgt.qry(rt, 1, n, d, d + a - 1, e, e + b - 1);
		sgt.upd(rt, 1, n, d, d + a - 1, e, e + b - 1,
				sgt.qry(rt, 1, n, d, d + a - 1, e, e + b - 1) + c);
	}
	printf("%d\n", sgt.qry(rt, 1, n, 1, n, 1, m));
}