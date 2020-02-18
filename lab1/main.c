#include <stdio.h>
#include <math.h>
#include <cs50.h>
double function(double x)
{//задана функція
    //return sqrt(64.0f-x*x)*log2(x)-sin(2*x);
    return x*x*x-3*x*x+9*x-8;
}

double func_poh_1(double x)
{//перша похідна
    //return (-log2(x)/sqrt(64.0-x*x)) + (sqrt(64.0-x*x)/(x*M_LN2)) - 2*cos(2*x);
    return 3*x*x-6*x+9;
}

double func_poh_2(double x)
{//друга похідна
    //return 4*sin(2*x) -(sqrt(64-x*x)/(x*x*M_LN2)) -
      //      ((x*x)/(sqrt((64.0-x*x)*(64.0-x*x)*(64.0-x*x))*log2(x))) -
        //    (2/(sqrt(64.0-x*x)*M_LN2)) - (1/(sqrt(64.0-x*x)*log2(x)));
    return 6*x-6;
}

int main()
{
    double x, x0, a, b, a1, b1, a2, b2, a3, b3, eps;
    int count = 0;
    do
    {
        printf("Enter a:");
        scanf("%lf", &a);
        printf("Enter b:");
        scanf("%lf", &b);
        printf("Enter eps:");
        scanf("%lf", &eps);

    }while((b<a) || (function(a)*function(b))>0 || (fabs(a-b)<eps));

    a1 = a;b1 = b;a2=a;b2=b;a3=a;b3=b;
    while(fabs(b-a)>eps)
    {
        ++count;
        x = (a+b)/2;
        if((!(function(x)>0))&&(!(function(x)<0)))
            break;
        if(function(a)*function(x)>0)
            a=x;
        else
            b=x;
    }
    x = (a + b)/2;
    printf("Navpil: x = %lf, iteration = %d\n", x, count);

    count = 0;
    if(function(a1)*func_poh_2(a1)>0)
    {
        x0 = a1;
        x = x0 - ((function(x0)*(b1-x0))/(function(b1)-function(x0)));
        while(fabs(x-x0)>eps)
        {
            ++count;
            x0 = x;
            x = x0 - ((function(x0)*(b1-x0))/(function(b1)-function(x0)));
        }
    }

    if(function(b1)*func_poh_2(b1)>0)
    {
        x0 = b1;
        x = x0 - ((function(x0)*(a1-x0))/(function(a1)-function(x0)));
        while(fabs(x-x0)>eps)
        {
            ++count;
            x0 = x;
            x = x0 - ((function(x0)*(a1-x0))/(function(a1)-function(x0)));
        }
    }
    printf("Horda: x = %lf, iteration = %d\n", x, count);

    count = 0;

    x0 = function(b2)*func_poh_2(b2) > 0 ? b2 : a2;
    x = x0 - function(x0)/func_poh_1(x0);

    while(fabs(x-x0)>eps)
    {
        x0 = x;
        x = x0 -function(x0)/func_poh_1(x0);
        ++count;
    }
    printf("Dotychna: x = %lf, iteration = %d\n", x, count);


    count=0;
    x0 = function(b3)*func_poh_2(b3) > 0 ? b3 : a3;
    x = pow(3*x0*x0-9*x0+8, 1./3.);
    while(fabs(x-x0)>eps)
    {
        x0 = x;
        x = pow(3*x0*x0-9*x0+8, 1./3.);
        ++count;
    }
    printf("Iterachia: x = %lf, iteration = %d\n", x, count);
    return 0;
}
