/*
 * Author: Nikita Karatsev
 * Description: Runge-Kutta method (3-order). If you want calculate with y, just comment K1 and uncomment 1 line up with
 * K1, K2, etc.*/
#include <iostream>
#include <cmath>
#include <iomanip>
#include <sys/time.h>
#include <time.h>

#define NS_IN_S  1E9
#define PI 3.14159265358979323846264338

using namespace std;

/*
 * Runge-Kutta method (3-order)
уi+1=уi+(k1+4k2+k3)/6,
k1=hf(xi, yi),
k2=hf(xi+h/2, yi+k1/2),
k3=hf(xi+h, yi+2k2-k1),
xi+1=xi+h.
*/

double F(double, double);

void insertData(double&, double&, double&, int&);

void fillData(double&, double&, double&, double*, double*, int&);

double aitkenProcess(double, double, double);

int main() {
    // Time
    struct timespec start, stop, duration;

    int n;
    double a, b, h, t;

    insertData(a, b, t, n);

    double X[(int) n];
    double K1[(int) n];
    double K2[(int) n];
    double K3[(int) n];
    double Y[(int) n];

    fillData(a, t, h, X, Y, n);


    // Start timer
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    // Calculate
    for (int i = 1; i <= n; i++) {
        X[i] = (double) (a + i * h);
        K1[i] = F(X[i - 1], t);
        //K2[i]=F(X[i-1]+h/2.0, Y[i - 1] + K1[i]/2.0);
        K2[i] = F(X[i - 1] + h / 2.0, t);
        //K3[i]=F(X[i-1]+h, Y[i - 1] + 2*K2[i] - K1[i]);
        K3[i] = F(X[i - 1] + h, t);
        Y[i] = Y[i - 1] + h * (K1[i] + 4 * K2[i] + K3[i]) / 6;
    }
    // End timer
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
    if ((stop.tv_nsec - start.tv_nsec) < 0)
    {
        duration.tv_sec = stop.tv_sec - start.tv_sec - 1;
        duration.tv_nsec = NS_IN_S + stop.tv_nsec - start.tv_nsec;
    }
    else
    {
        duration.tv_sec = stop.tv_sec - start.tv_sec;
        duration.tv_nsec = stop.tv_nsec - start.tv_nsec;
    }
    double result = duration.tv_sec + duration.tv_nsec / NS_IN_S;

    //print results
    for (int i = 0; i <= n; i++) {
        cout    << setw(2) << left << "X["
                << setw(2) << left << i
                << setw(3) << left << "]="
                << setw(6) << left << X[i]
                << setw(2) << left << "Y["
                << setw(2) << left << i
                << setw(3) << left << "]="
                << setw(7) << left << Y[i];
        cout << "\n";
    }
    double aitken = aitkenProcess(X[n], 0.001, t);
    cout << "Aitken process: " << aitken << endl;
    cout << "Difference: " << fixed << Y[n] - aitken << endl;
    cout << "Time: " << fixed << result;
    return 0;
}

double F(double x, double y) {
    // formula
    return (x + 1) * exp(PI * y);
}

void insertData(double& a, double& b, double& t, int& n){
    cout << "Input a: ";
    cin >> a;
    cout << "Input b: ";
    cin >> b;
    cout << "Input t: ";
    cin >> t;
    cout << "Input n: ";
    cin >> n;
}

void fillData(double& a, double& t, double& h, double* X, double* Y, int& n) {
    h = 2 / (double) n;
    X[0] = a;
    Y[0] = 1 / (0.01 + pow((h*t-1), 2));
}

double aitkenProcess(double x, double eps, double t) {
    double x0, x1, x2, d;
    do
    {
        x0=x;
        x1=F(1, t);
        x2=F(1, t);
        d=x0-2*x1+x2;
        if (d!=0)
        {
            x=(x0*x2-x1*x1)/d;
        }
        else return x;
    } while(fabs(x-x0)>eps);
    return x;
}