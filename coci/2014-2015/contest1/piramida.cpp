#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

#define pb push_back

using namespace std;

typedef long long LL;

const int MAXL = 1 << 20;

LL n;
int k;
LL l;
char word[MAXL];
vector<int> vec[32];

void read() {
	scanf("%lld\n", &n);
	scanf("%s", &word);
	scanf("%d", &k);
}

LL get(int letter, int rightBound) {	/// inclusive
	if(rightBound < 0 || vec[letter].empty() || vec[letter][0] > rightBound)
		return 0;
	
	if(vec[letter].back() <= rightBound)
		return (int)vec[letter].size();
	
	int le = 0, ri = (int)vec[letter].size() - 1, mid;
	int ret = -1;
	while(le <= ri) {
		mid = (le + ri) >> 1;
		if(vec[letter][mid] <= rightBound) {
			ret = mid;
			le = mid + 1;
		}
		else ri = mid - 1;
	}
	
	return ret + 1;
}

LL get(int letter, int le, int ri) {
	if(le > ri)
		return 0;
	
	return get(letter, ri) - get(letter, le - 1);
}

void solve() {
	l = strlen(word);
	for(int i = 0; i < l; i ++)
		vec[ word[i] - 'A' ].pb(i);
	
	LL a;
	char c;
	
	for(int i = 0; i < k; i ++) {
		scanf("%lld %c", &a, &c);
		
		LL mul1 = a, mul2 = a - 1;
		if(mul1 & 1) mul2 >>= 1;
		else mul1 >>= 1;
		
		if(mul1 >= l) mul1 %= l;
		if(mul2 >= l) mul2 %= l;
		
		LL startIndex = (mul1 * mul2) % l;
		
		int let = c - 'A';
		LL ans = 0;
		
		if(l - startIndex > a) ans += get(let, startIndex, startIndex + a - 1);
		else {
			ans += get(let, startIndex, l - 1);
			a -= (l - startIndex);
			ans += (LL)(a / l) * get(let, 0, l - 1);
			a %= l;
			ans += get(let, 0, a - 1);
		}
		
		printf("%lld\n", ans);
	}
}

int main()
{
	read();
	solve();

    return 0;
}
