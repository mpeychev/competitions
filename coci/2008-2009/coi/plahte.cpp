#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define pb push_back

using namespace std;

typedef long long LL;

const int MAXN = 100100;

struct event {
	LL t;
	int i;
	int bit;
	
	event() {}
	event(LL _t, int _i, int _bit): t(_t), i(_i), bit(_bit) {}
};

struct group {
	LL sumX1, sumY1;
	LL sumX2, sumY2;
	LL free;
	LL count;
	
	group() {}
	group(LL _sumX1, LL _sumY1, LL _sumX2, LL _sumY2, LL _free, LL _count):
		sumX1(_sumX1), sumY1(_sumY1), sumX2(_sumX2), sumY2(_sumY2), free(_free), count(_count) {}
};

int n;
LL x1[MAXN], y1[MAXN];
LL x2[MAXN], y2[MAXN];

int mask[MAXN];
group g[16];

vector< event > vec;

bool cmp(event a, event b) {
	if(a.t != b.t)
		return a.t < b.t;
	
	if(a.i != b.i)
		return a.i > b.i;
	
	return a.bit < b.bit;
}

void init() {
	scanf("%d", &n);
	for(int i = 0; i < n; i ++) {
		scanf("%lld %lld %lld %lld", &x1[i], &y1[i], &x2[i], &y2[i]);
		
		LL valX = 0, valY = 0;
		if(x1[i] > 0) valX = x1[i];
		if(x2[i] < 0) valX = -x2[i];
		if(y1[i] > 0) valY = y1[i];
		if(y2[i] < 0) valY = -y2[i];
		
		LL startValid = max(valX, valY);
		mask[i] = 15;
		if(startValid < x2[i]) {
			mask[i] ^= 1;
			vec.pb(event(x2[i], i, 0));
		}
		if(-startValid > x1[i]) {
			mask[i] ^= 2;
			vec.pb(event(-x1[i], i, 1));
		}
		if(startValid < y2[i]) {
			mask[i] ^= 4;
			vec.pb(event(y2[i], i, 2));
		}
		if(-startValid > y1[i]) {
			mask[i] ^= 8;
			vec.pb(event(-y1[i], i, 3));
		}
		
		vec.pb(event(startValid, i, -1));
	}
	
	int m;
	LL t;
	scanf("%d", &m);
	for(int i = 0; i < m; i ++) {
		scanf("%lld", &t);
		vec.pb(event(t, -1, -1));
	}
	
	sort(vec.begin(), vec.end(), cmp);
	
	for(int i = 0; i <= 15; i ++)
		g[i] = group(0, 0, 0, 0, 0, 0);
}

void updateGroup(int groupIndex, int rectIndex, LL coef) {
	g[groupIndex].sumX1 += coef * x1[rectIndex];
	g[groupIndex].sumX2 += coef * x2[rectIndex];
	g[groupIndex].sumY1 += coef * y1[rectIndex];
	g[groupIndex].sumY2 += coef * y2[rectIndex];
	g[groupIndex].count += coef;
	
	if(groupIndex == 5) g[groupIndex].free += coef * x2[rectIndex] * y2[rectIndex];
	if(groupIndex == 6) g[groupIndex].free -= coef * x1[rectIndex] * y2[rectIndex];
	if(groupIndex == 7) g[groupIndex].free += coef * (x2[rectIndex] * y2[rectIndex] - x1[rectIndex] * y2[rectIndex]);
	if(groupIndex == 9) g[groupIndex].free -= coef * x2[rectIndex] * y1[rectIndex];
	if(groupIndex == 10) g[groupIndex].free += coef * x1[rectIndex] * y1[rectIndex];
	if(groupIndex == 11) g[groupIndex].free += coef * (x1[rectIndex] * y1[rectIndex] - x2[rectIndex] * y1[rectIndex]);
	if(groupIndex == 13) g[groupIndex].free += coef * (x2[rectIndex] * y2[rectIndex] - x2[rectIndex] * y1[rectIndex]);
	if(groupIndex == 14) g[groupIndex].free += coef * (x1[rectIndex] * y1[rectIndex] - x1[rectIndex] * y2[rectIndex]);
	if(groupIndex == 15) g[groupIndex].free += coef * (x2[rectIndex] * y2[rectIndex] + x1[rectIndex] * y1[rectIndex] -
													   x2[rectIndex] * y1[rectIndex] - x1[rectIndex] * y2[rectIndex]);
}

LL calc(int idx, LL t) {
	switch(idx) {
		case 1:
			return 2LL * t * g[idx].sumX2 + (2LL * t * t + 3LL * t) * g[idx].count + g[idx].sumX2 + g[idx].count;
		case 2:
			return -2LL * t * g[idx].sumX1 + (2LL * t * t + 3LL * t) * g[idx].count - g[idx].sumX1 + g[idx].count;
		case 3:
			return 2LL * t * (g[idx].sumX2 - g[idx].sumX1) + g[idx].sumX2 - g[idx].sumX1 + 2LL * t * g[idx].count + g[idx].count;
		case 4:
			return 2LL * t * g[idx].sumY2 + (2LL * t * t + 3LL * t) * g[idx].count + g[idx].sumY2 + g[idx].count;
		case 5:
			return g[idx].free + t * (g[idx].sumX2 + g[idx].sumY2) + g[idx].sumX2 + g[idx].sumY2 +
				   (t * t + 2LL * t) * g[idx].count + g[idx].count;
		case 6:
			return g[idx].free + t * (-g[idx].sumX1 + g[idx].sumY2) - g[idx].sumX1 + g[idx].sumY2 +
				   (t * t + 2LL * t) * g[idx].count + g[idx].count;
		case 7:
			return g[idx].free + t * (g[idx].sumX2 - g[idx].sumX1) + g[idx].sumX2 - g[idx].sumX1 + g[idx].sumY2 +
				   t * g[idx].count + g[idx].count;
		case 8:
			return -2LL * t * g[idx].sumY1 + (2LL * t * t + 3LL * t) * g[idx].count - g[idx].sumY1 + g[idx].count;
		case 9:
			return g[idx].free + t * (g[idx].sumX2 - g[idx].sumY1) + g[idx].sumX2 - g[idx].sumY1 +
				   (t * t + 2LL * t) * g[idx].count + g[idx].count;
		case 10:
			return g[idx].free - t * (g[idx].sumX1 + g[idx].sumY1) - g[idx].sumX1 - g[idx].sumY1 +
				   (t * t + 2LL * t) * g[idx].count + g[idx].count;
		case 11:
			return g[idx].free + t * (g[idx].sumX2 - g[idx].sumX1) + g[idx].sumX2 - g[idx].sumX1 - g[idx].sumY1 +
				   t * g[idx].count + g[idx].count;
		case 12:
			return 2LL * t * (g[idx].sumY2 - g[idx].sumY1) + g[idx].sumY2 - g[idx].sumY1 + 2LL * t * g[idx].count + g[idx].count;
		case 13:
			return g[idx].free + t * (g[idx].sumY2 - g[idx].sumY1) + g[idx].sumX2 + g[idx].sumY2 - g[idx].sumY1 +
				   t * g[idx].count + g[idx].count;
		case 14:
			return g[idx].free + t * (g[idx].sumY2 - g[idx].sumY1) - g[idx].sumX1 + g[idx].sumY2 - g[idx].sumY1 +
				   t * g[idx].count + g[idx].count;
		case 15:
			return g[idx].free + g[idx].sumX2 - g[idx].sumX1 + g[idx].sumY2 - g[idx].sumY1 + g[idx].count;
		default:
			return 0;
	}
}

void findArea(LL t) {
	LL ret = 0;
	for(int i = 1; i <= 15; i ++)
		ret += calc(i, t);
	printf("%lld\n", ret);
}

void solve() {
	for(int iter = 0; iter < (int)vec.size(); iter ++)
		if(vec[iter].i != -1) {
			if(vec[iter].bit == -1) updateGroup(mask[ vec[iter].i ], vec[iter].i, 1);
			else {
				updateGroup(mask[ vec[iter].i ], vec[iter].i, -1);
				mask[ vec[iter].i ] |= (1 << vec[iter].bit);
				updateGroup(mask[ vec[iter].i ], vec[iter].i, 1);
			}
		}
		else findArea(vec[iter].t);
}

int main()
{
	init();
	solve();

    return 0;
}
