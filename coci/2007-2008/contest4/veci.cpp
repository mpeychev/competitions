#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

#define pb push_back

using namespace std;

vector<int> getVector(int num) {
	vector<int> d;
	while(num) {
		d.pb(num % 10);
		num /= 10;
	}
	return d;
}

bool check0(vector<int> &d) {
	for(int i = 0; i < (int)d.size() - 1; i ++)
		if(d[i] > d[i + 1])
			return false;
	return true;
}

int main()
{
	int x;
	cin >> x;
	
	vector<int> d;
	d = getVector(x);
	
	if(check0(d)) {
		cout << 0 << endl;
		return 0;
	}
	
	sort(d.begin(), d.end());
	
	vector<int> t;
	for(int i = x + 1; ; i ++) {
		t = getVector(i);
		sort(t.begin(), t.end());
		if(t == d) {
			cout << i << endl;
			break;
		}
	}

    return 0;
}
