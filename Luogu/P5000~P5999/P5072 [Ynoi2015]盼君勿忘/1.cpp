// 卡动了，不自闭
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize( \
	"inline,-fgcse,-fgcse-lm,-fipa-sra,-ftree-pre,-ftree-vrp,-fpeephole2,-ffast-math,-fsched-spec,unroll-loops,-falign-jumps,-falign-loops,-falign-labels,-fdevirtualize,-fcaller-saves,-fcrossjumping,-fthread-jumps,-funroll-loops,-freorder-blocks,-fschedule-insns,inline-functions,-ftree-tail-merge,-fschedule-insns2,-fstrict-aliasing,-fstrict-overflow,-falign-functions,-fcse-follow-jumps,-fsched-interblock,-fpartial-inlining,no-stack-protector,-freorder-functions,-findirect-inlining,-fhoist-adjacent-loads,-frerun-cse-after-loop,inline-small-functions,-finline-small-functions,-ftree-switch-conversion,-foptimize-sibling-calls,-fexpensive-optimizations,inline-functions-called-once,-fdelete-null-pointer-checks")
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <unordered_set>

typedef std::unordered_set<int>::const_iterator $;
const int N = 1e5 + 51;

struct io_t {
#define $$ (s == t && (t = (s = in) + fread(in, 1, SIZ, stdin), s == t) ? EOF : *s++)
	static const int SIZ = 1 << 25;
	char in[SIZ], out[SIZ], *s = in, *t = in, *o = out;
	int st[15], top;
	inline ~io_t() { fwrite(out, o - out, 1, stdout); }
	inline int read() {
		int x = 0;
		char c = $$;
		while (!isdigit(c)) c = $$;
		while (isdigit(c)) x = x * 10 + c - 48, c = $$;
		return x;
	}
	inline void prt(int x) {
		if (x > 9) prt(x / 10);
		*o++ = 48 + x % 10;
	}
	inline operator int() { return read(); }
	inline io_t& operator<(int x) { return prt(x), *this; }
	inline io_t& operator<(char x) { return *o++ = x, *this; }
} io;

const int sz = 317;
struct node {
	int l, r, p, *ans;
	inline bool operator<(const node& rhs) const {
		return l / sz == rhs.l / sz ? l / sz % 2 ? r < rhs.r : r > rhs.r : l < rhs.l;
	}
} q[N];

int n, m, l, r, a[N], b[N], ans[N], cnt[N], u[N], v[N];
std::unordered_set<int> mmp;
int buk[N];
inline int p2(int x, int y) { return 1ll * u[x % sz] * v[x / sz] % y; }
inline void md(int& x, int y) { x >= y && (x -= y); }
inline void add(int x) {
	if (cnt[x] && !(buk[cnt[x]] -= b[x])) mmp.erase(cnt[x]);
	if (!buk[++cnt[x]]) mmp.insert(cnt[x]);
	buk[cnt[x]] += b[x];
}
inline void del(int x) {
	if (!(buk[cnt[x]] -= b[x])) mmp.erase(cnt[x]);
	if (--cnt[x] && (buk[cnt[x]] += b[x]) == b[x]) mmp.insert(cnt[x]);
}
int main() {
	n = io, m = io;
	for (int i = 1; i <= n; i++) {
		a[i] = io, b[i] = a[i];
	}
	std::sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i++) {
		a[i] = std::lower_bound(b + 1, b + n + 1, a[i]) - b;
	}
	for (int i = 1; i <= m; i++) {
		q[i] = (node){io, io, io, ans + i};
	}
	std::sort(q + 1, q + m + 1);
	l = 1;
	r = 0;
	for (int i = 1; i <= m; i++) {
		u[0] = v[0] = 1;
		for (int j = 1; j <= sz; j++) md(u[j] = u[j - 1] << 1, q[i].p);
		for (int j = 1; j <= sz; j++) v[j] = 1ll * v[j - 1] * u[sz] % q[i].p;
		while (l > q[i].l) add(a[--l]);
		while (r < q[i].r) add(a[++r]);
		while (l < q[i].l) del(a[l++]);
		while (r > q[i].r) del(a[r--]);
		int tmp = p2(r - l + 1, q[i].p);
		for ($ it = mmp.begin(); it != mmp.end(); it++) {
			md(*q[i].ans =
				   (*q[i].ans +
					1ll * buk[*it] * (tmp - p2(r - l - *it + 1, q[i].p) + q[i].p)) %
				   q[i].p,
			   q[i].p);
		}
	}
	for (int i = 1; i <= m; i++) {
		io < ans[i] < '\n';
	}
}