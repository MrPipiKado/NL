#include <iostream>

const int X = 0, Y = 1, Z = 2;

double get_determinant(double matrix[3][3])
{
    return matrix[0][0]*matrix[1][1]*matrix[2][2]+
           matrix[0][1]*matrix[1][2]*matrix[2][0]+
           matrix[1][0]*matrix[2][1]*matrix[0][2]-
           matrix[0][2]*matrix[1][1]*matrix[2][0]-
           matrix[1][0]*matrix[0][1]*matrix[2][2]-
           matrix[0][0]*matrix[2][1]*matrix[1][2];
}

void pass(double matrix[3][3], double matrixi[3][3], double B[3][1], int l)
{
    for(int i = 0; i<3; ++i)
        for(int j = 0; j<3;  ++j)
        {
            matrixi[i][j] = matrix[i][j];
        }
    for(int i = 0; i<3; ++i)
        matrixi[i][l] = B[i][0];
    if(l==0)std::cout << "X1 Matrix\n";
    if(l==1)std::cout << "X2 Matrix\n";
    if(l==2)std::cout << "X3 Matrix\n";
    for (int i = 0; i<3; ++i)
    {
        for(int j = 0; j<3; ++j)
            std::cout << matrix[i][j] << " || ";
        std::cout << std::endl;
    }
}

double Kramer(double det_i, double det)
{
    return det_i/det;
}



void crate_reversed(double matrix[3][3], double matrix_rev[3][3])
{
    double tmp[4], minor, tmmp;
    double det = get_determinant(matrix);
    int k;
    for(int i = 0; i<3; ++i)
        for(int j = 0; j<3; ++j)
        {
            k = 0;
            for(int n = 0; n<3; ++n)
            {
                for (int m = 0; m < 3; ++m)
                {
                    if (n == i || m == j)
                    {
                        continue;
                    }
                    tmp[k] = matrix[n][m];
                    ++k;
                }
            }
            minor = tmp[0]*tmp[3] - tmp[1]*tmp[2];
            if((i + j)%2)
                minor = -1. * minor;
            matrix_rev[i][j] = minor/det;
        }

    for(int i = 0; i<3; ++i)
        for(int j = 0; j<3; ++j)
            if(i<j)
            {
                tmmp = matrix_rev[i][j];
                matrix_rev[i][j] = matrix_rev[j][i];
                matrix_rev[j][i] = tmmp;
            }
}

double get_x(double matrix[3][3], double B[3][1], int l)
{
    double res = 0;
    for(int i = 0; i<3; ++i)
        res += matrix[l][i]*B[i][0];
    return res;
}

int main()
{
    double A[3][3] = {{0.65, -0.93, 0.45},
                      {1.15, 0.43, -0.72},
                      {0.56, -0.18, 1.03}};
    double B[3][1] = {{-0.72},
                      {1.24},
                      {2.15}};
    double Ax[3][3], Ay[3][3], Az[3][3], A_rev[3][3];

    std::cout << "Source matrix" << std::endl;

    for (int i = 0; i<3; ++i)
    {
        for(int j = 0; j<3; ++j)
            std::cout << A[i][j] << " || ";
        std::cout << B[i][0] <<std::endl;
    }
    std::cout << "det = " << get_determinant(A) << std::endl;
    std::cout << std::endl;
    pass(A, Ax, B, X);
    std::cout << "det = " << get_determinant(Ax) << std::endl;
    std::cout << std::endl;
    pass(A, Ay, B, Y);
    std::cout << "det = " << get_determinant(Ay) << std::endl;
    std::cout << std::endl;
    pass(A, Az, B, Z);
    std::cout << "det = " << get_determinant(Az) << std::endl;
    std::cout << std::endl;

    double x1 = Kramer(get_determinant(Ax), get_determinant(A));
    double x2 = Kramer(get_determinant(Ay), get_determinant(A));
    double x3 = Kramer(get_determinant(Az), get_determinant(A));
    std::cout << "Cramar's method" << std::endl;
    std::cout << "x1 = " << x1 << std::endl;
    std::cout << "x2 = " << x2 << std::endl;
    std::cout << "x3 = " << x3 << std::endl;
    std::cout << std::endl;

    crate_reversed(A, A_rev);

    std::cout << "Reversed matrix" << std::endl;

    for (int i = 0; i<3; ++i)
    {
        for(int j = 0; j<3; ++j)
            std::cout << A_rev[i][j] << " || ";
        std::cout<<std::endl;
    }
    std::cout << std::endl;
    x1 = get_x(A_rev, B, X);
    x2 = get_x(A_rev, B, Y);
    x3 = get_x(A_rev, B, Z);

    std::cout << "Matrix method" << std::endl;
    std::cout << "x1 = " << x1 << std::endl;
    std::cout << "x2 = " << x2 << std::endl;
    std::cout << "x3 = " << x3 << std::endl;

    return 0;
}
