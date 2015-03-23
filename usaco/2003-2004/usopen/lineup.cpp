#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAXK = 10100;

int n, k, a;
bool used[MAXK];
int cnt, ans;

int main()
{
    scanf("%d %d", &n, &k);
    for(int i = 0; i < n; i ++) {
        scanf("%d", &a);
        if(!used[a]) {
            used[a] = true;
            cnt ++;

            if(cnt == k) {
                ans ++;
                cnt = 0;
                memset(used, 0, sizeof(used));
            }
        }
    }

    cout << ans + 1 << endl;

    return 0;
}
