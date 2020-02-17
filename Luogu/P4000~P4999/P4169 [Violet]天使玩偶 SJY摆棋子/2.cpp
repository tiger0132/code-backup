#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <algorithm>
#include <cstdio>
#include <cstring>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize( \
	"inline,-fgcse,-fgcse-lm,-fipa-sra,-ftree-pre,-ftree-vrp,-fpeephole2,-ffast-math,-fsched-spec,unroll-loops,-falign-jumps,-falign-loops,-falign-labels,-fdevirtualize,-fcaller-saves,-fcrossjumping,-fthread-jumps,-funroll-loops,-freorder-blocks,-fschedule-insns,inline-functions,-ftree-tail-merge,-fschedule-insns2,-fstrict-aliasing,-fstrict-overflow,-falign-functions,-fcse-follow-jumps,-fsched-interblock,-fpartial-inlining,no-stack-protector,-freorder-functions,-findirect-inlining,-fhoist-adjacent-loads,-frerun-cse-after-loop,inline-small-functions,-finline-small-functions,-ftree-switch-conversion,-foptimize-sibling-calls,-fexpensive-optimizations,inline-functions-called-once,-fdelete-null-pointer-checks")

struct io_t {
	struct stat st;
	char* ptr;
	int fd;
	io_t() {
		fd = fileno(stdin), fstat(fd, &st), ptr = (char*)mmap(0, st.st_size, 1, 2, fd, 0);
	}
	inline io_t& operator>>(int& x) {
#ifdef LOCAL
		scanf("%d", &x);
#else
		x = 0;
		while (*ptr < '0') ++ptr;
		while (*ptr >= '0') x = x * 10 + *ptr++ - 48;
#endif
		return *this;
	}
} io;

const int N = 6e5 + 56, M = 1e6 + 61;

struct rec {
	int id, x, y, op, ans;
} a[N];

void upd(int, int), clr(int);
int qry(int);

int tr[M], lim;
void upd(int i, int x) {
	for (; i < lim; i += i & -i) tr[i] = std::max(tr[i], x);
}
void clr(int i) {
	for (; i < lim; i += i & -i) tr[i] = 0xc0c0c0c0;
}
int qry(int i) {
	int r = 0xc0c0c0c0;
	for (; i > 0; i -= i & -i) r = std::max(r, tr[i]);
	return r;
}

void cdq(rec* p, int n) {
	if (n == 1) return;
	int m = n / 2, px = 0;
	cdq(p, m), cdq(p + m, n - m);
	for (int i = m; i < n; i++) {
		for (; p[px].x <= p[i].x && px < m; px++)
			if (p[px].op == 1) upd(p[px].y, p[px].x + p[px].y);
		if (p[i].op == 2) p[i].ans = std::min(p[i].ans, p[i].x + p[i].y - qry(p[i].y));
	}
	while (px--)
		if (p[px].op == 1) clr(p[px].y);
	std::inplace_merge(p, p + m, p + n, [](const rec& lhs, const rec& rhs) {
		return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
	});
}

int n, m, op = 1, x, y, mx, my;
int main() {
	io >> n >> m;
	memset(tr, 0xc0, sizeof tr);
	m += n;
	for (int i = 0; i < m; i++) {
		if (i >= n) io >> op;
		io >> x >> y;
		x++, y++;
		mx = std::max(mx, x + 1);
		my = std::max(my, y + 1);
		a[i] = (rec){i, x, y, op, 0};
		if (op == 2) a[i].ans = 1e9;
	}
	lim = std::max(mx, my) + 10;
	for (int _ = 0; _ < 4; _++) {
		cdq(a, m);
		std::sort(a, a + m,
				  [](const rec& lhs, const rec& rhs) { return lhs.id < rhs.id; });
		for (int i = 0; i < m; i++) a[i].y = my - a[i].y, std::swap(a[i].x, a[i].y);
		std::swap(mx, my);
	}
	for (int i = 0; i < m; i++)
		if (a[i].op == 2) printf("%d\n", a[i].ans);
}