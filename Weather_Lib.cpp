#include "Weather_Lib.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

// Convert Temperature from Degrees C to Degrees F
float DegCtoDegF(float Temp)
{
        return( (9.0 / 5.0) * Temp + 32.0 );
}

// Convert Temperature from Degrees F to Degrees C
float DegFtoDegC(float Temp)
{
    return( 5.0 / 9.0) * (Temp - 32.0 );
}

// Saturated Vapour Pressure
// Enter Temperature in Degrees C
// Retruns pressure in milli bar.
float SaturatedVapourPressure(float Temp)
{
    float ptemp;
    ptemp = (7.5*Temp)/(237.3+Temp);
    return( 6.11 * pow(10.0, ptemp) );
}

// Dew Point
// Enter Temperature in *C and Relitive Humidity in %
// Return the Dew Point in *C
float DewPoint(float Temp, float RH)
{
    return(243.04*(log(RH/100)+((17.625*Temp)/(243.04+Temp)))/(17.625-log(RH/100)-((17.624*Temp)/(232.04+Temp))));
}

// Actual Vapour Pressure
// Enter Temperature in *C and Relitive Humidity
// Returns the pressure in milli bar
float ActualVapourPressure(float RH, float Temp)
{
    float DPTemp, ptemp;
    DPTemp = DewPoint(Temp, RH);
    ptemp = (7.5*DPTemp)/(237.3+DPTemp);
    return( 6.11 * pow(10, ptemp) );
}

