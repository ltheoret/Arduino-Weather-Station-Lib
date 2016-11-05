#include "Weather_Lib.h"
#include <math.h>

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

// Convert Temperature from Degrees C to Degrees F
float DegCtoDegF(float Temp)
{
  return ( (9.0 / 5.0) * Temp + 32.0 );
}

// Convert Temperature from Degrees F to Degrees C
float DegFtoDegC(float Temp)
{
  return ( 5.0 / 9.0) * (Temp - 32.0 );
}

// Saturated Vapour Pressure
// Enter Temperature in Degrees C
// Retruns pressure in milli bar.
float SaturatedVapourPressure(float Temp)
{
  float ptemp;
  ptemp = (7.5 * Temp) / (237.3 + Temp);
  return ( 6.11 * pow(10.0, ptemp) );
}

// Dew Point
// Enter Temperature in *C and Relitive Humidity in %
// Return the Dew Point in *C
float DewPoint(float Temp, float RH)
{
  return (243.04 * (log(RH / 100) + ((17.625 * Temp) / (243.04 + Temp))) / (17.625 - log(RH / 100) - ((17.624 * Temp) / (232.04 + Temp))));
}

// Actual Vapour Pressure
// Enter Temperature in *C and Relitive Humidity
// Returns the pressure in milli bar
float ActualVapourPressure(float RH, float Temp)
{
  float DPTemp, ptemp;
  DPTemp = DewPoint(Temp, RH);
  ptemp = (7.5 * DPTemp) / (237.3 + DPTemp);
  return ( 6.11 * pow(10, ptemp) );
}

// Humidex
// Enter Temperature in *C and Dew Point in *C
// Retrn the Humidex in *C
double Humidex(double Temp, double humidity)
{
  double c1 = -42.38, c2 = 2.049, c3 = 10.14, c4 = -0.2248, c5= -6.838e-3, c6=-5.482e-2, c7=1.228e-3, c8=8.528e-4, c9=-1.99e-6  ;
  double T = DegCtoDegF( Temp );
  double R = humidity;

  double A = (( c5 * T) + c2) * T + c1;
  double B = ((c7 * T) + c4) * T + c3;
  double C = ((c9 * T) + c8) * T + c6;

  double rv = (C * R + B) * R + A;
  return DegFtoDegC(rv);

}

