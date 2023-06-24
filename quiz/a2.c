#include <stdio.h>

int main() 
{
    int a,digits[10],count,i,t;
    scanf("%d",&a);
    count=0;
    while (a!=0) 
    {
        t=a%10;
        digits[count]=t;
        a=a/10;
        count=count+1;
    }

    for (i=count-1; i>=0;i--)
    printf("%d ",digits[i]);

}
