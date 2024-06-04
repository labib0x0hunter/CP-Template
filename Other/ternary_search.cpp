int lo = 0, hi = a / b;
while (hi - lo > 2) {
	int mid1 = (lo + lo + hi) / 3;
	int mid2 = (lo + hi + hi) / 3;
	if (check(mid1) > check(mid2)) lo = mid1;
	else hi = mid2;
}