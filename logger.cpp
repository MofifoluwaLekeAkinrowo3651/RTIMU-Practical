/** @file logger.cpp
 *  @brief logger functions
 */

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cinttypes>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "logger.h"
#include "sensehat.h"

//Global Objects
SenseHat Sh;

/** @brief Data Logger Initializes data logger
 *  @author Dieko Akinrowo
 *  @date 17MAY21
 *  @param None void
 *  @return int status
 */
 int DlInitialization(void)
 {
    fprintf(stdout,"\nDieko Akinrowo's CENG252 Vehicle Data Logger\n");
    fprintf(stdout,"Data Logger Initialization\n");
    return 1;
 }

 /** @brief Data Logger Get Serial
  *  @author Dieko Akinrowo
  *  @date 17MAY21
  *  @param None void
  *  @return uint64_t serial number
  */
 uint64_t DlGetSerial(void)
 {
	static uint64_t serial = 0;
	FILE * fp;
	char buf[SYSINFOBUFSZ];
	char searchstring[] = SEARCHSTR;

	fp = fopen ("/proc/cpuinfo", "r");
	if (fp != NULL)
	{
		while (fgets(buf, sizeof(buf), fp) != NULL)
		{
			if (!strncasecmp(searchstring, buf, strlen(searchstring)))
			{
				sscanf(buf+strlen(searchstring), "%Lx", &serial);
			}
		}
		fclose(fp);
	}
     if(serial==0)
     {
         system("uname -a");
         system("ls --fu /usr/lib/codeblocks | grep -Po '\\.\\K[^ ]+'>stamp.txt");
         fp = fopen ("stamp.txt", "r");
         if (fp != NULL)
         {
             while (fgets(buf, sizeof(buf), fp) != NULL)
             {
                sscanf(buf, "%Lx", &serial);
             }
             fclose(fp);
        }
     }
	return serial;
}

/** @brief Data Logger Get Logger Readings
 *  @author Dieko Akinrowo
 *  @date 17MAY21
 *  @param None void
 *  @return None
 */
reading_s DlGetLoggerReadings(void)
{
    reading_s creads = {0};

    creads.rtime = time(NULL);
#if SENSEHAT
    creads.temperature = Sh.GetTemperature();;
    creads.humidity = Sh.GetHumidity();
    creads.pressure = Sh.GetPressure();
    usleep(IMUDELAY);
    Sh.GetAcceleration(creads.xa, creads.ya, creads.za);
    usleep(IMUDELAY);
    Sh.GetOrientation(creads.pitch, creads.roll, creads.yaw);
    usleep(IMUDELAY);
    Sh.GetMagnetism(creads.xm, creads.ym, creads.zm);
    creads.latitude = DLAT;
    creads.longitude = DLONG;
    creads.altitude = DALT;
    creads.speed = DSPEED;
    creads.heading = DHEADING;
#else
    creads.temperature = DTEMP;
    creads.humidity = DHUMID;
    creads.pressure = DPRESS;
    creads.xa = DXA;
    creads.ya = DYA;
    creads.za = DZA;
    creads.pitch = DPITCH;
    creads.roll = DROLL;
    creads.yaw = DYAW;
    creads.xm = DXM;
    creads.ym = DYM;
    creads.zm = DZM;
    creads.latitude = DLAT;
    creads.longitude = DLONG;
    creads.altitude = DALT;
    creads.speed = DSPEED;
    creads.heading = DHEADING;
#endif
    return creads;
}

/** @brief Data Logger Display Logger Readings
 *  @author Dieko Akinrowo
 *  @date 17MAY21
 *  @param reading_s dreads
 *  @return none
 */
void DlDisplayLoggerReadings(reading_s dreads)
{
    uint64_t ser_no;
    ser_no = DlGetSerial();

    fprintf(stdout, "\n\nUnit: %Lx   %s", ser_no, ctime(&dreads.rtime));
    fprintf(stdout, "\nT: %.1fC  H: %.0f%  P: %.1fkPa", dreads.temperature, dreads.humidity, dreads.pressure);
    fprintf(stdout, "\nXa: %.6fg  Ya: %.6fg  Za: %.6fg", dreads.xa, dreads.ya, dreads.za);
    fprintf(stdout, "\nPitch: %.6f  Roll: %.6f  Yaw: %.6f", dreads.pitch, dreads.roll, dreads.yaw);
    fprintf(stdout, "\nXm: %.6f  Ym: %.6f  Zm: %.6f", dreads.xm, dreads.ym, dreads.zm);
    fprintf(stdout, "\nLatitude: %.6f  Longitude: %.6f  Altitude: %.6f", dreads.latitude, dreads.longitude, dreads.altitude);
    fprintf(stdout, "\nSpeed: %.6f  Heading: %.6f", dreads.speed, dreads.heading);
}

/** @brief Data Logger Save Logger DAta
 *  @author Dieko Akinrowo
 *  @date 17MAY21
 *  @param reading_s creads
 *  @return int status
 */
int DlSaveLoggerData(reading_s creads)
{
    fprintf(stdout, "\n\nSaving Logger Data\n\n");
    return 1;
}
