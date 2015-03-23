/*
  Source: usaco - 2001/2002 - feb
  Task: pasture
  KeyW: dp
*/
#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;

int n, l, s;
bool dp[2048][2048];
double ans = -1.0;

int main()
{
    scanf("%d", &n);
    dp[0][0] = 1;
    for(int i = 0; i < n; i ++)
    {
        scanf("%d", &l);
        s += l;
        for(int j = s; j >= 0; j --)
            for(int k = s; k >= 0; k --)
                if((j - l >= 0 && dp[j - l][k]) || (k - l >= 0 && dp[j][k - l]))
                    dp[j][k] = 1;
    }

    for(int i = 1; i <= s; i ++)
        for(int j = 1; j <= s; j ++)
            if(dp[i][j])
            {
                double a = (double)i;
                double b = (double)j;
                double c = (double)s - a - b;
                if(a + b > c && a + c > b && b + c > a)
                {
                    double p = (a + b + c) / 2;
                    double area = sqrt(p * (p - a) * (p - b) * (p - c));
                    if(area > ans) ans = area;
                }
            }

    if(ans == -1.0) printf("-1\n");
    else printf("%.0lf\n", floor(100 * ans));

    return 0;
}
