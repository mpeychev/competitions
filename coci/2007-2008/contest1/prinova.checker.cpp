#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;

FILE *inp, *sol, *mysol;

const int MAXN = 1 << 7;

int n, arr[MAXN];
int a, b;

int solPos, mySolPos;

int dist1, dist2;

void readInput() {
	fscanf(inp, "%d", &n);
	for(int i = 0; i < n; i ++)
		fscanf(inp, "%d", &arr[i]);
	fscanf(inp, "%d %d", &a, &b);
}

void readSolution() {
	fscanf(sol, "%d", &solPos);
}

void readMySolution() {
	fscanf(mysol, "%d", &mySolPos);
}

int abss(int x) {
	if(x < 0) return -x;
	return x;
}

int main(int argc, char** argv)
{
	inp = fopen(argv[1], "r");
	sol = fopen(argv[2], "r");
	mysol = fopen(argv[3], "r");
	
	readInput();
	readSolution();
	readMySolution();
	
	cout << "Author solution - " << solPos << endl;
	cout << "My solution - " << mySolPos << endl;
	
	if(mySolPos % 2 == 0) {
		cout << "wa - even\n";
		return 0;
	}
	
	if(mySolPos < a || mySolPos > b) {
		cout << "wa - out of range\n";
		return 0;
	}
	
	dist1 = abss(solPos - arr[0]);
	for(int i = 1; i < n; i ++)
		dist1 = min(dist1, abss(solPos - arr[i]));
	
	dist2 = abss(mySolPos - arr[0]);
	for(int i = 1; i < n; i ++)
		dist2 = min(dist2, abss(mySolPos - arr[i]));
	
	cout << "dist1 = " << dist1 << endl;
	cout << "dist2 = " << dist2 << endl;
	
	if(dist1 < dist2) {
		cout << "wa - answer dist is lower\n";
		return 0;
	}
	
	if(dist1 > dist2) {
		cout << "wa - answer dist is higher\n";
		return 0;
	}
	
	cout << "ok\n";

    return 0;
}
