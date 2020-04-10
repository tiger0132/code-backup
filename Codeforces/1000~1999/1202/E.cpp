#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

#pragma region IO
namespace IO {
#ifdef __unix__
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

struct in_t {
#ifdef LOCAL_QWQ
	inline in_t() {}
	inline in_t(const char *path) { freopen(path, "r", stdin); }
	inline char gc() { return getchar(); }
#elif __unix__
	struct stat st;
	char *ptr;
	int fd;
	inline in_t() {
		fd = fileno(stdin), fstat(fd, &st),
		ptr = (char *)mmap(0, st.st_size, 1, 2, fd, 0);
	}
	inline in_t(const char *path) {
		fd = open(path, O_RDONLY), fstat(fd, &st),
		ptr = (char *)mmap(0, st.st_size, 1, 2, fd, 0);
	}
	inline char gc() { return *ptr++; }
#else
	static const int SZ = 1 << 20;
	char buf[SZ], *s, *t;
	inline in_t() {}
	inline in_t(const char *path) { freopen(path, "r", stdin); }
	inline char gc() {
		if (s == t) t = (s = buf) + fread(buf, 1, SZ, stdin);
		return s == t ? ' ' : *s++;
	}
#endif
	template <typename T>
	void readU(T &x) {
		x = 0;
		char c = gc();
		while (c < '0') c = gc();
		for (; c >= '0'; c = gc()) x = x * 10 + (c & 15);
	}
	template <typename T>
	void readI(T &x) {
		x = 0;
		bool f = 0;
		char c = gc();
		for (; c < '0'; c = gc())
			if (c == '-') f = 1;
		for (; c >= '0'; c = gc()) x = x * 10 + (c & 15);
		if (f) x = -x;
	}
	template <typename T>
	void readF(T &x) {
		T tmp = 1;
		bool f = 0;
		char c = gc();
		x = 0;
		for (; c < '0'; c = gc())
			if (c == '-') f = 1;
		for (; c >= '0'; c = gc()) x = x * 10 + (c & 15);
		if (c == '.')
			for (c = gc(); c >= '0'; c = gc()) tmp /= 10, x += tmp * (c & 15);
		if (f) x = -x;
	}

#define READ_DEF(type, func) \
	in_t &operator>>(type &x) { return func(x), *this; };
#ifdef __x86_64__
#define READ_DEF_X64(type, func) READ_DEF(type, func)
#else
#define READ_DEF_X64(type, func)
#endif

	READ_DEF(signed short, readI);
	READ_DEF(signed int, readI);
	READ_DEF(signed long, readI);
	READ_DEF(signed long long, readI);
	READ_DEF_X64(signed __int128, readI);

	READ_DEF(unsigned short, readU);
	READ_DEF(unsigned int, readU);
	READ_DEF(unsigned long, readU);
	READ_DEF(unsigned long long, readU);
	READ_DEF_X64(unsigned __int128, readU);

	READ_DEF(float, readF);
	READ_DEF(double, readF);
	READ_DEF(__float128, readF);

	in_t &operator>>(char &c) {
		for (c = gc(); c <= ' ';) c = gc();
		return *this;
	}
	in_t &operator>>(char *s) {
		char c;
		for (c = gc(); c <= ' ';) c = gc();
		for (; c > ' '; c = gc()) *s++ = c;
		return *s = 0, *this;
	}
#ifdef _STRINGFWD_H
	in_t &operator>>(std::string &s) {
		char c;
		s.clear();
		for (c = gc(); c <= ' ';) c = gc();
		for (; c > ' '; c = gc()) s += c;
		return *this;
	}
#endif
};

struct out_t {
#ifdef LOCAL_QWQ
	inline out_t() { setvbuf(stdout, 0, _IONBF, 0); }
	inline out_t(const char *path) {
		freopen(path, "w", stdout);
		setvbuf(stdout, 0, _IONBF, 0);
	}
	inline void flush() {}
	inline void pc(char c) { putchar(c); }
#else
	static const int SZ = 1 << 20;
	char buf[SZ], *s = buf, *t = buf + SZ;
	inline out_t() { setvbuf(stdout, 0, _IONBF, 0); }
	inline out_t(const char *path) {
		freopen(path, "w", stdout);
		setvbuf(stdout, 0, _IONBF, 0);
	}
	inline void flush() { fwrite(buf, 1, s - buf, stdout); }
	inline void pc(char c) {
		if (s == t) flush(), s = buf;
		*s++ = c;
	}
	inline ~out_t() { flush(); }
#endif
	template <typename T>
	void outU(const T &x) {
		if (x > 9) outU(x / 10);
		pc(x % 10 + '0');
	}
	template <typename T>
	void outI(const T &x) {
		if (x < 0) pc('-');
		outU(x);
	}

#define OUT_DEF(type, func) \
	out_t &operator<<(type x) { return func(x), *this; };
#ifdef __x86_64__
#define OUT_DEF_X64(type, func) OUT_DEF(type, func)
#else
#define OUT_DEF_X64(type, func)
#endif

	OUT_DEF(signed short, outI);
	OUT_DEF(signed int, outI);
	OUT_DEF(signed long, outI);
	OUT_DEF(signed long long, outI);
	OUT_DEF_X64(signed __int128, outI);

	OUT_DEF(unsigned short, outU);
	OUT_DEF(unsigned int, outU);
	OUT_DEF(unsigned long, outU);
	OUT_DEF(unsigned long long, outU);
	OUT_DEF_X64(unsigned __int128, outU);

	out_t &operator<<(char c) { return pc(c), *this; }
	out_t &operator<<(char *s) {
		while (*s) pc(*s++);
		return *this;
	}
};
}  // namespace IO
using namespace IO;
#pragma endregion

in_t in;
out_t out;

const int N = 4e5 + 54;

struct SAM {
	int v[N], len[N], link[N], tr[N][26], pre[N], nc, last;
	SAM() { nc = last = 1; }
	void ins(int c) {
		int cur = ++nc, p = last, q, cl;
		cur[len] = p[len] + 1;
		for (; p && !(q = p[tr][c]); p = p[link]) p[tr][c] = cur;
		if (!p)
			cur[link] = 1;
		else if (p[len] + 1 == q[len])
			cur[link] = q;
		else {
			cl = ++nc, cl[len] = p[len] + 1, cl[link] = q[link];
			memcpy(cl[tr], q[tr], sizeof *tr);
			for (; p && p[tr][c] == q; p = p[link]) p[tr][c] = cl;
			q[link] = cur[link] = cl;
		}
		last = cur;
	}
	void operator+=(char *s) {
		for (int i = 0; *s; i++) ins(*s++ - 97), i[pre] = last;
	}
	void operator<<=(char *s) {
		int x = 1;
		for (; *s; x = x[tr][*s++ - 97])
			if (!x[tr][*s - 97]) return;
		x[v]++;
	}

	std::vector<int> g[N];
	void dfs(int x, int s) {
		s = x[v] += s;
		for (int nx : x[g]) dfs(nx, s);
	}
	void solve() {
		for (int i = 2; i <= nc; i++) i[link][g].push_back(i);
		dfs(1, 0);
	}
} sm, rsm;

long long ans;
char s[N];
int t, n;
int main() {
	in >> s, n = strlen(s);
	sm += s, std::reverse(s, s + n), rsm += s;
	for (in >> t; t--;) {
		in >> s;
		sm <<= s, std::reverse(s, s + strlen(s)), rsm <<= s;
	}
	sm.solve(), rsm.solve();
	for (int i = 0; i < n - 1; i++)
		ans += 1ll * sm.pre[i][sm.v] * rsm.pre[n - i - 2][rsm.v];
	out << ans;
}