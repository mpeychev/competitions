#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>
#include <vector>

#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> PII;

int ma3x[32][32];

int fact[16];
int level[400400];
PII move[400400];
queue<int> q;

int perm2num(int *p, int n) {
    int ret = 0;
    bool used[16];
    memset(used, 0, sizeof(used));

    for(int i = 0; i < n; i ++) {
        int br = 0;
        for(int j = 1; j < p[i]; j ++)
            if(!used[j])
                br ++;
        ret += br * fact[n - i - 1];
        used[ p[i] ] = true;
    }
    return ret;
}

int* num2perm(int k, int n) {
    int *p;
    p = new int[n];

    bool used[16];
    memset(used, 0, sizeof(used));

    for(int i = 0; i < n; i ++)
        for(int j = 1; j <= n; j ++)
            if(!used[j]) {
                if(fact[n - i - 1] <= k) k -= fact[n - i - 1];
                else {
                    p[i] = j;
                    used[j] = true;
                    break;
                }
            }

    return p;
}

void rotateRow(int *p, int i, int j, int c) {
    int idx1, idx2, idx3, idx4, val;

    idx1 = i * c + j;
    idx2 = idx1 + 1;
    idx3 = idx1 + c;
    idx4 = idx3 + 1;

    val = p[idx1];
    p[idx1] = p[idx3];
    p[idx3] = p[idx4];
    p[idx4] = p[idx2];
    p[idx2] = val;
}

void rotateRowBack(int *p, int i, int j, int c) {
    int idx1, idx2, idx3, idx4, val;

    idx1 = i * c + j;
    idx2 = idx1 + 1;
    idx3 = idx1 + c;
    idx4 = idx3 + 1;

    val = p[idx1];
    p[idx1] = p[idx2];
    p[idx2] = p[idx4];
    p[idx4] = p[idx3];
    p[idx3] = val;
}

void bfs(int *p, int r, int c) {
    int code, nxtCode;
    int n = r * c;

    code = perm2num(p, n);
    level[code] = 1;
    move[code] = mp(-1, -1);
    q.push(code);

    while(!q.empty()) {
        int *nxt;
        code = q.front();
        q.pop();

        if(!code) break;

        for(int i = 0; i < r - 1; i ++)
            for(int j = 0; j < c - 1; j ++) {
                nxt = num2perm(code, n);
                rotateRow(nxt, i, j, c);
                nxtCode = perm2num(nxt, n);
                if(!level[nxtCode]) {
                    level[nxtCode] = level[code] + 1;
                    q.push(nxtCode);
                    move[nxtCode] = mp(i, j);
                }
            }
    }

    code = 0;
    vector< PII > vec;
    while(1) {
        int i, j;
        i = move[code].first;
        j = move[code].second;

        if(i == -1 || j == -1) break;

        vec.pb(move[code]);
        p = num2perm(code, n);
        rotateRowBack(p, i, j, c);
        code = perm2num(p, n);
    }

    for(int i = vec.size() - 1; i >= 0; i --)
        printf("%d %d\n", vec[i].first + 1, vec[i].second + 1);
}

void rotate2n(int** p, int i, int j) {
    printf("%d %d\n", i + 1, j + 1);

    int val = p[i][j];
    p[i][j] = p[i + 1][j];
    p[i + 1][j] = p[i + 1][j + 1];
    p[i + 1][j + 1] = p[i][j + 1];
    p[i][j + 1] = val;
}

void solve2n(int** p, int n) {
    int x, y;

    for(int col = n - 1; col >= 4; col --) {
        int a = col + 1;
        int b = a + n;

        if(p[0][col] == a && p[1][col] == b) continue;

        for(int i = 0; i < 2; i ++)
            for(int j = 0; j <= col; j ++)
                if(p[i][j] == b) {
                    x = i;
                    y = j;
                }

        if(x == 1) {
            if(y) {
                rotate2n(p, 0, y - 1);
                rotate2n(p, 0, y - 1);
                rotate2n(p, 0, y - 1);
            }
            else rotate2n(p, 0, y);
            x = 0;
        }

        for(int i = y; i < col; i ++)
            rotate2n(p, 0, i);

        for(int i = 0; i < 2; i ++)
            for(int j = 0; j <= col; j ++)
                if(p[i][j] == a) {
                    x = i;
                    y = j;
                }

        if(x == 1 && y == col) {
            rotate2n(p, 0, col - 1);
            rotate2n(p, 0, col - 2);

            rotate2n(p, 0, col - 1);
            rotate2n(p, 0, col - 1);
            rotate2n(p, 0, col - 1);

            rotate2n(p, 0, col - 2);
            rotate2n(p, 0, col - 2);
        }
        else {
            if(x == 1) {
                if(y) {
                    rotate2n(p, 0, y - 1);
                    rotate2n(p, 0, y - 1);
                    rotate2n(p, 0, y - 1);
                }
                else rotate2n(p, 0, y);
                x = 0;
            }

            for(int i = y; i < col - 1; i ++)
                rotate2n(p, 0, i);
        }

        rotate2n(p, 0, col - 1);
    }

    int *p2;
    int sz = 0;
    int val;

    p2 = new int[8];
    for(int i = 0; i < 2; i ++)
        for(int j = 0; j < 4; j ++) {
            val = p[i][j];
            if(val > 4) val = val - n + 4;
            p2[sz ++] = val;
        }

    bfs(p2, 2, 4);
}

void rotateMa3x(int i, int j) {
    printf("%d %d\n", i + 1, j + 1);

    int val = ma3x[i][j];
    ma3x[i][j] = ma3x[i + 1][j];
    ma3x[i + 1][j] = ma3x[i + 1][j + 1];
    ma3x[i + 1][j + 1] = ma3x[i][j + 1];
    ma3x[i][j + 1] = val;
}

void moveNum(int num, int r, int c, int tx, int ty) {
    int x, y;
    for(int i = 0; i < r; i ++)
        for(int j = 0; j < c; j ++)
            if(ma3x[i][j] == num) {
                x = i;
                y = j;
            }

    if(x == 0) {
        if(!y) {
            rotateMa3x(0, 0);
            rotateMa3x(0, 0);
            y = 1;
        }
        else rotateMa3x(x, y - 1);
        x = 1;
    }

    if(y < ty) {
        for(int i = y; i < ty; i ++)
            for(int j = 0; j < 3; j ++)
                rotateMa3x(x - 1, i);
    }

    if(y > ty) {
        for(int i = y - 1; i >= ty; i --)
            rotateMa3x(x - 1, i);
    }

    for(int i = x; i < tx; i ++)
        rotateMa3x(i, ty - 1);
}

int main()
{
    int r, c, n;
    int *p;

    /* read - begin */
    scanf("%d %d", &r, &c);
    for(int i = 0; i < r; i ++)
        for(int j = 0; j < c; j ++)
            scanf("%d", &ma3x[i][j]);
    /* read - end */

    /* init - begin */
    fact[0] = 1;
    for(int i = 1; i <= 10; i ++)
        fact[i] = fact[i - 1] * i;
    /* init - end */

    if(r * c <= 9) {
        n = 0;
        p = new int[r * c];
        for(int i = 0; i < r; i ++)
            for(int j = 0; j < c; j ++)
                p[n ++] = ma3x[i][j];

        bfs(p, r, c);
        return 0;
    }

    for(int row = r - 1; row >= 2; row --) {
        for(int j = c - 1; j >= 2; j --)
            moveNum(row * c + j + 1, r, c, row, j);
        moveNum(row * c + 1, r, c, row, 1);

        int b = row * c + 2;
        int x, y;
        for(int i = 0; i < r; i ++)
            for(int j = 0; j < c; j ++)
                if(ma3x[i][j] == b) {
                    x = i;
                    y = j;
                }

        if(x != row) moveNum(b, r, c, row - 1, 1);
        else {
            rotateMa3x(row - 1, 0);
            rotateMa3x(row - 2, 0);

            rotateMa3x(row - 1, 0);
            rotateMa3x(row - 1, 0);
            rotateMa3x(row - 1, 0);

            rotateMa3x(row - 2, 0);
            rotateMa3x(row - 2, 0);
        }

        rotateMa3x(row - 1, 0);
    }

    int **s;
    s = new int*[2];
    for(int i = 0; i < 2; i ++)
        s[i] = new int[c];

    for(int i = 0; i < 2; i ++)
        for(int j = 0; j < c; j ++)
            s[i][j] = ma3x[i][j];

    solve2n(s, c);

    return 0;
}
