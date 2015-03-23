#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>

#define pb push_back

using namespace std;

const int MAXN = 100100;

int n, k;
char cmd[MAXN];
int x[MAXN], y[MAXN];
set<int> diff, sum;
vector<int> diffAll, sumAll;

set<int> stDiff[MAXN], stSum[MAXN];
set<int> negStDiff[MAXN], negStSum[MAXN];
set<int> :: iterator it;

void read() {
    scanf("%d %d\n", &n, &k);
    scanf("%s", &cmd);
    for(int i = 0; i < n; i ++)
        scanf("%d %d", &x[i], &y[i]);
}

int findInDiffAll(int k) {
    int le = 0, ri = diffAll.size() - 1, mid;
    while(le <= ri) {
        mid = (le + ri) >> 1;
        if(diffAll[mid] == k) return mid;
        if(diffAll[mid] > k) ri = mid - 1;
        else le = mid + 1;
    }
    return -1;
}

int findInSumAll(int k) {
    int le = 0, ri = sumAll.size() - 1, mid;
    while(le <= ri) {
        mid = (le + ri) >> 1;
        if(sumAll[mid] == k) return mid;
        if(sumAll[mid] > k) ri = mid - 1;
        else le = mid + 1;
    }
    return -1;
}

void removeDiff(int k, int idx) {
    stDiff[idx].erase(k);
    negStDiff[idx].erase(-k);
}

void removeSum(int k, int idx) {
    stSum[idx].erase(k);
    negStSum[idx].erase(-k);
}

void solve() {
    for(int i = 0; i < n; i ++) {
        sum.insert(x[i] + y[i]);
        diff.insert(x[i] - y[i]);
    }

    for(it = diff.begin(); it != diff.end(); it ++)
        diffAll.pb(*it);
    for(it = sum.begin(); it != sum.end(); it ++)
        sumAll.pb(*it);

    for(int i = 0; i < n; i ++) {
        int idx;

        idx = findInDiffAll(x[i] - y[i]);
        stDiff[idx].insert(x[i]);
        negStDiff[idx].insert(-x[i]);

        idx = findInSumAll(x[i] + y[i]);
        stSum[idx].insert(x[i]);
        negStSum[idx].insert(-x[i]);
    }

    int curX = x[0], curY = y[0];
    for(int i = 0; i < k; i ++) {
        int curSum = curX + curY;
        int curDiff = curX - curY;

        int idxSum = findInSumAll(curSum);
        int idxDiff = findInDiffAll(curDiff);

        int nxtX, nxtY;

        if(cmd[i] == 'A') {
            it = stDiff[idxDiff].lower_bound(curX);
            it ++;
            if(it == stDiff[idxDiff].end()) continue;
            nxtX = *it;
            nxtY = nxtX - curDiff;
        }

        if(cmd[i] == 'B') {
            it = stSum[idxSum].lower_bound(curX);
            it ++;
            if(it == stSum[idxSum].end()) continue;
            nxtX = *it;
            nxtY = curSum - nxtX;
        }

        if(cmd[i] == 'C') {
            it = negStSum[idxSum].lower_bound(-curX);
            it ++;
            if(it == negStSum[idxSum].end()) continue;
            nxtX = -(*it);
            nxtY = curSum - nxtX;
        }

        if(cmd[i] == 'D') {
            it = negStDiff[idxDiff].lower_bound(-curX);
            it ++;
            if(it == negStDiff[idxDiff].end()) continue;
            nxtX = -(*it);
            nxtY = nxtX - curDiff;
        }

        removeDiff(curX, idxDiff);
        removeSum(curX, idxSum);

        curX = nxtX;
        curY = nxtY;
    }

    cout << curX << " " << curY << endl;
}

int main()
{
    read();
    solve();

    return 0;
}
