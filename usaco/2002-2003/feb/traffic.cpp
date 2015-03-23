#include <iostream>
#include <stdio.h>
#include <queue>

using namespace std;

const int MAXV = 10;
const int MAXT = 1500;

struct TrafficLight {
	int timeGreen;
	int timeRed;
	char initColor;
	int timeInitColor;
	
	TrafficLight() {}
	TrafficLight(int _Tg, int _Tr, char _color, int _Tc): timeGreen(_Tg), timeRed(_Tr), initColor(_color), timeInitColor(_Tc) {}
};

struct el {
	int p, v, t;
	
	el() {}
	el(int _p, int _v, int _t): p(_p), v(_v), t(_t) {}
};

int l, n;
TrafficLight tr[128];
bool used[105][12][1515];
queue< el > q;
el nxt;

void init() {
	scanf("%d %d", &l, &n);
	
	for(int i = 0; i <= l; i ++)
		tr[i] = TrafficLight(-1, -1, 'N', -1);
	
	int pos;
	for(int i = 0; i < n; i ++) {
		scanf("%d", &pos);
		scanf("%d %d %c %d", &tr[pos].timeGreen, &tr[pos].timeRed, &tr[pos].initColor, &tr[pos].timeInitColor);
	}
}

bool check(int idx, int moment) {
	if(tr[idx].timeGreen == -1)
		return true;
	
	int Tg = tr[idx].timeGreen;
	int Tr = tr[idx].timeRed;
	char ch = tr[idx].initColor;
	int Tc = tr[idx].timeInitColor;
	
	moment += Tc;
	moment %= (Tg + Tr);
	
//	cout << "Test " << ch << " " << Tr << " " << Tg << " " << moment << endl;
	
	if(ch == 'R') return moment >= Tr;
	return moment < Tg;
}

void solve() {
	q.push(el(0, 0, 0));
	used[0][0][0] = true;
	
	while(!q.empty()) {
		el tmp = q.front();
		q.pop();
		
//		cout << tmp.p << " " << tmp.v << " " << tmp.t << endl;
		
		if(tmp.p + (tmp.v * (tmp.v + 1)) / 2 > l) continue;
		
		if(tmp.p == l) {
			if(tmp.v == 0) {
				cout << tmp.t << endl;
				return;
			}
			continue;
		}
		
		bool fl = true;
		for(int i = tmp.p; i < tmp.p + tmp.v; i ++)
			if(!check(i, tmp.t)) {
				fl = false;
				break;
			}
		
		if(fl) {
//			cout << "Can go\n";
			
			nxt.p = tmp.p + tmp.v;
			nxt.t = tmp.t + 1;
			
//			cout << "potential adds: " << nxt.p << " " << nxt.t << endl;
			
			nxt.v = tmp.v;
			if(nxt.t < MAXT && nxt.p <= l && !used[nxt.p][nxt.v][nxt.t]) {
				used[nxt.p][nxt.v][nxt.t] = true;
				q.push(nxt);
//				cout << "ADD " << nxt.p << " " << nxt.v << " " << nxt.t << endl;
			}
			
			nxt.v = tmp.v + 1;
			if(nxt.t < MAXT && nxt.p <= l && nxt.v <= MAXV && !used[nxt.p][nxt.v][nxt.t]) {
				used[nxt.p][nxt.v][nxt.t] = true;
				q.push(nxt);
//				cout << "ADD " << nxt.p << " " << nxt.v << " " << nxt.t << endl;
			}
			
			nxt.v = tmp.v - 1;
			if(nxt.t < MAXT && nxt.p <= l && nxt.v >= 0 && !used[nxt.p][nxt.v][nxt.t]) {
				used[nxt.p][nxt.v][nxt.t] = true;
				q.push(nxt);
//				cout << "ADD " << nxt.p << " " << nxt.v << " " << nxt.t << endl;
			}
//			cout << endl;
		}
	}
	
	cout << "-1\n";
}

int main()
{
	init();
	solve();

    return 0;
}
