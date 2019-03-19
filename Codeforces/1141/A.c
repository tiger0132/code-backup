a, b, c;
main() {
	scanf("%d%d", &a, &b);
	if (b % a) return !printf("-1");
	b /= a;
	while (b % 3 == 0) c++, b /= 3;
	while (b % 2 == 0) c++, b /= 2;
	if (b > 1)
		puts("-1");
	else
		printf("%d", c);
}