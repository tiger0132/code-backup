long long a, b;
double x;
main() {
	scanf("%lld%lld", &a, &b);
	printf("%.13f", (b * b - a * a) / 2. / a);
}