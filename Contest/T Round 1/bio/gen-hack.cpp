#include <algorithm>
#include <cstdio>
#include <cstring>
#define int unsigned

const int N = 7e6 + 67;

signed main(int argc, char **argv) {
	printf("%d %d\n", 7e6, 7e6);
	for (int i = 1; i <= 7e6; i++) printf("0%c", " \n"[i == 7e6]);
	for (int i = 1; i <= 7e6; i++) printf("1%c", " \n"[i == 7e6]);
}