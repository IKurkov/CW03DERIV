/* Kurkov Ivan, 22.B05-MM, 16.03.2024 */

#ifndef DERIV_H
#define DERIV_H

double Deriv1TableBeginO2( double *value, double step );
double Deriv1CenterO2( double *value, double step );
double Deriv1TableEndO2( double *value, double step );

double Deriv1TableBeginO4( double *value, double step );
double Deriv1CenterO4( double *value, double step );
double Deriv1TableEndO4( double *value, double step );

double Deriv2TableBeginO2( double *value, double step );
double Deriv2CenterO2( double *value, double step );
double Deriv2TableEndO2( double *value, double step );

#endif // !DERIV_H