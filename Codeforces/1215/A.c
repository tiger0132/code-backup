main(a1, a2, k1, k2, n, m, t) {
	int a = 0;
	scanf("%d%d%d%d%d", &a1, &a2, &k1, &k2, &n);
	m = n - a1 * (k1 - 1) - a2 * (k2 - 1);
	m = m < a1 + a2 ? m : a1 + a2;
	if (k1 > k2) {
		t = k1, k1 = k2, k2 = t;
		t = a1, a1 = a2, a2 = t;
	}
	a += n / k1 < a1 ? n / k1 : a1;
	n -= a * k1;
	a += n / k2 < a2 ? n / k2 : a2;
	printf("%d %d", m > 0 ? m : 0, a);
}