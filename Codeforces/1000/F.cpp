#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 5e5 + 55;

struct io_t {
#define $ (s == t && (t = (s = in) + fread(in, 1, SIZ, stdin), s == t) ? EOF : *s++)
	static const int SIZ = 1 << 25;
	char in[SIZ], out[SIZ], *s = in, *t = in, *o = out;
	~io_t() { fwrite(out, o - out, 1, stdout); }
	inline int read() {
		int x = 0;
		char c = $;
		while (c < '0' || c > '9') c = $;
		while (c >= '0' && c <= '9') x = x * 10 + c - 48, c = $;
		return x;
	}
	void prt(int x) {
		if (x > 9) prt(x / 10);
		*o++ = 48 + x % 10;
	}
	operator int() { return read(); }
	io_t& operator<(int x) { return prt(x), *this; }
	io_t& operator<(char x) { return *o++ = x, *this; }
} io;

int sz;
struct qry {
	int l, r, *ans;
	inline bool operator<(const qry& rhs) const {
		return l / sz == rhs.l / sz ? l / sz % 2 ? r < rhs.r : r > rhs.r : l < rhs.l;
	}
} q[N];

int n, m, a[N], cnt[N], ans[N], pre[N], nxt[N], head;
inline void add(int x, int o) {
	if (x[cnt] == 1) {
		x[pre][nxt] = x[nxt];
		if (x[nxt])
			x[nxt][pre] = x[pre];
		else
			head = x[pre];
		x[pre] = x[nxt] = 0;
	}
	if ((x[cnt] += o) == 1) head[nxt] = x, x[pre] = head, head = x;
}
int main() {
	n = io, sz = sqrt(n);
	for (int i = 1; i <= n; i++) a[i] = io;
	m = io;
	for (int i = 1; i <= m; i++) q[i].l = io, q[i].r = io, q[i].ans = ans + i;
	std::sort(q + 1, q + m + 1);
	int l = 1, r = 0;
	for (int i = 1; i <= m; i++) {
		while (l > q[i].l) add(a[--l], 1);
		while (r < q[i].r) add(a[++r], 1);
		while (l < q[i].l) add(a[l++], -1);
		while (r > q[i].r) add(a[r--], -1);
		*q[i].ans = head;
	}
	for (int i = 1; i <= m; i++) io < ans[i] < '\n';
}