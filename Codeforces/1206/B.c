a[111111], mn = 1e9;
long long ans;
main(n, i, c, z) {
	scanf("%d", &n), z = c = 0;
	for (i = 0; i < n; i++) {
		scanf("%d", a + i);
		z += !a[i];
		if (a[i] >= 1) ans += a[i] - 1;
		if (a[i] <= -1) ans += -1 - a[i], c ^= 1;
	}
	ans += z;
	if (c && !z) ans += 2;
	printf("%lld", ans);
}