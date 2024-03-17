/* Kurkov Ivan, 22.B05-MM, 16.03.2024 */

#ifndef DERIV_H
#define DERIV_H

double Deriv1O2( const double *vals, size_t size, size_t arg, double step );
double Deriv1O4( const double *vals, size_t size, size_t arg, double step );
double Deriv2O2( const double *vals, size_t size, size_t arg, double step );

#endif // !DERIV_H