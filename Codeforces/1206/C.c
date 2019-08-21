int n;
main() {
	scanf("%d", &n);
	if (!(n % 2)) return puts("NO"), 0;
	puts("YES");
	printf("1 ");
	for (int i = 4; i <= 2 * n; i += 4) printf("%d %d ", i, i + 1);
	for (int i = 2; i <= 2 * n; i += 4) printf(i == 2 * n ? "%d" : "%d %d ", i, i + 1);
}