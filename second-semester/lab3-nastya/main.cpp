#include <iostream>
#include <cmath>
#include <sys/time.h>

#define Author Anastasiya_Merz
#define PI 3.14159265358979323846264338

using namespace std;

double F(double, double);

double aitkenProcess(double, double, double);

int main() {
    struct timespec start, stop, duration;
    int n;
    double a, b, h, t;
    cout << "Введите a: ";
    cin >> a;
    cout << "Введите b: ";
    cin >> b;
    cout << "Ввдеите t: ";
    cin >> t;
    cout << "Введите n: ";
    cin >> n;
    double X[(int) n];
    double Y1[(int) n];
    double Y[(int) n];
    h = 2 / (double) n;
    X[0] = a;
    Y[0] = 1 / (0.01 + pow((h*t-1), 2));
    //Y[0] = 1 /(1.01 + pow(t, 2));
    // Вычисление
    for (int i = 1; i <= n; i++) {
        X[i] = (double) (a + i * h);
        Y1[i] = h*F(X[i - 1] + h/2.0, t);
        Y[i] = Y[i - 1] + Y1[i];
    }
    // Вывод результатов
    for (int i = 0; i <= n; i++) {
        cout    << "X["<< i << "]=" << X[i] << " ";
    }
    cout << endl;
    for (int i = 0; i <= n; i++) {
        cout    << "Y[" << i << "]=" << Y[i] << " ";
    }
    cout << endl;
    double aitken = aitkenProcess(X[n], 0.001, t);
    cout << "Результат процесса Эйткена: " << aitken << endl;
    cout << "Разница между методом Эйлера и процессом Эйткена: " << fixed << Y[n] - aitken << endl;
    return 0;
}

double F(double x, double y) {
    // Исходня формула
    return ((x + 1) * exp(-PI * y))/exp(PI*y);
}


double aitkenProcess(double x, double eps, double t) {
    double x0, x1, x2, d;
    do
    {
        x0=x;
        x1=F(x, t);
        x2=F(x, t);
        d=x0-2*x1+x2;
        if (d!=0)
        {
            x=(x0*x2-x1*x1)/d;
        }
        else return x;
    } while(fabs(x-x0)>eps);
    return x;
}