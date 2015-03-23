#include <iostream>
#include <stdio.h>
#include <set>

#define mp make_pair

using namespace std;

typedef unsigned long long ULL;
typedef pair< ULL, ULL > PUU;

const int MAXN = 1 << 10;

const ULL prime1 = 43;
const ULL prime2 = 257;

const ULL MOD1 = 65243625723481LL;
const ULL MOD2 = 847346902559LL;

int r, c;
char ma3x[MAXN][MAXN];
PUU h[MAXN][MAXN];
int ans = 0;

void read() {
	scanf("%d %d\n", &r, &c);
	for(int i = 0; i < r; i ++)
		scanf("%s", &ma3x[i]);
}

void solve() {
	for(int i = 0; i < c; i ++)
		h[r - 1][i] = mp(ma3x[r - 1][i] - 'a' + 1, ma3x[r - 1][i] + 1);
	
	for(int i = r - 2; i >= 0; i --)
		for(int j = 0; j < c; j ++) {
			h[i][j].first = (h[i + 1][j].first * prime1 + (ma3x[i][j] - 'a' + 1)) % MOD1;
			h[i][j].second = (h[i + 1][j].second * prime2 + (ma3x[i][j] - 'a' + 1)) % MOD2;
		}
	
	for(int i = 0; i < r - 1; i ++) {
		bool fl = true;
		set< PUU > st;
		
		for(int j = 0; j < c; j ++)
			if(st.find(h[i + 1][j]) != st.end()) {
				fl = false;
				break;
			}
			else st.insert(h[i + 1][j]);
		
		if(!fl) break;
		
		ans ++;
	}
	
	cout << ans << endl;
}

int main()
{
	read();
	solve();

    return 0;
}
