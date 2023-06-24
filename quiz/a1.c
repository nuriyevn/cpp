#include <stdio.h>

int main ()
{
    int a,p,n,l,i;
    int t;
    int digits[10];
    scanf ("%d",&a);

    l=0;
    n=0;
    p=1;
    while(a!=0)
    {
        t=a%10;
        //printf("%d ", t);
        digits [l]=t;
        l++;
        n=n+p*t;
        p=p*10;
        a = a/10;
    }

    for(i = l-1;i >= 0; i--)
        printf("%d ",digits[i]);

    printf("\n");	

}

