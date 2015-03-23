#include <stdio.h>
#include <iostream>
#include <deque>

using namespace std;

int n, x;
deque<int> list;
long long ans;

int add(int key) {
    int le = 0, ri = list.size() - 1, mid;
    int pos = 0;
    while(le <= ri) {
        mid = (le + ri) >> 1;
        if(list[mid] > key) {
            pos = mid;
            le = mid + 1;
        }
        else ri = mid - 1;
    }

    return list.size() - pos;
}

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i ++) {
        scanf("%d", &x);
        ans += add(x);
        while(!list.empty() && list.back() < x) list.pop_back();
        list.push_back(x);
    }
    cout << ans << endl;

    return 0;
}
