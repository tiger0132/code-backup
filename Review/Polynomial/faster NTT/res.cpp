#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#define int unsigned

typedef unsigned long long L;
const int N = 2.7e5 + 572, P = 998244353, G = 3;

struct io_t {
	struct stat st;
	char* ptr;
	int fd;
	inline io_t() {
		fd = fileno(stdin), fstat(fd, &st), ptr = (char*)mmap(0, st.st_size, 1, 2, fd, 0);
	}
	io_t& operator>>(int& x) {
#ifdef LOCAL
		scanf("%d", &x);
#else
		x = 0;
		while (*ptr < '0') ++ptr;
		while (*ptr >= '0') x = x * 10 + (*ptr++ ^ 48);
#endif
		return *this;
	}
} io;

int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = (L)x * x % P)
		if (y & 1) r = (L)r * x % P;
	return r;
}

unsigned char _dft[] = {
	0x85, 0xf6, 0x0f, 0x84, 0x58, 0x01, 0x00, 0x00, 0x41, 0x57, 0x41, 0x56, 0x31, 0xc9,
	0x41, 0x55, 0x41, 0x54, 0x55, 0x53, 0x48, 0x83, 0xec, 0x28, 0x0f, 0x1f, 0x84, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x44, 0x8d, 0x41, 0x01, 0x89, 0xc8, 0x83, 0xc1, 0x02, 0x4c,
	0x8d, 0x14, 0xc7, 0x4e, 0x8d, 0x04, 0xc7, 0x49, 0x8b, 0x02, 0x4d, 0x8b, 0x08, 0x41,
	0x8d, 0x1c, 0x01, 0x05, 0x01, 0x00, 0x80, 0x3b, 0x44, 0x29, 0xc8, 0x39, 0xce, 0x49,
	0x89, 0x1a, 0x49, 0x89, 0x00, 0x77, 0xd3, 0x83, 0xfe, 0x02, 0x0f, 0x86, 0xfb, 0x00,
	0x00, 0x00, 0x48, 0x89, 0x54, 0x24, 0x18, 0x89, 0x74, 0x24, 0x0c, 0x49, 0x89, 0xfe,
	0x41, 0xbc, 0x02, 0x00, 0x00, 0x00, 0x48, 0xbb, 0x3f, 0xcc, 0xe0, 0x5d, 0x87, 0x40,
	0xae, 0x89, 0x66, 0x0f, 0x1f, 0x44, 0x00, 0x00, 0x47, 0x8d, 0x2c, 0x24, 0x31, 0xd2,
	0xb8, 0x00, 0x00, 0x80, 0x3b, 0xbf, 0x03, 0x00, 0x00, 0x00, 0x41, 0xf7, 0xf5, 0x89,
	0xc6, 0x48, 0x8b, 0x44, 0x24, 0x18, 0xff, 0xd0, 0x44, 0x89, 0xe6, 0x45, 0x85, 0xe4,
	0x48, 0x89, 0x74, 0x24, 0x10, 0x0f, 0x84, 0x9e, 0x00, 0x00, 0x00, 0x41, 0x8d, 0x54,
	0x24, 0xff, 0x89, 0xc5, 0x45, 0x31, 0xe4, 0x4d, 0x8d, 0x7c, 0xd6, 0x08, 0x0f, 0x1f,
	0x40, 0x00, 0x45, 0x89, 0xe1, 0xb9, 0x01, 0x00, 0x00, 0x00, 0x4e, 0x8d, 0x14, 0xcd,
	0x00, 0x00, 0x00, 0x00, 0x4c, 0x03, 0x4c, 0x24, 0x10, 0x4b, 0x8d, 0x34, 0x16, 0x4f,
	0x8d, 0x1c, 0x17, 0x49, 0xc1, 0xe1, 0x03, 0x0f, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x00,
	0x48, 0x89, 0xf7, 0x4c, 0x29, 0xd7, 0x4e, 0x8b, 0x04, 0x0f, 0x4c, 0x0f, 0xaf, 0xc1,
	0x48, 0x0f, 0xaf, 0xcd, 0x4c, 0x89, 0xc0, 0x48, 0xf7, 0xe3, 0x48, 0x8b, 0x06, 0x48,
	0x05, 0x01, 0x00, 0x80, 0x3b, 0x48, 0xc1, 0xea, 0x1d, 0x48, 0x69, 0xd2, 0x01, 0x00,
	0x80, 0x3b, 0x49, 0x29, 0xd0, 0x4c, 0x29, 0xc0, 0x4a, 0x89, 0x04, 0x0f, 0x48, 0x89,
	0xc8, 0x4c, 0x01, 0x06, 0x48, 0xf7, 0xe3, 0x48, 0x83, 0xc6, 0x08, 0x48, 0xc1, 0xea,
	0x1d, 0x48, 0x69, 0xd2, 0x01, 0x00, 0x80, 0x3b, 0x29, 0xd1, 0x49, 0x39, 0xf3, 0x75,
	0xab, 0x45, 0x01, 0xec, 0x44, 0x39, 0x64, 0x24, 0x0c, 0x0f, 0x87, 0x75, 0xff, 0xff,
	0xff, 0x44, 0x3b, 0x6c, 0x24, 0x0c, 0x45, 0x89, 0xec, 0x0f, 0x82, 0x27, 0xff, 0xff,
	0xff, 0x48, 0x83, 0xc4, 0x28, 0x5b, 0x5d, 0x41, 0x5c, 0x41, 0x5d, 0x41, 0x5e, 0x41,
	0x5f, 0xc3, 0xf3, 0xc3, 0x66, 0x2e, 0x0f, 0x1f, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x0f, 0x1f, 0x40, 0x00};

template <typename F>
F* build(unsigned char* buffer, size_t buf_size) {
	void* buf = mmap(nullptr, buf_size, PROT_READ | PROT_WRITE,
					 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	memcpy(buf, buffer, buf_size);
	mprotect(buf, buf_size, PROT_READ | PROT_EXEC);
	return reinterpret_cast<F*>(buf);
}

void __dft(L* tmp, int n, int (*_fpw)(int, int)) {
	build<void(L*, int, int (*)(int, int))>(_dft, sizeof _dft)(tmp, n, _fpw);
}

struct poly {
	std::vector<int> v;

	inline poly() {}
	inline poly(int n) : v(n) {}
	inline poly(const poly& rhs) : v(rhs.v) {}
	inline poly(const std::vector<int>& rhs) : v(rhs) {}

	inline size_t size() { return v.size(); }
	inline bool empty() { return v.empty(); }
	inline void resize(int n) { v.resize(n); }
	inline void shl() { v.insert(v.begin(), 0); }
	void shrink() {
		while (!v.empty() && !v.back()) v.pop_back();
	}

	inline static int len(int n) { return 1 << (32 - __builtin_clz(n - 1)); }

	inline int& operator[](int i) { return v[i]; }
	inline void operator*=(const poly& rhs) { mul(rhs); }

	void dft(int n) {
		static L tmp[N];
		resize(n);
		if (n <= 1) return;
		for (int i = 0, ri = 0; i < n; i++) {
			tmp[i] = v[ri];
			for (int k = n >> 1; (ri ^= k) < k;) k >>= 1;
		}
		__dft(tmp, n, pw);
		for (int i = 0; i < n; i++) v[i] = tmp[i] % P;
	}
	void idft(int n) {
		dft(n);
		if (n <= 1) return;
		std::reverse(v.begin() + 1, v.end());
		int tmp = P - (P - 1) / n;
		for (int& i : v) i = (L)i * tmp % P;
	}
	void mul(poly rhs) {
		int n = len(size() + rhs.size() - 1);
		dft(n), rhs.dft(n);
		for (int i = 0; i < n; i++) v[i] = (L)v[i] * rhs[i] % P;
		idft(n);
	}
} a, b;

int n, m;
signed main() {
	io >> n >> m;
	a.resize(n + 1), b.resize(m + 1);
	for (int i = 0; i <= n; i++) io >> a[i];
	for (int i = 0; i <= m; i++) io >> b[i];
	a *= b;
	for (int i = 0; i <= n + m; i++) printf("%u ", a[i]);
}