#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
#define L (x << 1)
#define R ((x << 1) | 1)
#define mid (l + r) / 2

#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize( \
	"inline,-fgcse,-fgcse-lm,-fipa-sra,-ftree-pre,-ftree-vrp,-fpeephole2,-ffast-math,-fsched-spec,unroll-loops,-falign-jumps,-falign-loops,-falign-labels,-fdevirtualize,-fcaller-saves,-fcrossjumping,-fthread-jumps,-funroll-loops,-freorder-blocks,-fschedule-insns,inline-functions,-ftree-tail-merge,-fschedule-insns2,-fstrict-aliasing,-fstrict-overflow,-falign-functions,-fcse-follow-jumps,-fsched-interblock,-fpartial-inlining,no-stack-protector,-freorder-functions,-findirect-inlining,-fhoist-adjacent-loads,-frerun-cse-after-loop,inline-small-functions,-finline-small-functions,-ftree-switch-conversion,-foptimize-sibling-calls,-fexpensive-optimizations,inline-functions-called-once,-fdelete-null-pointer-checks")

const int N = 1e6 + 61, M = 2e6 + 62, K = 1e5;

struct io_t {  // 欺负人
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

struct _ {
	int *p, v;
} st[N * 3];
int top;
void set(int& x, int y) { st[++top] = (_){&x, x}, x = y; }

int p[N], s[N];
int f(int x) { return x[p] ? f(x[p]) : x; }
void mg(int x, int y) {
	if ((x = f(x)) != (y = f(y))) {
		if (x[s] > y[s]) std::swap(x, y);
		set(x[p], y), set(y[s], x[s] + y[s]);
	}
}

std::vector<int> opr[4 * K];
int n, ql, qr, u[M], v[M];
void ins(int x, int l, int r, int y) {
	if (ql <= l && r <= qr) return x[opr].push_back(y);
	if (ql <= mid) ins(L, l, mid, y);
	if (mid < qr) ins(R, mid + 1, r, y);
}
void dfs(int x, int l, int r) {
	int sz = top;
	for (int i : x[opr]) mg(u[i], v[i]);
	if (l == r) {
		if (f(1)[s] == n) exit(!printf("%d", l));
	} else
		dfs(L, l, mid), dfs(R, mid + 1, r);
	for (; top > sz; top--) *st[top].p = st[top].v;
}

int m, x;
int main() {
	io >> n >> m;
	for (int i = 1; i <= n; i++) i[s] = 1;
	for (int i = 1; i <= m; i++) {
		io >> u[i] >> v[i] >> x;
		if (x) ql = 0, qr = x - 1, ins(1, 0, K, i);
		if (x < K) ql = x + 1, qr = K, ins(1, 0, K, i);
	}
	dfs(1, 0, K);
	puts("100001");
}