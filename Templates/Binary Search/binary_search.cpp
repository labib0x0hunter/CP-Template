int lo = 0;
int hi = arr.size() - 1;

int ans = -1;

while (lo <= hi) {

	int mid = lo + (hi - lo) / 2;

	if (arr[mid] == key) {
		ans = mid;
	}

	if (arr[mid] > key) hi = mid - 1; // upperbound : (>=) ans = mid

	else lo = mid + 1; // lowerbound : ans = mid
}