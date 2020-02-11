#include <stdio.h>
#include <math.h>

float function(float x)
{
    return sqrtf(64.0f-x*x)*log2f(x)-sinf(2*x);
}

int main()
{
    float x, a, b, eps;
    int count = 0;
    do
    {
        printf("Enter a:");
        scanf("%f", &a);
        printf("Enter b:");
        scanf("%f", &b);
        printf("Enter eps:");
        scanf("%f", &eps);
    }while((function(a)*function(b))>0 || (fabsf(a-b)<eps));

    while(fabsf(a-b)>eps)
    {
        ++count;
        x = (a+b)/2;
        if((!(x>0))&&(!(x<0)))
            break;
        if(function(a)*function(x)>0)
            a=x;
        if(function(b)*function(x)>0)
            b=x;
    }
    printf("x = %f, iteration = %d, precision = %f\n", x, count, eps);


    return 0;
}
