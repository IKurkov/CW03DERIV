/* Kurkov Ivan, 22.B05-MM, 16.03.2024 */
#include "deriv.h"

double Deriv1TableBeginO2( double *value, double step )
{
  return (-3 * value[0] + 4 * value[1] - value[2]) / (2 * step);
}

double Deriv1CenterO2( double *value, double step )
{
  return (value[1] - value[-1]) / (2 * step);
}

double Deriv1TableEndO2( double *value, double step )
{
  return (3 * value[0] - 4 * value[-1] + value[-2]) / (2 * step);
}

double Deriv1TableBeginO4( double *value, double step )
{
  return (-25 * value[0] + 48 * value[1] - 36 * value[2] + 16 * value[3] - 3 * value[4]) / (12 * step);
}

double Deriv1CenterO4( double *value, double step )
{
  return (value[-2] - 8 * value[-1] + 8 * value[1] - value[2]) / (12 * step);
}

double Deriv1TableEndO4( double *value, double step )
{
  return (25 * value[0] - 48 * value[-1] + 36 * value[-2] - 16 * value[-3] + 3 * value[-4]) / (12 * step);
}

double Deriv2TableBeginO2( double *value, double step )
{
  return (2 * value[0] - 5 * value[1] + 4 * value[2] - value[3]) / (step * step);
}

double Deriv2CenterO2( double *value, double step )
{
  return (value[1] - 2 * value[0] + value[-1]) / (step * step);
}

double Deriv2TableEndO2( double *value, double step )
{
  return (2 * value[0] - 5 * value[-1] + 4 * value[-2] - value[-3]) / (step * step);
}