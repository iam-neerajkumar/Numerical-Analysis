#include<stdio.h>
int main()
{
    int a, b, c, i,n ;
    n=20;
    a=0;
    b=1;
    printf("Fibonacci numbers\n");
    printf("%d\n%d\n",a,b);

    for ( i = 0; i < n-2; i++)
    {
        c= a+b;
        printf("%d\t\n",c);
        a=b;
        b=c;
        
    }
    
    return 0;
}

