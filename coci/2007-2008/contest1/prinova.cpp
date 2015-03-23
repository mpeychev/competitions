#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define pb push_back

using namespace std;

const int MAXN = 1 << 7;

int n, arr[MAXN], a, b;
vector< int > vec;

int ans, dist;

void read() {
	cin >> n;
	for(int i = 0; i < n; i ++)
		cin >> arr[i];
	cin >> a >> b;
}

int abss(int x) {
	if(x < 0) return -x;
	return x;
}

void check(int le, int ri, int cur) {
	if(cur % 2 == 0) return;
	if(cur < le || ri < cur) return;
	if(cur < a || b < cur) return;
	
	int _dist = min(abss(le - cur), abss(ri - cur));
	if(_dist > dist) {
		dist = _dist;
		ans = cur;
	}
}

void solve() {
	sort(arr, arr + n);
	
	if(a % 2 == 0) a ++;
	if(b % 2 == 0) b --;
	
	for(int i = 0; i < n; i ++)
		if(a <= arr[i] && arr[i] <= b) vec.pb(arr[i]);
		else if(arr[i] < a) {
			if(i == n - 1 || arr[i + 1] > a) vec.pb(arr[i]);
		}
		else {
			if(i == 0 || arr[i - 1] < b)vec.pb(arr[i]);
		}
	
	if(vec.size() == 1) {
		if(abss(a - vec[0]) > abss(b - vec[0])) cout << a << endl;
		else cout << b << endl;
		
		return;
	}
	
	dist = -1;
	
	if(vec[0] > a) {
		dist = vec[0] - a;
		ans = a;
	}
	
	if(vec.back() < b) {
		int _dist = b - vec.back();
		if(_dist > dist) {
			dist = _dist;
			ans = b;
		}
	}
	
	for(int i = 0; i < (int)vec.size() - 1; i ++) {
		check(vec[i], vec[i + 1], a);
		check(vec[i], vec[i + 1], b);
		check(vec[i], vec[i + 1], (vec[i] + vec[i + 1]) / 2);
		check(vec[i], vec[i + 1], (vec[i] + vec[i + 1]) / 2 + 1);
		check(vec[i], vec[i + 1], (vec[i] + vec[i + 1]) / 2 - 1);
	}
	
	cout << ans << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
