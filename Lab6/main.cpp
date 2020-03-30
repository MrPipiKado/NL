#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

void transpone(double A[5][3], double AT[3][5])
{
    std::cout << std::fixed << std::showpos << std::setw( 4 ) << std::setprecision( 5 )
              << std::setfill( '0' ) << "Matrix:" << std::endl;
    for(int i = 0; i<5; ++i)
    {
        for(int j = 0; j<3; ++j)
        {
            AT[j][i] = A[i][j];
            std::cout << A[i][j] << "||";
        }
        std::cout << std::endl;
    }
    std::cout << "TMatrix:" << std::endl;
    for(int i = 0; i<3; ++i)
    {
        for(int j = 0; j<5; ++j)
        {
            std::cout << AT[i][j] << "||";
        }
        std::cout << std::endl;
    }
}
void get_normal(double A[5][3], double AT[3][5], double N[3][3])
{
    std::cout << "NMatrix:" << std::endl;
    double tmp;
    for(int i = 0; i<3; ++i)
    {
        for(int j = 0; j<3; ++j)
        {
            tmp = 0;
            for (int k = 0; k<5;++k)
                tmp += AT[i][k]*A[k][j];
            N[i][j] = tmp;
            std::cout << N[i][j] << "||" ;
        }
        std::cout << std::endl;
    }
}
void get_C(double AT[3][5], double B[5][1], double C[3][1])
{
    std::cout << std::endl;
    double tmp;
    for(int i = 0; i<3; ++i)
    {
        for(int j = 0; j<1; ++j)
        {
            tmp = 0;
            for (int k = 0; k<5;++k)
                tmp += AT[i][k]*B[k][j];
            C[i][j] = tmp;
            std::cout << C[i][j] << "||" ;
        }
        std::cout << std::endl;
    }
}
void get_L_LT(double N[3][3], double L[3][3], double LT[3][3])
{
    L[0][0] = LT[0][0] = sqrt(N[0][0]);
    L[1][0] = LT[0][1] = N[1][0]/L[0][0];
    L[2][0] = LT[0][2] = N[2][0]/L[0][0];
    L[1][1] = LT[1][1] = sqrt(N[1][1]-L[1][0]*L[1][0]);
    L[2][1] = LT[1][2] = (N[2][1]-L[2][0]*L[1][0])/L[1][1];
    L[2][2] = LT[2][2] = sqrt(N[2][2]-L[2][0]*L[2][0]-L[2][1]*L[2][1]);
    std::cout << "LMatrix:"<<std::endl;
    for(int i = 0; i<3; ++i)
    {
        for(int j = 0; j<3; ++j)
        {
            std::cout << L[i][j] << "||" ;
        }
        std::cout << std::endl;
    }
    std::cout << "LTMatrix:"<<std::endl;
    for(int i = 0; i<3; ++i)
    {
        for(int j = 0; j<3; ++j)
        {
            std::cout << LT[i][j] << "||" ;
        }
        std::cout << std::endl;
    }
}
void get_x_y(double A[3][3], double B[3][1], double X[3][1])
{
    double L[3][3], U[3][3], Y[3][1];
    int i = 0, j = 0, k = 0;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (j < i)
                L[j][i] = 0;
            else {
                L[j][i] = A[j][i];
                for (k = 0; k < i; k++)
                {
                    L[j][i] = L[j][i] - L[j][k] * U[k][i];
                }
            }
        }
        for (j = 0; j < 3; j++)
        {
            if (j < i)
                U[i][j] = 0;
            else if (j == i)
                U[i][j] = 1;
            else {
                U[i][j] = A[i][j] / L[i][i];
                for (k = 0; k < i; k++)
                {
                    U[i][j] = U[i][j] - ((L[i][k] * U[k][j]) / L[i][i]);
                }
            }
        }
    }
    double sum = 0;
    for(int i = 0; i<3; i++)
    {
        sum = 0;
        for(int j = 0; j<i; j++)
        {
            sum+= L[i][j] * Y[j][0];
        }
        Y[i][0] = 1 / L[i][i] * (B[i][0] - sum);
    }

    for(int i = 2; i>=0; i--)
    {
        sum = 0;
        for(int j = 2; j>i; j--)
        {
            sum+= U[i][j] * X[j][0];
        }
        X[i][0] = (Y[i][0] - sum);
    }
}
int main()
{
    double A[5][3] = {{ 3,  1, -1},
                      {-5,  1,  3},
                      { 2,  0,  1},
                      { 1, -5,  3},
                      { 2, -4, -1}};
    double B[5][1] = { 2,
                      -10,
                       1,
                       7,
                       11};
    double AT[3][5], N[3][3], C[3][1],
           L[3][3] = {0}, LT[3][3] = {0},
           Y[3][1], X[3][1];
    transpone(A, AT);
    get_normal(A, AT, N);
    get_C(AT, B, C);
    get_L_LT(N, L, LT);
    get_x_y(L, B, Y);
    get_x_y(LT, Y, X);
    for(int i = 0; i<3; ++i)
        std::cout << "X" << i+1 << " = " << X[i][0] << std::endl;
    return 0;
}
