#include <cstdio>

const int N = 1e6 + 61;

int newNode(int, int, int), n;
extern struct node _[];
struct node {
	int lc, rc, v;
	void build(int l = 1, int r = n) {
		if (l == r) return (void)scanf("%d", &v);
		int mid = (l + r) >> 1;
		_[lc = newNode(0, 0, 0)].build(l, mid);
		_[rc = newNode(0, 0, 0)].build(mid + 1, r);
	}
	int update(int x, int y, int l = 1, int r = n) {
		if (l == r) return newNode(0, 0, y);
		int mid = (l + r) >> 1;
		if (x <= mid) return newNode(_[lc].update(x, y, l, mid), rc, 0);
		return newNode(lc, _[rc].update(x, y, mid + 1, r), 0);
	}
	int query(int x, int l = 1, int r = n) {
		if (l == r) return v;
		int mid = (l + r) >> 1;
		if (x <= mid) return _[lc].query(x, l, mid);
		return _[rc].query(x, mid + 1, r);
	}
} _[N * 90];
int newNode(int lc, int rc, int v) {
	static int ptr = 1;
	_[ptr].lc = lc, _[ptr].rc = rc, _[ptr].v = v;
	return ptr++;
}
int rt[N];

int m, x, op, y, z;
int main() {
	scanf("%d%d", &n, &m);
	_[rt[0] = newNode(0, 0, 0)].build();
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &x, &op, &y);
		if (op == 1) {
			scanf("%d", &z);
			rt[i] = _[rt[x]].update(y, z);
		} else {
			printf("%d\n", _[rt[i] = rt[x]].query(y));
		}
	}
}