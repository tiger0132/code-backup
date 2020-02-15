#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <type_traits>

// QwQ

#include <algorithm>
#include <cstdio>
#include <cstring>

typedef unsigned u;
struct io_t {
	struct stat st;
	char *ptr;
	int fd;
	io_t() {
		fd = fileno(stdin), fstat(fd, &st),
		ptr = (char *)mmap(0, st.st_size, 1, 2, fd, 0);
	}
	io_t(const char *path) {
		fd = open(path, O_RDONLY), fstat(fd, &st),
		ptr = (char *)mmap(0, st.st_size, 1, 2, fd, 0);
	}
	template <typename T>
	inline typename std::enable_if<std::is_unsigned<T>::value, io_t &>::type operator>>(
		T &x) {
		x = 0;
		while (*ptr < '0') ++ptr;
		while (*ptr >= '0') x = x * 10 + *ptr++ - 48;
		return *this;
	}
	template <typename T>
	inline typename std::enable_if<std::is_signed<T>::value, io_t &>::type operator>>(
		T &x) {
		x = 0;
		int f = 0;
		while (*ptr < '0' && *ptr != '-') ++ptr;
		if (*ptr == '-') ++ptr, f = 1;
		while (*ptr >= '0') x = x * 10 + *ptr++ - 48;
		if (f) x = -x;
		return *this;
	}
	template <typename T>
	inline typename std::enable_if<std::__is_char<T>::__value, io_t &>::type operator>>(
		T *x) {
		// while (*prt ==)
	}
} io;

u n, x, ans;
char s[2333];
int main() {
	io >> s;
	puts(s);
	// for (io >> n; n--; ans ^= x) io >> x;
	// printf("%u", ans);
}