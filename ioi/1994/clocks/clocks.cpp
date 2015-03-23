#include <iostream>

#define rep(i) for(int i=0;i<4;i++)
using namespace std;

int sol=100;
int tmp[16];

int main()
{
    int a,b,c,d,e,f,g,h,i;
    
    cin >> a >> b >> c >> d >> e >> f >> g >> h >> i;
    a/=3; b/=3; c/=3; d/=3; e/=3; f/=3; g/=3; h/=3; i/=3;
    
    rep(i1)
     rep(i2)
      rep(i3)
       rep(i4)
        rep(i5)
         rep(i6)
          rep(i7)
           rep(i8)
            rep(i9)
            {
                   if(i1+i2+i3+i4+i5+i6+i7+i8+i9<sol &&
                      (a+i1+i2+i4)%4==0 &&
                      (b+i1+i2+i3+i5)%4==0 &&
                      (c+i2+i3+i6)%4==0 &&
                      (d+i1+i4+i5+i7)%4==0 &&
                      (e+i1+i3+i5+i7+i9)%4==0 &&
                      (f+i3+i5+i6+i9)%4==0 &&
                      (g+i4+i7+i8)%4==0 &&
                      (h+i5+i7+i8+i9)%4==0 &&
                      (i+i6+i8+i9)%4==0
                     ) { tmp[1]=i1; tmp[2]=i2; tmp[3]=i3; tmp[4]=i4; tmp[5]=i5; tmp[6]=i6; tmp[7]=i7; tmp[8]=i8; tmp[9]=i9; 
                         sol=i1+i2+i3+i4+i5+i6+i7+i8+i9;
                       }
            }
    
    int l=10;
    for(int i=9;i>=1;i--) if(tmp[i]!=0) { l=i; break; }
    
    for(int i=1;i<l;i++)
     for(int j=0;j<tmp[i];j++) cout << i << " ";
    
    for(int i=0;i<tmp[l]-1;i++) cout << l << " ";
    cout << l << endl;
    
    return 0;
}
/*
Move 	 Affected clocks
1 	ABDE
2 	ABC
3 	BCEF
4 	ADG
5 	BDEFH
6 	CFI
7 	DEGH
8 	GHI
9 	EFHI
*/
