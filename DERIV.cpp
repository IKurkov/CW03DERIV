/* Kurkov Ivan, 22.B05-MM, 16.03.2024 */
#include "deriv.h"

double Deriv1O2( const double *vals, size_t size, size_t arg, double step )
{
  if (arg == 0)
    return (-3 * vals[arg] + 4 * vals[arg + 1] - vals[arg + 2]) / (2 * step);
  if (arg == size - 1)
    return (3 * vals[arg] - 4 * vals[arg - 1] + vals[arg - 2]) / (2 * step);
  return (vals[arg + 1] - vals[arg - 1]) / (2 * step);
}

double Deriv1O4( const double *vals, size_t size, size_t arg, double step )
{
  if (arg == 0)
    return (-25 * vals[arg] + 48 * vals[arg + 1] - 36 * vals[arg + 2] + 16 * vals[arg + 3] - 3 * vals[arg + 4]) / (12 * step);
  if (arg == 1)
    return (-3 * vals[arg - 1] - 10 * vals[arg] + 18 * vals[arg + 1] - 6 * vals[arg + 2] + vals[arg + 3]) / (12 * step);
  if (arg == size - 2)
    return (-vals[arg - 3] + 6 * vals[arg - 2] - 18 * vals[arg - 1] + 10 * vals[arg] + 3 * vals[arg + 1]) / (12 * step);
  if (arg == size - 1)
    return (25 * vals[arg] - 48 * vals[arg - 1] + 36 * vals[arg - 2] - 16 * vals[arg - 3] + 3 * vals[arg - 4]) / (12 * step);
  return (vals[arg - 2] - 8 * vals[arg - 1] + 8 * vals[arg + 1] - vals[arg + 2]) / (12 * step);
}

double Deriv2O2( const double *vals, size_t size, size_t arg, double step )
{
  if (arg == 0)
    return (2 * vals[arg] - 5 * vals[arg + 1] + 4 * vals[arg + 2] - vals[arg + 3]) / (step * step);
  if (arg == size - 1)
    return (2 * vals[arg] - 5 * vals[arg - 1] + 4 * vals[arg - 2] - vals[arg - 3]) / (step * step);
  return (vals[arg + 1] - 2 * vals[arg] + vals[arg - 1]) / (step * step);
}