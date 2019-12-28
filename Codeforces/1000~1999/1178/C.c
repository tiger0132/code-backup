typedef long long l;
const p = 998244353;
a = 1;
main(n, m, i) {
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n + m; i++) a = a * 2ll % p;
	printf("%d", a);
}