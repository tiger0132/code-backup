#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>

std::set<int> s;
int n;
int main() {
	scanf("%d", &n);
	for (int i = 1, j; i * i <= n; i++)
		if (n % i == 0) {
			j = n / i;
			for (int x = 1; x <= n; x += j)  // j | (x - 1)
				if ((x + 1) % i == 0) s.insert(x);
			for (int x = j - 1; x <= n; x += j)  // j | (x + 1)
				if ((x - 1) % i == 0) s.insert(x);
		}
	for (int i : s) printf("%d\n", i);
}