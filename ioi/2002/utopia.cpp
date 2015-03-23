#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

const int MAXN = 10100;

int n;
int nums[2 * MAXN];
int cmd[MAXN];

int vec[MAXN], pos[MAXN];
int ans[MAXN][2];

void read() {
	scanf("%d", &n);
	for(int i = 0; i < 2 * n; i ++)
		scanf("%d", &nums[i]);
	for(int i = 0; i < n; i ++)
		scanf("%d", &cmd[i]);
}

void go(bool fl) {
	sort(vec + 1, vec + n + 1);
	
	int br = 0;
	for(int i = 0; i < n; i ++)
		if(pos[i] != pos[i + 1])
			br ++;
	
	int le, ri;
	le = n - br;
	ri = le + 2;
	
	bool sign;
	
	if(pos[1] == 2) {
		ans[1][fl] = vec[le + 1];
		sign = true;
	}
	else {
		ans[1][fl] = -vec[le + 1];
		sign = false;
	}
	
	for(int i = 2; i <= n; i ++) {
		if(pos[i] != pos[i - 1]) {
			if(pos[i] == 2) ans[i][fl] = vec[ri ++];
			else ans[i][fl] = -vec[ri ++];
		}
		else {
			if(sign) ans[i][fl] = -vec[le --];
			else ans[i][fl] = vec[le --];
			
			sign ^= true;
		}
	}
}

void solve() {
	/// solve X
	for(int i = 0; i < n; i ++) {
		vec[i + 1] = nums[i];
		if(cmd[i] == 2 || cmd[i] == 3) pos[i + 1] = 1;
		else pos[i + 1] = 2;
	}
	go(0);
	
	/// solve Y
	for(int i = n; i < 2 * n; i ++) {
		vec[i - n + 1] = nums[i];
		if(cmd[i - n] == 1 || cmd[i - n] == 2) pos[i - n + 1] = 2;
		else pos[i - n + 1] = 1;
	}
	go(1);
}

void write() {
	for(int i = 1; i <= n; i ++) {
		if(ans[i][0] > 0) printf("+");
		printf("%d ", ans[i][0]);
		
		if(ans[i][1] > 0) printf("+");
		printf("%d\n", ans[i][1]);
	}
}

int main()
{
	read();
	solve();
	write();
	
	return 0;
}
