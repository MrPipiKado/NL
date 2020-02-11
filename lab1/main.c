#include <stdio.h>
#include <math.h>

double function(double x)
{//задана функція
    return sqrt(64.0f-x*x)*log2(x)-sin(2*x);
}

double func_poh_1(double x)
{//перша похідна
    return (-log2(x)/sqrt(64.0-x*x)) + (sqrt(64.0-x*x)/(x*M_LN2)) - 2*cos(2*x);
}

double func_poh_2(double x)
{//друга похідна
    return 4*sin(2*x) -(sqrt(64-x*x)/(x*x*M_LN2)) -
            ((x*x)/(sqrt((64.0-x*x)*(64.0-x*x)*(64.0-x*x))*log2(x))) -
            (2/(sqrt(64.0-x*x)*M_LN2)) - (1/(sqrt(64.0-x*x)*log2(x)));
}

int main()
{
    double x, x0, a, b, eps;
    int count = 0;
    do
    {
        printf("ODZ x є (0;8]\n");
        printf("Enter a:");
        scanf("%lf", &a);
        printf("Enter b:");
        scanf("%lf", &b);
        printf("Enter eps:");
        scanf("%lf", &eps);

    }while(a<0 || b<0 || a>8 || b>8 || //перевір ОДЗ
            (function(a)*function(b))>0 || (fabs(a-b)<eps));

    while(fabs(a-b)>eps)
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
    printf("x = %lf, iteration = %d, precision = %20.19lf\n", x, count, eps);

    do
    {
        printf("ODZ x є (0;8]\n");
        printf("Enter a:");
        scanf("%lf", &a);
        printf("Enter b:");
        scanf("%lf", &b);
        printf("Enter eps:");
        scanf("%lf", &eps);

    }while(a<0 || b<0 || a>8 || b>8 || //перевір ОДЗ
           (function(a)*function(b))>0 || (fabs(a-b)<eps));



    return 0;
}
