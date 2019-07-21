#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

int n, m, op;

int main() {
	freopen("1.in", "w", stdout);
	srand((unsigned long long)new char);
	n = m = 1e5, op = rand() < rand();
	printf("%d %d %d\n", n, m, op);
	for (int i = 1; i <= n; i++) printf("%d%c", 1, " \n"[i == n]);
}