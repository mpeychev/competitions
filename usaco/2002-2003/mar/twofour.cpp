#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int n;
short int states[1024][8], sz;
short int dp[1024][32];

short int cmp(short int a[8], short int b[8]) {
	for(int i = 0; i < 5; i ++)
		if(a[i] > b[i]) return 1;
		else if(a[i] < b[i]) return -1;
	
	return 0;
}

short int findIndex(short int vec[8]) {
	int le = 0, ri = sz - 1, mid;
	while(le <= ri) {
		mid = (le + ri) >> 1;
		
		short int d = cmp(states[mid], vec);
		
		if(d == 0) return mid;
		if(d == 1) ri = mid - 1;
		else le = mid + 1;
	}
	
	return -1;
}

short int go(int stateIndex, int firstOwn) {
	short int &ret = dp[stateIndex][firstOwn];
	
	if(ret != -1)
		return ret;
	
	int secondOwn = states[stateIndex][2] - firstOwn;
	
	if(states[stateIndex][2] == n) {
		ret = 0;
		if(firstOwn > secondOwn) ret = 1;
		else if(firstOwn < secondOwn) ret = 2;
		
		return ret;
	}
	
	bool draw = false;
	short int res;
	short int cur[8];
	
	for(int i = 0; i <= 2; i ++)
		for(int j = i + 2; j <= 4; j ++)
			if(states[stateIndex][i] && states[stateIndex][j]) {
				memcpy(cur, states[stateIndex], sizeof(states[stateIndex]));
				
				cur[i] --, cur[j] --;
				cur[i + 1] ++, cur[j - 1] ++;
				int nxtStateIndex = findIndex(cur);
				
				if(i != 2 && j != 2) {
					res = go(nxtStateIndex, secondOwn);
					
					if(res == 2) return ret = 1;
					if(res == 0) draw = true;
				}
				else {
					if(firstOwn) {
						res = go(nxtStateIndex, secondOwn);
						
						if(res == 2) return ret = 1;
						if(res == 0) draw = true;
					}
					
					if(secondOwn) {
						res = go(nxtStateIndex, secondOwn - 1);
						
						if(res == 2) return ret = 1;
						if(res == 0) draw = true;
					}
				}
			}
	
	if(draw) return ret = 0;
	return ret = 2;
}

int main()
{
	short int g, cnt[8], inp;
	
	scanf("%d %hd", &n, &g);
	
	for(int a = 0; a <= n; a ++)
		for(int b = 0; a + b <= n; b ++)
			for(int c = 0; a + b + c <= n; c ++)
				for(int d = 0; a + b + c + d <= n; d ++) {
					int e = n - a - b - c - d;
					if(b + 2 * c + 3 * d + 4 * e == 2 * n) {
						states[sz][0] = a;
						states[sz][1] = b;
						states[sz][2] = c;
						states[sz][3] = d;
						states[sz][4] = e;
						
						sz ++;
					}
				}
	
	memset(dp, -1, sizeof(dp));
	
	for( ; g; g --) {
		memset(cnt, 0, sizeof(cnt));
		for(int i = 0; i < n; i ++) {
			scanf("%hd", &inp);
			cnt[inp] ++;
		}
		
		printf("%hd\n", go(findIndex(cnt), cnt[2] / 2));
	}

    return 0;
}
