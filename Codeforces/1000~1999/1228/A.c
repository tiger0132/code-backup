f[111];
main(a, b, i, j) {
	scanf("%d%d", &a, &b);
	for (i = a; i <= b; i++) {
		for (j = 0; j < 10; j++) f[j] = 0;
		for (j = i; j; f[j % 10] = 1, j /= 10)
			if (f[j % 10]) goto end;
		return !printf("%d", i);
	end:;
	}
	puts("-1");
}