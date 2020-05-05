#include <iostream>
#include <cmath>
using namespace std;
const double PI = 3.1415926;

double func(double x)
{
    return std::sqrt(x)*std::sin(PI*x/3)*std::sin(PI*x/3);
}

double Left(double a, double b, int n)
{
    double res = 0;
    double tmp = 0;
    double x = a;
    double h = (b - a) / n;
    while (x < b)
    {
        tmp = h * func(x);
        x += h;
        res += tmp;
    }
    return res;
}

double Right(double a, double b, int n)
{
    double res = 0;
    double tmp = 0;
    double x = a;
    double h = (b - a) / n;
    while (x < b)
    {
        tmp = h * func(x + h);
        x += h;
        res += tmp;
    }
    return res;
}

double Mid(double a, double b, int n)
{
    double res = 0;
    double tmp = 0;
    double x = a;
    double h = (b - a) / n;
    while (x < b)
    {
        tmp = h * func((2 * x + h) / 2.0);
        x += h;
        res += tmp;
    }
    return res;
}

double Trap(double a, double b, int n)
{
    double h = (b-a)/n;
    double res = 0;
    double x = a;
    while(x <= b)
    {
        res+=func(x);
        x += h;
    }
    res = (res + (func(a) + func(b)) / 2) * h;
    return res;
}

double Simpson(double a, double b, int n)
{
    if(n%2)++n;
    double h = (b - a)/n;
    double res;
    double x = a+h;
    double tmp = 0;
    res = func(a) + func(b);
    while (x <= b){
        tmp+=func(x);
        x += 2*h;
    }
    res+= 4 * tmp;
    tmp = 0;
    x = a;
    while (x <= b){
        tmp+=func(x);
        x += 2*h;
    }
    res+= 2 * tmp;
    res*=(h / 3);
    return res;
}

double get_integral(double a, double b, int &n, double(*func)(double a, double b, int n))
{
    while (fabs(func(a, b, n) - func(a, b, n * 2)) > 0.001)
    {
        n *= 2;
    }
    return func(a, b, n);
}

int main() {
    double a, b;
    int n = 1;
    cout << "Enter a b: ";
    cin >> a >> b;
    cout << "Left rectangles : "
        << get_integral(a, b, n, Left) << endl;
    cout << "Iterations: " << n << endl << endl;
    n = 1;
    cout << "Right rectangles : "
        << get_integral(a, b, n, Right) << endl;
    cout << "Iterations: " << n << endl << endl;
    n = 1;
    cout << "Middle rectangles : "
        << get_integral(a, b, n, Mid) << endl;
    cout << "Iterations: " << n << endl << endl;
    n = 1;
    cout << "Trap method: "
        << get_integral(a, b, n, Trap) << endl
        << "Iterations: " << n << endl << endl;
    n = 2;
    cout << "Simpson method: ";
    cout << get_integral(a, b, n, Simpson) << endl
        << "Iterations: " << n << endl << endl;
    return 0;
}
