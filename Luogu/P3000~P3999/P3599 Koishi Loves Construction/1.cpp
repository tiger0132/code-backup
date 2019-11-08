#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51;
int op, n, m, f, inv[N];
void w() {
	for (int i = f = 2; i * i <= n; i++)
		if (!(n % i)) return void(f = 0);
}
int main() {
	for (inv[1] = 1, scanf("%d%*d", &op); ~scanf("%d", &n); puts(""))
		if (n == 1)
			printf("2 1");
		else if (op == 1)
			if (n % 2)
				printf("0");
			else
				for (int i = printf("2"); i <= n; i++)
					printf(" %d", i % 2 ? n - i + 1 : i - 1);
		else if (n == 4)
			printf("2 1 3 2 4");
		else if (w(), printf("%d", f), f)
			for (int i = printf(" 1"); i <= n; i++)
				printf(" %d", 1 + inv[i - 1]),
					inv[i] = 1ll * (n - n / i) * inv[n % i] % n;
}