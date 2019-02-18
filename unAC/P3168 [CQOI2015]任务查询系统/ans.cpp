#include <algorithm>
#include <cstdio>
#include <vector>

const int MAXN = 100000;
const int MAXX = 10000000;

struct Tag {
	int x;
	bool del;
	Tag(int x, bool del) : x(x), del(del) {}
};

extern struct SegT *null;

struct SegT {
	SegT *lc, *rc;
	int cnt;
	long long sum;
	SegT() : lc(this), rc(this), cnt(0), sum(0) {}
	SegT(SegT *lc, SegT *rc) : lc(lc), rc(rc), cnt(lc->cnt + rc->cnt), sum(lc->sum + rc->sum) {}
	SegT(SegT *lc, SegT *rc, int cnt, long long sum) : lc(lc), rc(rc), cnt(cnt), sum(sum) {}
	SegT *insert(int l, int r, int x, int delta) {
		int mid = l + (r - l) / 2;
		if (l == r) return new SegT(null, null, cnt + delta, sum + (long long)delta * l);
		if (x <= mid)
			return new SegT(lc->insert(l, mid, x, delta), rc);
		else
			return new SegT(lc, rc->insert(mid + 1, r, x, delta));
	}
	long long query(int l, int r, int k) {
		int mid = l + (r - l) / 2;
		if (k > cnt)
			return sum;
		else if (l == r)
			return (long long)k * l;
		else if (k == lc->cnt)
			return lc->sum;
		else if (k > lc->cnt)
			return lc->sum + rc->query(mid + 1, r, k - lc->cnt);
		else
			return lc->query(l, mid, k);
	}
} * rt[MAXN + 1], *null;

inline void init() { null = new SegT(); }

int m, n;
std::vector<Tag> tags[MAXN + 1];

inline void build() {
	rt[0] = null;
	for (int i = 1; i <= n; i++) {
		SegT *v = rt[i - 1];
		for (std::vector<Tag>::iterator it = tags[i].begin(); it != tags[i].end(); it++) {
			v = v->insert(1, MAXX, it->x, it->del ? -1 : 1);
		}
		rt[i] = v;
	}
}

int main() {
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= m; i++) {
		int l, r, x;
		scanf("%d%d%d", &l, &r, &x);
		tags[l].push_back(Tag(x, false));
		if (r + 1 <= n) tags[r + 1].push_back(Tag(x, true));
	}
	init();
	build();
	long long lastAns = 1;
	for (int i = 1; i <= n; i++) {
		int x, a, b, c;
		scanf("%d%d%d%d", &x, &a, &b, &c);
		int k = 1 + (a * lastAns + b) % c;
		lastAns = rt[x]->query(1, MAXX, k);
		printf("%lld\n", lastAns);
	}
	return 0;
}