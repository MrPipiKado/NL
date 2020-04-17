#include <iostream>
#include <cmath>
#include <iomanip>
unsigned int factorial(unsigned int n)
{
    if (n == 0 || n==1)
        return 1;
    return n * factorial(n - 1);
}

void Lagranch(const double X[10], const double Y[10], const double X0)
{
    double tmp = 1, res = 0;
    for(int i = 0; i<10; ++i)
    {
        tmp = 1;
        for(int j = 0; j<10; ++j)
        {
            if(j==i)continue;
            tmp*=(X0 -X[j])/(X[i]-X[j]);
        }
        res+=tmp*Y[i];
    }
    std::cout<<"Lagranch f(x0)= "<<res<<std::endl;
}

void Neuthon(const double X[10], const double Y[10], const double X0)
{
    double DMatrix[10][10]={0};
    double h = X[1] - X[0];
    double res = Y[0];
    double tmp_1, tmp_2;
    for(int i = 0; i<10; ++i)
    {
        DMatrix[i][0] = Y[i];
    }
    for(int j = 1; j<10 ;++j)
    {
        for(int i = 0; i<10-j; ++i)
        {
            DMatrix[i][j] = DMatrix[i+1][j-1]-DMatrix[i][j-1];
        }
    }
    for(int j = 1; j<10; ++j)
    {
        tmp_1 = DMatrix[0][j];
        tmp_2 = factorial(j);
        for(int i = 0; i<j; i++)
        {
            tmp_1*=X0 - X[i];
            tmp_2*=h;
        }
        res+=tmp_1/tmp_2;
    }
    std::cout<<"Neuthon f(x0)= "<<res<<std::endl;
}

int main()
{
    double X[10] = {1.415, 1.420, 1.425, 1.430, 1.435, 1.440, 1.445, 1.450, 1.455, 1.460};
    double Y[10] = {0.880, 0.889, 0.890, 0.891, 0.892, 0.893, 0.894, 0.895, 0.896, 0.897};
    double X0 = 1.461;

    std::cout << std::fixed << std::showpos << std::setw( 2 ) << std::setprecision( 3 )
              << std::setfill( '0' );
    std::cout<<"X: ";
    for(double i : X)
    {
        std::cout<<i<<" ";
    }
    std::cout<<"\nY: ";
    for(double i : Y)
    {
        std::cout<<i<<" ";
    }
    std::cout<<std::endl;
    Lagranch(X, Y, X0);
    Neuthon(X, Y, X0);
    return 0;
}
