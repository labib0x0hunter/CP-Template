int mask = 10; // bit_set
while (mask) {
	int p = LSONE(mask);
	int sub = tailing_zero(p);

	mask -= p;
	// subset
	cout << arr[sub] << " ";
}