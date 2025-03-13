// Find strictly smaller value of arr[i] in left
// Returns the index
// -1 means no smaller value
vector<int> next_smaller(vector<int>& arr) {
	int n = arr.size();
	stack<int> st; st.push(-1);
	vector<int> index;
	for (int i = 0; i < n; i++) {
		while (!st.empty() and st.top() != -1) {
			if (arr[i] <= arr[st.top()])
				st.pop();
			else break;
		}
		index.push_back(st.top());
		st.push(i);
	}
	return index;
}

// Find strictly greater value of arr[i] in left
// Returns the index
// -1 means no greater value
vector<int> next_greater(vector<int>& arr) {
	int n = arr.size();
	stack<int> st; st.push(-1);
	vector<int> index;
	for (int i = 0; i < n; i++) {
		while (!st.empty() and st.top() != -1) {
			if (arr[i] >= arr[st.top()])
				st.pop();
			else break;
		}
		index.push_back(st.top());
		st.push(i);
	}
	return index;
}

// // Range Coverage For Smaller Value
// auto L = next_smaller(arr);
// ranges::reverse(arr);
// auto R = next_smaller(arr);
// ranges::reverse(arr);
// ranges::reverse(R);

// for (int i = 0; i < n; i++) {
// 	L[i]++;
// 	R[i]++;
// 	R[i] = n - R[i] - 1;
// }
