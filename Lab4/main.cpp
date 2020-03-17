#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
void diagon(double A[3][4])
{
    double max, tmp;
    int k;
    for(int j = 0; j<3; ++j)
    {
        max = abs(A[j][j]);
        k = j;
        for(int i = j; i<3; i++)
        {
            if(abs(A[i][j])>max)
            {
                max = abs(A[i][j]);
                k = i;
            }
        }
        for(int i = 0; i<4; ++i)
        {
            tmp = A[k][i];
            A[k][i] = A[j][i];
            A[j][i] = tmp;
        }
    }
    for(int i = 0; i<3; ++i)
    {
        for(int j = 0; j<4; ++j)
        {
            std::cout << std::fixed << std::showpos << std::setw( 4 ) << std::setprecision( 5 )
                      << std::setfill( '0' )<< A[i][j] << "||";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void copy_matrix(double A[3][4], double Ad[3][4])
{
    for(int i = 0; i<3; ++i)
        for(int j = 0; j<4; ++j)
            Ad[i][j] = A[i][j];
}

void make_triangle(double A[3][4])
{
    double tmp;
    for(int i = 0; i<3; ++i)
    {
        for(int j = i+1; j<3; ++j)
        {
            tmp = A[j][i];
            for(int k = 0; k<4; ++k)
            {
                A[j][k] = A[j][k] - (A[i][k]*tmp/A[i][i]);
            }
        }
    }
    for(int i = 0; i<3; ++i)
    {
        for(int j = 0; j<4; ++j)
        {
            std::cout << A[i][j] << "||";
        }
        std::cout << std::endl;
    }
}

void get_x(double A[3][4], double X[3][1])
{
    double sum = 0;
    for(int i = 2; i>-1; --i)
    {
        sum = 0;
        for(int j = 2; j>i; --j)
        {
            sum+=A[i][j] * X[j][0];
        }
        X[i][0] = 1/A[i][i]*(A[i][3] - sum);
    }
    for(int i = 0; i<3; ++i)
    {
        std::cout << X[i][0] << "||";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void fill_L_U(double A[3][4], double L[3][3], double U[3][3])
{
    int i = 0, j = 0, k = 0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (j < i)
                L[j][i] = 0;
            else {
                L[j][i] = A[j][i];
                for (k = 0; k < i; k++) {
                    L[j][i] = L[j][i] - L[j][k] * U[k][i];
                }
            }
        }
        for (j = 0; j < 3; j++) {
            if (j < i)
                U[i][j] = 0;
            else if (j == i)
                U[i][j] = 1;
            else {
                U[i][j] = A[i][j] / L[i][i];
                for (k = 0; k < i; k++) {
                    U[i][j] = U[i][j] - ((L[i][k] * U[k][j]) / L[i][i]);
                }
            }
        }
    }

}
void get_x_y(double A[3][4], double L[3][3], double U[3][3], double X[3][1], double Y[3][1])
{
    double sum = 0;
    for(int i = 0; i<3; i++)
    {
        sum = 0;
        for(int j = 0; j<i; j++)
        {
            sum+=L[i][j] * Y[j][0];
        }
        Y[i][0] = 1/L[i][i]*(A[i][3] - sum);
    }

    for(int i = 2; i>=0; i--)
    {
        sum = 0;
        for(int j = 2; j>i; j--)
        {
            sum+=U[i][j] * X[j][0];
        }
        X[i][0] = (Y[i][0] - sum);
    }
    for(int i = 0; i<3; ++i)
    {
        std::cout << X[i][0] << "||";
        std::cout << std::endl;
    }
}
int main()
{
    double A[3][4] = {{0.65, -0.93, 0.45, -0.72},
                      {1.15, 0.43, -0.72, 1.24},
                      {0.56, -0.18, 1.03, 2.15}};
    double Ad[3][4], X[3][1], L[3][3], U[3][3], Y[3][1];
    copy_matrix(A, Ad);
    diagon(Ad);
    make_triangle(Ad);
    get_x(Ad, X);
    fill_L_U(A, L, U);
    get_x_y(A, L, U, X, Y);
    return 0;
}