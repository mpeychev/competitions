#include <iostream>
#include <stdio.h>

using namespace std;

int r, c, zr, zc;
char s[64];

int main()
{
    scanf("%d %d %d %d\n", &r, &c, &zr, &zc);
    for(int i = 0; i < r; i ++) {
        scanf("%s", &s);
        for(int j = 0; j < zr; j ++) {
            for(int k = 0; k < c; k ++)
                for(int h = 0; h < zc; h ++)
                    printf("%c", s[k]);
            printf("\n");
        }
    }

    return 0;
}
