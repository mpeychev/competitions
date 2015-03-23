#include <iostream>
#include <stdio.h>

using namespace std;

int na, nb;
int pos[1024];

int cmp(int x, int y) {
	printf("cmp %d %d\n", x, y);
	fflush(stdout);
	
	int ret;
	scanf("%d", &ret);
	return ret;
}

int findPos(int kIndex) {
	int le = na + 1, ri = na + nb, mid;
	int ret = na;
	while(le <= ri) {
		mid = (le + ri) >> 1;
		int _cmp = cmp(kIndex, mid);
		if(_cmp > 0) {
			ret = mid;
			le = mid + 1;
		}
		else ri = mid - 1;
	}
	return ret;
}

void rev(int x, int y) {
	if(x >= y) return;
	printf("reverse %d %d\n", x, y);
	fflush(stdout);
}

int main()
{
	scanf("%d %d", &na, &nb);
	
	for(int i = 1; i <= na; i ++)
		pos[i] = findPos(i);
	
	int cur;
	for(int i = 1; i <= na; i ++) {
		if(i == 1) cur = 1;
		else cur = pos[i - 1] - na + i;
		
		int target = pos[i];
		
		int len = target - cur + 1;
		int b1 = na - i + 1;
		int b2 = len - b1;
		
		if(b2) {
			rev(cur, target);
			rev(cur, cur + b2 - 1);
			rev(cur + b2, target);
		}
	}
	
	printf("end\n");
	fflush(stdout);
	
	return 0;
}
