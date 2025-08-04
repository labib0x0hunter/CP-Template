// Count how many numbers has bit k on in range [0, n]
template<typename T = int>
T count_set_bit(T n, int k)
{
	n += 1;
	T res = (n >> (k + 1)) << k;
	if ((n >> k) & 1)
		res += n & ((1ll << k) - 1);
	return res;
}