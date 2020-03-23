#include <iostream>
#include <iomanip>
#include <cmath>
double max(double X[4][1], double X_PREV[4][1])
{
    double max = fabs((X[0][0] - X_PREV[0][0]));
    for(int i = 1; i<4; ++i)
    {
        if(fabs((X[i][0] - X_PREV[i][0]))>max)
            max = fabs((X[i][0] - X_PREV[i][0]));
    }
    return max;
}

void Jacobi(double A[4][4], double B[4][1])
{
    double Alpha[4][4], Beta[4][1], X[4][1], X_PREV[4][1], tmp1, tmp2;
    int count = 1;
    for(int i = 0; i<4; ++i)
    {
        for(int j = 0; j<4;++j)
        {
            Alpha[i][j] = - A[i][j]/A[i][i];
        }
        Beta[i][0] = B[i][0]/A[i][i];
        X[i][0] = X_PREV[i][0] = B[i][0];
    }
    std::cout << "Alpha:" << std::endl;
    for(int i = 0; i<4; ++i)
    {
        Alpha[i][i] = 0;
        for(int j = 0; j<4;++j)
        {
            std::cout << std::fixed << std::showpos << std::setw( 4 ) << std::setprecision( 5 )
                      << std::setfill( '0' ) << Alpha[i][j] << "||";
        }
        std::cout << std::endl;
    }
    std::cout << "Beta:" << std::endl;
    for(int i = 0; i<4; ++i)
    {
        std::cout << Beta[i][0] << std::endl;
    }
    do
    {
        for(int i = 0; i < 4; ++i)
            X_PREV[i][0] = X[i][0];
        for(int i = 0; i < 4; ++i)
        {
            tmp1 = tmp2 = 0;
            for(int j = 0; j<i; ++j)
            {
                tmp1 += Alpha[i][j] * X_PREV[j][0];
            }
            for(int j = i+1; j<4 ; ++j)
            {
                tmp2 += Alpha[i][j] * X_PREV[j][0];
            }
            X[i][0] = Beta[i][0] + tmp1 + tmp2;
        }
        std::cout<< "Iteration: " << count <<
                    " x1=" << X[0][0] <<
                    " x2=" << X[1][0] <<
                    " x3=" << X[2][0] <<
                    " x4=" << X[3][0] << std::endl;
        ++count;
    }while(max(X, X_PREV)>0.001);
}

void Zeidal(double A[4][4], double B[4][1])
{
    double Alpha[4][4], Beta[4][1], X[4][1], X_PREV[4][1], tmp1, tmp2;
    int count = 1;
    for(int i = 0; i<4; ++i)
    {
        for(int j = 0; j<4;++j)
        {
            Alpha[i][j] = - A[i][j]/A[i][i];
        }
        Beta[i][0] = B[i][0]/A[i][i];
        X[i][0] = X_PREV[i][0] = B[i][0];
    }
    std::cout << "Alpha:" << std::endl;
    for(int i = 0; i<4; ++i)
    {
        Alpha[i][i] = 0;
        for(int j = 0; j<4;++j)
        {
            std::cout << std::fixed << std::showpos << std::setw( 4 ) << std::setprecision( 5 )
                      << std::setfill( '0' ) << Alpha[i][j] << "||";
        }
        std::cout << std::endl;
    }
    std::cout << "Beta:" << std::endl;
    for(int i = 0; i<4; ++i)
    {
        std::cout << Beta[i][0] << std::endl;
    }
    do
    {
        for(int i = 0; i < 4; ++i)
            X_PREV[i][0] = X[i][0];
        for(int i = 0; i < 4; ++i)
        {
            tmp1 = tmp2 = 0;
            for(int j = 0; j<i; ++j)
            {
                tmp1 += Alpha[i][j] * X[j][0];
            }
            for(int j = i+1; j<4 ; ++j)
            {
                tmp2 += Alpha[i][j] * X_PREV[j][0];
            }
            X[i][0] = Beta[i][0] + tmp1 + tmp2;
        }
        std::cout<< "Iteration: " << count <<
                 " x1=" << X[0][0] <<
                 " x2=" << X[1][0] <<
                 " x3=" << X[2][0] <<
                 " x4=" << X[3][0] << std::endl;
        ++count;
    }while(max(X, X_PREV)>0.001);
}

int main() {
    double A[4][4]={{0.23, -0.04, 0.21, -0.18},
                    {0.45, -0.23, 0.06,  0.0 },
                    {0.26,  0.0 , 0.34, -0.11},
                    {0.05, -0.26, 0.34, -1.12}};
    double B[4][1]={{-1.24},
                    { 0.88},
                    {-0.62},
                    { 1.17}};
    Jacobi(A, B);
    Zeidal(A, B);
    return 0;
}
