#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <queue>
#define M1(x, y) (((x) >> (y)) & 1)
#define GET(x, y, z, w, v, ...) v
#define $(...) GET(__VA_ARGS__, M2, 0, M1)(__VA_ARGS__)

#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize( \
	"inline,-fgcse,-fgcse-lm,-fipa-sra,-ftree-pre,-ftree-vrp,-fpeephole2,-ffast-math,-fsched-spec,unroll-loops,-falign-jumps,-falign-loops,-falign-labels,-fdevirtualize,-fcaller-saves,-fcrossjumping,-fthread-jumps,-funroll-loops,-freorder-blocks,-fschedule-insns,inline-functions,-ftree-tail-merge,-fschedule-insns2,-fstrict-aliasing,-fstrict-overflow,-falign-functions,-fcse-follow-jumps,-fsched-interblock,-fpartial-inlining,no-stack-protector,-freorder-functions,-findirect-inlining,-fhoist-adjacent-loads,-frerun-cse-after-loop,inline-small-functions,-finline-small-functions,-ftree-switch-conversion,-foptimize-sibling-calls,-fexpensive-optimizations,inline-functions-called-once,-fdelete-null-pointer-checks")

typedef unsigned u;
const int N = 5e5 + 55, LG = 31;
#define lc ch[0]
#define rc ch[1]

extern struct node _[];
int M2(int, int, int, int);
int cnt;
struct node {
	int ch[2], id, v;
	int ins(int x, int idx, int id = LG) {
		if (id < 0) return $(0, 0, v + 1, idx);
		if (!$(x, id))
			return $(_[lc].ins(x, idx, id - 1), rc, v + 1, -1);
		else
			return $(lc, _[rc].ins(x, idx, id - 1), v + 1, -1);
	}
} _[N * 45];
inline int M2(int x, int y, int z, int id) { return _[++cnt] = (node){{x, y}, id, z}, cnt; }
int rt[N];
inline int query(int L, int R, u x) {
	L = rt[L], R = rt[R];
	int t;
	for (int i = LG; i >= 0; i--) {
		t = $(x, i);
		if (_[_[R].ch[!t]].v - _[_[L].ch[!t]].v)
			L = _[L].ch[!t], R = _[R].ch[!t];
		else
			L = _[L].ch[t], R = _[R].ch[t];
	}
	return _[R].id;
}

static int n, k;
static u a[N];
long long ans;

struct q {
	int L, l, r, x;
	inline bool operator<(const q &rhs) const { return (a[x] ^ a[L - 1]) < (a[rhs.x] ^ a[rhs.L - 1]); }
};
static __gnu_pbds::priority_queue<q> pq;
int main() {
	scanf("%d%d", &n, &k);
	rt[0] = $(0, 0, 0, -1);
	for (int i = 1; i <= n; i++) scanf("%u", a + i), rt[i] = _[rt[i - 1]].ins(a[i] ^= a[i - 1], i);
	for (int i = 1; i <= n; i++) pq.push((q){i, i, n, query(i - 1, n, a[i - 1])});
	while (k--) {
		q x = pq.top();
		ans += a[x.x] ^ a[x.L - 1], pq.pop();
		if (x.l != x.x) pq.push((q){x.L, x.l, x.x - 1, query(x.l - 1, x.x - 1, a[x.L - 1])});
		if (x.x != x.r) pq.push((q){x.L, x.x + 1, x.r, query(x.x, x.r, a[x.L - 1])});
	}
	printf("%lld", ans);
}