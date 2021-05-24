#ifndef DLGPS_H
#define DLGPS_H
/** @file dlgps.h
 *  @brief Constants, structures, function prototypes for gps functions
 */
#include <cmath>

#define round(x) ((x < 0) ? (ceil((x)-0.5)) : (floor((x)+0.5)))
#define SIMGPS 1
#define GPSSERIAL 0
#define GPSDATASZ 256

typedef struct location
{
	double utc;
	double date;
    double latitude;
    double longitude;
    double speed;
    double altitude;
    double course;
} loc_t;

///\cond INTERNAL
// Function Prototypes
extern void DlGpsInit(void);
extern void DlGpsOn(void);
loc_t DlGpsLocation(void);
extern void DlGpsOff(void);
// -------------------------------------------------------------------------
// Internal functions
// -------------------------------------------------------------------------
// convert deg to decimal deg latitude, (N/S), longitude, (W/E)
void DlGpsConvertDegToDec(double *, char, double *, char);
double DlGpsDegDec(double);
///\endcond
#endif
