#include <iostream>
#include <cmath>

double fi_y(double x)
{
    return sin(x+1) -1.2;
}

double fi_x(double  y)
{
    return (2-cos(y))/2;
}

double f1_x_y(double x, double y)
{
    return sin(x+1) - y - 1.2;
}

double f1_po_x(double x)
{
    return cos(x+1);
}

double f1_po_y(double y)
{
    return -1;
}

double f2_x_y(double x, double y)
{
    return 2*x + cos(y) - 2;
}

double f2_po_x(double x)
{
    return 2;
}

double f2_po_y(double y)
{
    return -2*sin(y);
}

void iteration()
{
    int count = 1;
    double x = -5, y = -5, x0 = 0., y0 =0.;
    do
    {
        x0 = x;
        y0 = y;
        x = fi_x(y0);
        y = fi_y(x0);
        std::cout<<"iteration"<<count<<" x = "<<x<<" y = "<<y<<std::endl;
        ++count;
    }while((std::abs(x-x0)+std::abs(y-y0))>0.001);

}

void nuiton()
{
    int count = 1;
    double x = 0., y = 0., x0 = 0., y0 =0., det, dx, dy;
    do
    {
        x0 = x;
        y0 = y;
        det = (f1_po_x(x)*f2_po_y(y) - f1_po_y(y)*f2_po_x(x));
        dx = -(f1_x_y(x, y)*f2_po_y(y) - f1_po_y(y)*f2_x_y(x, y))/det;
        dy = -(f1_po_x(x)*f2_x_y(x, y) - f1_x_y(x, y)*f2_po_x(x))/det;
        x = x0 + dx;
        y = y0 + dy;
        std::cout<<"iteration"<<count<<"x = "<<x<<" y = "<<y<<std::endl;
        ++count;
    }while((std::abs(x-x0)+std::abs(y-y0))>0.001);
}

int main()
{
    std::cout<<"Iteration method"<<std::endl;
    iteration();
    std::cout<<"Neuton method"<<std::endl;
    nuiton();
    return 0;

}
