#include <iostream>
#include <stdio.h>
#include <stack>

using namespace std;

typedef long long LL;

const int MAXN = 300300;

int n, maxLog[MAXN];
LL vec[MAXN];
LL mn[MAXN][19], mx[MAXN][19];
LL ans;
stack<LL> st;
LL leftMax[MAXN], leftMin[MAXN];

void read() {
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%lld", &vec[i]);
}

void build() {
	maxLog[1] = 0;
	maxLog[2] = 1;
	for(int i = 3; i <= n; i ++)
		maxLog[i] = maxLog[i >> 1] + 1;
	
	for(int i = 0; i < n; i ++) {
		mn[i][0] = vec[i];
		mx[i][0] = vec[i];
	}
	
	for(int j = 1; j <= maxLog[n]; j ++)
		for(int i = 0; i + (1 << j) - 1 < n; i ++) {
			mn[i][j] = min(mn[i][j - 1], mn[ i + (1 << (j - 1)) ][j - 1]);
			mx[i][j] = max(mx[i][j - 1], mx[ i + (1 << (j - 1)) ][j - 1]);
		}
}

int getMin(int le, int ri) {
	int len = (ri - le + 1);
	return min(mn[le][ maxLog[len] ], mn[ri - (1 << maxLog[len]) + 1][ maxLog[len] ]);
}

int getMax(int le, int ri) {
	int len = (ri - le + 1);
	return max(mx[le][ maxLog[len] ], mx[ri - (1 << maxLog[len]) + 1][ maxLog[len] ]);
}

int goLeftMax() {
	leftMax[0] = 1;
	st.push(0);
	for(int i = 1; i < n; i ++) {
		while(!st.empty() && vec[ st.top() ] < vec[i])
			st.pop();
		
		if(st.empty()) leftMax[i] = i + 1;
		else {
			leftMax[i] = i - st.top();
			if(vec[ st.top() ] == vec[i]) st.pop();
		}
		
		st.push(i);
	}
}

int goRightMax(int idx) {
	if(idx == n - 1 || getMax(idx + 1, n - 1) <= vec[idx]) return n - idx;
	
	int le = idx + 1, ri = n - 1, mid;
	int ret = 0;
	
	while(le <= ri) {
		mid = (le + ri) >> 1;
		if(getMax(idx + 1, mid) <= vec[idx]) le = mid + 1;
		else {
			ret = mid;
			ri = mid - 1;
		}
	}
	
	return ret - idx;
}

int goLeftMin() {
	while(!st.empty()) st.pop();
	
	leftMin[0] = 1;
	st.push(0);
	for(int i = 1; i < n; i ++) {
		while(!st.empty() && vec[ st.top() ] > vec[i])
			st.pop();
		
		if(st.empty()) leftMin[i] = i + 1;
		else {
			leftMin[i] = i - st.top();
			if(vec[ st.top() ] == vec[i]) st.pop();
		}
		
		st.push(i);
	}
}

int goRightMin(int idx) {
	if(idx == n - 1 || getMin(idx + 1, n - 1) >= vec[idx]) return n - idx;
	
	int le = idx + 1, ri = n - 1, mid;
	int ret = 0;
	
	while(le <= ri) {
		mid = (le + ri) >> 1;
		if(getMin(idx + 1, mid) >= vec[idx]) le = mid + 1;
		else {
			ret = mid;
			ri = mid - 1;
		}
	}
	
	return ret - idx;
}

void solve() {
	LL left, right;
	
	for(int i = 0; i < n; i ++) {
		left = leftMax[i];
		right = goRightMax(i);
		ans += left * right * vec[i];
		
		left = leftMin[i];
		right = goRightMin(i);
		ans -= left * right * vec[i];
	}
	
	cout << ans << endl;
}

int main()
{
	read();
	build();
	goLeftMax();
	goLeftMin();
	solve();
	
	return 0;
}
