#include <iostream>
#include <stdio.h>
#include <stack>

using namespace std;

typedef long long LL;

const int MAXN = 3000005;

int n, k;
LL x, y, a, b;
int nxt[MAXN];
bool used[MAXN];
stack<int> st;

int getNext(int pos) {
	while(used[ nxt[pos] ]) {
		st.push(pos);
		pos = nxt[pos];
	}
	
	int ret = nxt[pos];
	while(!st.empty()) {
		nxt[ st.top() ] = ret;
		st.pop();
	}
	
	return ret;
}

void put(int pos) {
	if(used[pos]) pos = getNext(pos);
	used[pos] = true;
}

int main()
{
	freopen("empty.in", "r", stdin);
	freopen("empty.out", "w", stdout);
	
	scanf("%d %d", &n, &k);
	
	for(int i = 0; i < n - 1; i ++)
		nxt[i] = i + 1;
	nxt[n - 1] = 0;
	
	for( ; k; k --) {
		scanf("%lld %lld %lld %lld", &x, &y, &a, &b);
		for(LL i = 1; i <= y; i ++)
			for(int j = 0; j < x; j ++)
				put((a * i + b) % n);
	}
	
	for(int i = 0; i < n; i ++)
		if(!used[i]) {
			cout << i << endl;
			return 0;
		}
	cout << "-1\n";
	
	return 0;
}
