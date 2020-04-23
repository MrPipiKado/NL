#include <iostream>
#include <cmath>
#include <iomanip>
void fill_L_U(double **A, const double *B, int n)
{
    auto **L = new double* [n];
    for(int i = 0; i<n; ++i)
        L[i] = new double [n];
    auto **U = new double* [n];
    for(int i = 0; i<n; ++i)
        U[i] = new double [n];
    auto *Y = new double [n];
    auto *X = new double [n];

    int i = 0, j = 0, k = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (j < i)
                L[j][i] = 0;
            else
            {
                L[j][i] = A[j][i];
                for (k = 0; k < i; k++)
                {
                    L[j][i] = L[j][i] - L[j][k] * U[k][i];
                }
            }
        }
        for (j = 0; j < n; j++)
        {
            if (j < i)
                U[i][j] = 0;
            else if (j == i)
                U[i][j] = 1;
            else
            {
                U[i][j] = A[i][j] / L[i][i];
                for (k = 0; k < i; k++)
                {
                    U[i][j] = U[i][j] - ((L[i][k] * U[k][j]) / L[i][i]);
                }
            }
        }
    }
    double sum = 0;
    for(i = 0; i<n; i++)
    {
        sum = 0;
        for(j = 0; j<i; j++)
        {
            sum+=L[i][j] * Y[j];
        }
        Y[i] = 1/L[i][i]*(B[i] - sum);
    }

    for(i = n-1; i>=0; i--)
    {
        sum = 0;
        for(j = n-1; j>i; j--)
        {
            sum+=U[i][j] * X[j];
        }
        X[i] = (Y[i] - sum);
    }
    std::cout<< std::endl << "Polinom: " << std::endl;
    for(i = n-1; i>=0; --i)
    {
        std::cout << "(" << X[i] << ")" << "X^" << i ;
        if(i)
            std::cout<<" + ";
    }
    std::cout << std::endl;

    for(i = 0; i<n; ++i)
        delete [] L[i];
    delete [] L;
    for(i = 0; i<n; ++i)
        delete [] U[i];
    delete [] U;
    delete [] X;
    delete [] Y;
}

void aproximation(const double *X, const double *Y, const int t, const int n)
{
    auto A = new double* [n + 1];
    for (int i = 0; i <= n; ++i)
        A[i] = new double[n + 1];
    auto B = new double[n + 1];
    auto Z = new double[n + 1];
    double sum = 0;

    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j <= n; ++j)
        {
            sum = 0;
            for (int q = 0; q < t; ++q)
            {
                sum += std::pow(X[q], i + j);
            }
            A[i][j] = sum;
        }
        sum = 0;
        for (int j = 0; j < t; ++j)
        {
            sum += Y[j] * std::pow(X[j], i);
        }
        B[i] = sum;
    }
    std::cout<< std::endl << "Matrix: " << std::endl;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            std::cout << std::setw(10) << A[i][j];
        }
        std::cout << " ||" << std::setw(10) << B[i] << std::endl;
    }
    fill_L_U(A, B, n);
}

int main()
{
    double X[6] = {0.59, 0.70, 0.81, 0.90, 0.95, 1.00};
    double Y[6] = {2.94, 3.20, 3.38, 3.53, 3.75, 4.06};
    for(int n = 2; n<=4; ++n)
    {
        aproximation(X, Y, 6, n);
    }

    return 0;
}
