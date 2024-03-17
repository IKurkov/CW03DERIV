/* Kurkov Ivan, 22.B05-MM, 16.03.2024 */
#include <cmath>
#include <conio.h>
#include <iostream>

#include "deriv.h"
#include "fort.hpp"

enum class ORDER
{
  FUNC,
  FIRST_DERIV,
  SECOND_DERIV
};

double Exp7( double x, ORDER o )
{
  switch (o)
  {
  case ORDER::FUNC:
    return exp(4.5 * x);
  case ORDER::FIRST_DERIV:
    return 4.5 * exp(4.5 * x);
  case ORDER::SECOND_DERIV:
    return 4.5 * 4.5 * exp(4.5 * x);
  default:
    return exp(4.5 * x);
  }
}

double FromTask1( double x, ORDER o )
{
  switch (o)
  {
  case ORDER::FUNC:
    return exp(-x) - x * x / 2;
  case ORDER::FIRST_DERIV:
    return -exp(-x) - x;
  case ORDER::SECOND_DERIV:
    return exp(-x) - 1;
  default:
    return exp(-x) - x * x / 2;
  }
}

std::string Exp7Str = "e^{4.5x}", FromTask1Str = "e^{-x} - x^2/2";

int main( void )
{
  bool run = true;
  double a, h, d1O4, d2O2, *args = nullptr, *vals = nullptr, *d1O2_vals = nullptr;
  int key;
  size_t n = 0;

  double (*f)(double, ORDER) = nullptr;

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
      delete[] d1O2_vals;
      run = false;
      break;
    case '1':
      {
        fort::char_table output_table;

        if (n != 0)
        {
          delete[] args;
          delete[] vals;
          delete[] d1O2_vals;
        }
        do
        {
          std::cout << "Choose function to differentiation:\n"
            << "1 - " << FromTask1Str << '\n'
            << "2 - " << Exp7Str << '\n';
          key = _getch();
          if (key == '1')
            f = FromTask1;
          else if (key == '2')
            f = Exp7;
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
        d1O2_vals = new double[n];
        vals[0] = f(args[0] = a, ORDER::FUNC);
        for (size_t i = 1; i < n; i++)
        {
          args[i] = args[i - 1] + h;
          vals[i] = f(args[i], ORDER::FUNC);
        }

        output_table << fort::header << "x" << "f(x)"
          << "f'_nd(x), O(h^2)" << "|f'(x) - f'_nd(x)|"
          << "f'_nd(x), O(h^4)" << "|f'(x) - f'_nd(x)|"
          << "f\"_nd(x), O(h^2)" << "|f\"(x) - f\"_nd(x)|" << fort::endr;

        for (size_t i = 0; i < n; i++)
        {
          d1O2_vals[i] = Deriv1O2(vals, n, i, h);
          d1O4 = Deriv1O4(vals, n, i, h);
          d2O2 = Deriv2O2(vals, n, i, h);
          output_table << args[i] << vals[i]
            << d1O2_vals[i] << fabs(f(args[i], ORDER::FIRST_DERIV) - d1O2_vals[i])
            << d1O4 << fabs(f(args[i], ORDER::FIRST_DERIV) - d1O4)
            << d2O2 << fabs(f(args[i], ORDER::SECOND_DERIV) - d2O2) << fort::endr;
        }
        std::cout << output_table.to_string() << '\n';
      }
      break;
    default:
      std::cout << "[Error]: Incorrect choice!\n";
      break;
    }
  }
  return 0;
}