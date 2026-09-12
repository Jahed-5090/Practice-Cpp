#include <bits/stdc++.h>
using namespace std;

int n;
const double E = 1e-3;

double f(double x, vector<double> &coff)
{
     double res = 0.0; 
     for (int i = n; i >= 0; i--) 
     {
          res += (coff[i] * pow(x, i));
     }
     return res;
}

double Secant(double x0, double x1, vector<double> &coff, int &itr)
{
     itr = 0;
     double x_curr = x1;
     double x_prev = x0;

     // Changed to || 
     while (fabs(x_curr - x_prev) >= E || fabs(f(x_curr, coff)) >= E)
     {
          double f_curr = f(x_curr, coff);
          double f_prev = f(x_prev, coff);

          if (fabs(f_curr - f_prev) <= 1e-12)
               break;

          // Reused calculated f_curr and f_prev
          double x_next = x_curr - f_curr * ((x_curr - x_prev) / (f_curr - f_prev));

          x_prev = x_curr;
          x_curr = x_next;
          itr++; // Added iteration increment
     }

     return x_curr; // Returned the actual calculated root
}

int main()
{
     cout << "Enter the no. of degree: ";
     cin >> n;

     vector<double> coff(n + 1); // Moved below cin >> n

     cout << "Enter the coefficients(an..a0) : ";

     for (int i = n; i >= 0; i--) // Started from n
     {
          cin >> coff[i];
     }

     double xmax = 0.0;

     // Fixed xmax formula (fabs, divided by coff[n], added 1)
     for (int i = 0; i < n; i++) 
     {
          xmax = max(xmax, fabs(coff[i] / coff[n])); 
     }
     xmax = 1.0 + xmax;

     double hi = fabs(xmax);
     double a = -fabs(xmax);

     double ss = 0.45;
     int rootCount = 0;
     bool found = false;

     while (a < hi)
     {
          double b = a + ss;
          if (b > hi) b = hi; // Prevent overshooting bounds

          if (f(a, coff) * f(b, coff) < 0.0)
          {
               found = true;
               rootCount++;
               int itr = 0;
               double root = Secant(a, b, coff, itr);
               cout << "Root " << rootCount << ": " << fixed << setprecision(5) << root << endl;
               cout << "Search Interval for root: [" << a << "," << b << "]" << endl;
               cout << "Total Iteration: " << itr << endl << endl;
          }
          a = b;
     }

     if (!found)
     {
          int itr = 0;
          // Provided distinct guesses so it doesn't immediately divide by 0
          double x0 = 0.0;
          double x1 = 1.0; 

          double root = Secant(x0, x1, coff, itr);
          cout << "Default Root : " << root << endl;
     }

     return 0;
}