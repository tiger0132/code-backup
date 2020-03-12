#include <algorithm>
#include <cstring>
#include <cstdio>

int n, m;
int main() {
	for (scanf("%*d"); ~scanf("%d%d", &n, &m);) puts(n % m ? "NO" : "YES");
}