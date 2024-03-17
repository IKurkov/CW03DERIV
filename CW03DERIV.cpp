/* Kurkov Ivan, 22.B05-MM, 16.03.2024 */
#include <cmath>
#include <conio.h>
#include <iostream>

#include "deriv.h"
#include "fort.hpp"

double Exp7( double x )
{
  return exp(4.5 * x);
}

double Exp7Deriv( double x )
{
  return 4.5 * exp(4.5 * x);
}

double Exp7Deriv2( double x )
{
  return 4.5 * 4.5 * exp(4.5 * x);
}

double FromTask1( double x )
{
  return exp(-x) - x * x / 2;
}

double FromTask1Deriv( double x )
{
  return -exp(-x) - x;
}

double FromTask1Deriv2( double x )
{
  return exp(-x) - 1;
}

std::string Exp7Str = "e^{4.5x}", FromTask1Str = "e^{-x} - x^2/2";

int main( void )
{
  bool run = true;
  double a, h, *args = nullptr, *vals = nullptr, *derivO2 = nullptr, *derivO4 = nullptr, *dderiv = nullptr;
  int key;
  size_t n = 0;

  double (*f)(double) = nullptr;
  double (*df_dx)(double) = nullptr;
  double (*d2f_dx2)(double) = nullptr;

  fort::char_table output_table;

  while (run)
  {
    std::cout << "Numeric differentiation menu [variant #7]:\n"
      "0 - exit\n"
      "1 - Find derivative\n"
      "2 - Make Runge-Romberg's refinement\n"
      "3 - Change function\n";
    switch (_getch())
    {
    case '0':
      delete[] args;
      delete[] vals;
      delete[] derivO2;
      delete[] derivO4;
      delete[] dderiv;
      run = false;
      break;
    case '1':
      if (n != 0)
      {
        delete[] args;
        delete[] vals;
        delete[] derivO2;
        delete[] derivO4;
        delete[] dderiv;
      }
      do
      {
        std::cout << "Choose function to differentiation:\n"
          << "1 - " << FromTask1Str << '\n'
          << "2 - " << Exp7Str << '\n';
        key = _getch();
        if (key == '1')
          f = FromTask1, df_dx = FromTask1Deriv, d2f_dx2 = FromTask1Deriv2;
        else if (key == '2')
          f = Exp7, df_dx = Exp7Deriv, d2f_dx2 = Exp7Deriv2;
      } while (key != '1' && key != '2');
      do
      {
        std::cout << "Input number of steps >= 5: ";
        std::cin >> n;
      } while (n < 5);
      std::cout << "Input starting point: ";
      std::cin >> a;
      do
      {
        std::cout << "Input step size: ";
        std::cin >> h;
      } while (h <= 0);

      args = new double[n];
      vals = new double[n];
      derivO2 = new double[n];
      derivO4 = new double[n];
      dderiv = new double[n];
      vals[0] = f(args[0] = a);
      for (size_t i = 1; i < n; i++)
      {
        args[i] = args[i - 1] + h;
        vals[i] = f(args[i]);
      }

      output_table << fort::header << "x" << "f(x)"
        << "f'_nd(x), O(h^2)" << "|f'(x) - f'_nd(x)|"
        << "f'_nd(x), O(h^4)" << "|f'(x) - f'_nd(x)|"
        << "f''_nd(x), O(h^2)" << "|f''(x) - f''_nd(x)|" << fort::endr;
      for (size_t i = 0; i < n; i++)
      {
        if (i == 0)
        {
          derivO2[i] = Deriv1TableBeginO2(vals + i, h);
          derivO4[i] = Deriv1TableBeginO4(vals + i, h);
          dderiv[i] = Deriv2TableBeginO2(vals + i, h);
        }
        else if (i == 1)
        {
          derivO2[i] = Deriv1CenterO2(vals + i, h);
          derivO4[i] = Deriv1TableBeginO4(vals + i, h);
          dderiv[i] = Deriv2CenterO2(vals + i, h);
        }
        else if (i == n - 2)
        {
          derivO2[i] = Deriv1CenterO2(vals + i, h);
          derivO4[i] = Deriv1TableEndO4(vals + i, h);
          dderiv[i] = Deriv2CenterO2(vals + i, h);
        }
        else if (i == n - 1)
        {
          derivO2[i] = Deriv1TableEndO2(vals + i, h);
          derivO4[i] = Deriv1TableEndO4(vals + i, h);
          dderiv[i] = Deriv2TableEndO2(vals + i, h);
        }
        else
        {
          derivO2[i] = Deriv1CenterO2(vals + i, h);
          derivO4[i] = Deriv1CenterO4(vals + i, h);
          dderiv[i] = Deriv2CenterO2(vals + i, h);
        }
        output_table << args[i] << vals[i]
          << derivO2[i] << fabs(df_dx(args[i]) - derivO2[i])
          << derivO4[i] << fabs(df_dx(args[i]) - derivO4[i])
          << dderiv[i] << fabs(d2f_dx2(args[i]) - dderiv[i]) << fort::endr;
      }
      std::cout << output_table.to_string() << '\n';
      break;
    default:
      std::cout << "[Error]: Incorrect choice!\n";
      break;
    }
  }
  return 0;
}